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
	
namespace rprotobuf{
	
	/**
	 * invoke an rpc method over http
	 */
	SEXP invoke_method_http( SEXP method_xp, SEXP message_xp, SEXP host_xp, SEXP port_xp){
		
		/* grab parameters */
		GPB::MethodDescriptor* method = (GPB::MethodDescriptor*)EXTPTR_PTR(method_xp) ;
		GPB::Message* input = (GPB::Message*)EXTPTR_PTR( message_xp); 
		int port = INTEGER(port_xp)[0]; 
		const char* host = CHAR( STRING_ELT( host_xp, 0) ) ;
		
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
		char buffer[33] ;
		int input_size = input->ByteSize() ;
		sprintf( buffer, "%d", input_size ) ;
		
		std::string header = "POST /" ;
		header += method->service()->full_name();
		header += '/' ;
		header += method->name() ;
		header += " HTTP/1.0\r\nConnection: close\r\nContent-Length: " ;
		header += buffer ;
		header += "\r\n\r\n" ;
		
		/* send the header */
		Rprintf( "sending http request\n" ) ;  
		int sent = 0 ;
		int total_sent = 0;
		int total = header.length() ;
		const char* c_str = header.c_str() ;
		char* p = (char*)c_str ;
		while( total_sent < total ){
			sent = send( socket_id, p, (total-total_sent), 0 ) ;
			total_sent = total_sent + sent ;
			Rprintf( "headers : sent %d bytes\n", total_sent ) ;  
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
			Rprintf( "input message : sent %d bytes\n", total_sent ) ;  
			p = p + sent ;
		}
		
		/* now read the response */
		closesocket(socket_id);
		socket_id = - 1 ;
		
		Rf_error( "message sent to rpc http server but reading output message back is not yet implemented" ) ; 
		
		return R_NilValue ;
	}
	
	
	
} // namespace rprotobuf




