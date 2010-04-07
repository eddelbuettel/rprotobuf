#include "rprotobuf.h"

#include <sys/types.h>
#include <sys/socket.h>

#include "sisocks.h"

/* FIXME: this should be probably handled by sisocks
          we need it for the TCP_NODELAY socket option */
#include <netinet/tcp.h>

#define RESET(MSG) closesocket(socket_id); \
	socket_id = - 1 ; \
	THROW_SOCKET_ERROR( "socket error" ) ; 

#define LINE_BUF_SIZE 1024

/* debug output - change the DBG(X) X to enable debugging output */
#define DBG(X) X


namespace rprotobuf{
	
	/**
	 * invoke an rpc method over http
	 */
	SEXP invoke_method_http( SEXP method_xp, SEXP message_xp, SEXP host_xp, SEXP port_xp, SEXP root_xp ){
		
		/* grab parameters */
		GPB::MethodDescriptor* method = (GPB::MethodDescriptor*)EXTPTR_PTR(method_xp) ;
		GPB::Message* input = (GPB::Message*)EXTPTR_PTR( message_xp); 
		int port = INTEGER(port_xp)[0]; 
		const char* host = CHAR( STRING_ELT( host_xp, 0) ) ;
		const char* root = CHAR( STRING_ELT( root_xp, 0) ) ;
		
		/* setup the socket */
		int socket_id = - 1 ;
		SAIN sa ;
		int opt = 1; 
		socket_id = socket( PF_INET, SOCK_STREAM, 0 ) ;
		memset(&sa,0,sizeof(SAIN));
	  	sa.sin_family=AF_INET;
	  	sa.sin_port=htons(port);
	  	sa.sin_addr.s_addr=(host)?inet_addr(host):htonl(INADDR_ANY);
	  	
		if( setsockopt( socket_id , IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt)) ){
			RESET( "setting socket options") ;
		}
		
		int res = connect(socket_id, (SA*)&sa, sizeof(sa)); 
		if( res==-1) {
			RESET( "cannot connect" ) ; 
		}
		
		/* building the HTTP request header */
		char buf[33] ;
		int input_size = input->ByteSize() ;
		sprintf( buf, "%d", input_size ) ;
		
		std::string header = "POST " ;
		header += root ; /* we know root starts and ends with a / */
		header += method->service()->full_name();
		header += "?method=" ;
		header += method->name() ;
		header += " HTTP/1.0\r\nConnection: close\r\nHost: 127.0.0.1\r\nContent-Type:application/x-protobuf\r\nContent-Length: " ;
		header += buf ;
		header += "\r\n\r\n" ;
		
		/* send the header */
		DBG(Rprintf( "sending http request\n" )) ;  
		int sent = 0 ;
		int total_sent = 0;
		int total = header.length() ;
		const char* c_str = header.c_str() ;
		char* p = (char*)c_str ;
		while( total_sent < total ){
			sent = send( socket_id, p, (total-total_sent), 0 ) ;
			total_sent = total_sent + sent ;
			DBG(Rprintf( "headers : sent %d bytes\n", total_sent )) ;  
			DBG(Rprintf( "%s\n", header.c_str() )) ;  
			p = p + sent ;
		}
		
		/* send the message payload */
		char payload[ input_size ] ;
		p = payload ;
		input->SerializeToArray( payload, input_size );
		total_sent = 0;
		while( total_sent < input_size ){
			sent = send( socket_id, p, (input_size-total_sent), 0 ) ;
			total_sent = total_sent + sent ;
			DBG(Rprintf( "input message : sent %d bytes\n", total_sent ) );  
			p = p + sent ;
		}
		
		/* make sure this is enough to read all the headers */
		char buffer[LINE_BUF_SIZE] ;
		char* response_body ;
		int content_length = 0 ;
		int success = 0 ;
		
		int n = recv( socket_id, buffer, LINE_BUF_SIZE, 0 ) ;
		DBG(Rprintf( "reading %d bytes\n", n )) ;
		
		char* s = buffer ;
		while( *s ){
			if( s[0] == '\n' || ( s[0] == '\r' && s[1] == '\n' ) ){
				/* single empty line : end of headers */
				DBG(Rprintf( "end of request - moving to body\n" ) );
				
				/* skip the (CR)LF */
				if( s[0] == '\r' ) s++ ; 
				s++ ;
				
				if( content_length ){
					response_body = (char*)malloc( content_length ) ;
					/* fill this */
					int pos = 0 ;
					char* p = response_body ;
					while( pos<content_length ){
						if( !s ) break ;
						*p = *s ;
						p++; s++; pos++;
					}
					while( pos < content_length ){
						/* FIXME: maybe we can stream this directly in the message */
						n = recv( socket_id, p , (content_length - pos) , 0 ) ;
						DBG(Rprintf( "reading %d bytes\n", n ) );
						if( n < 1){
							RESET( "reading the body" ) ; 
						}
						pos += n ;
					}
					closesocket( socket_id ) ;
					socket_id = -1 ;
					
					/* the body was read in full, we can now fill the 
					   response message */
					GPB::Message* result = PROTOTYPE( method->output_type() ) ;
					result->ParsePartialFromArray( response_body, content_length ) ;
					return( new_RS4_Message_( result ) ) ;
					
				} else {
					Rf_error( "need Content-Length header" ) ; 
				}
				
			} 
			
			/* read one line of header */
			char* bol = s; /* beginning of line */
			while (*s && *s != '\r' && *s != '\n') s++;
			if (!*s) { 
				/* incomplete line - this must mean the request 
				   was too large for the buffer, just generate an error 
				   for now, fix later */
				Rf_error( "response headers too large" ) ; 
			} else{
				/* complete header line, parse it */
				if (*s == '\r') *(s++) = 0;
				if (*s == '\n') *(s++) = 0;
				
				if( !success ){
					
					unsigned int rll = strlen(bol); /* request line length */
					if( rll < 9) {
						Rf_error("response line too short : {%s}", bol ) ; 
					}
					
					/* we have not parsed the first line of the 
					   headers yet */
					if( strncmp( bol, "HTTP/", 5 ) ){
						Rf_error( "wrong protocol, expecting HTTP {%s}", bol ) ; 
					}
					
					if( !( strncmp( bol+5, "1.0 ", 4) || strncmp(bol+5, "1.1 ", 4) )){
						Rf_error( "HTTP version should be 1.0 or 1.1 : {%s}", bol ) ; 
					}
					
					if( strncmp( bol+9, "200 OK", 6) ){
						Rf_error( "invocation error : {%s}", bol+9 ) ;
					}
					
					/* otherwise, things are ok */
					success = 1 ;
				}
				
				DBG(Rprintf("complete line: {%s}\n", bol)) ;
				
				/* lower case before the : */
				char *k = bol;
				while (*k && *k != ':') {
				    if (*k >= 'A' && *k <= 'Z')
					*k |= 0x20;
				    k++;
				}
				
				if (*k == ':') {
				    *(k++) = 0;
				    while (*k == ' ' || *k == '\t') k++;
				    printf("header '%s' => '%s'\n", bol, k);
				    if (!strcmp(bol, "content-length")) {
						content_length = atoi(k);
				    }
				}
				
				/* TODO: check if result ok */
				
			}
			
		}
		
		/* we only arrive here if something went wrong */
		
		closesocket(socket_id);
		socket_id = - 1 ;
		
		return R_NilValue ;
	}
	
	
	
} // namespace rprotobuf




