#include "RTcpChannel.h"

#define RPC_DEBUG

namespace rprotobuf{
	
	RTcpChannel::RTcpChannel(){
		socket_id = -1 ; 
	}
	
	int RTcpChannel::connect_socket(const char* host, int port){
		
		SAIN sa ;
		int opt = 1; 
		socket_id = socket( PF_INET, SOCK_STREAM, 0 ) ;
		memset(&sa,0,sizeof(SAIN));
	  	sa.sin_family=AF_INET;
	  	sa.sin_port=htons(port);
	  	sa.sin_addr.s_addr=(host)?inet_addr(host):htonl(INADDR_ANY);
	  	
		if( setsockopt( socket_id , IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt)) ){
			reset() ; 
			socketError() ; 
		}
		
		int res = connect(socket_id, (SA*)&sa, sizeof(sa)); 
		if( res==-1) {
			reset() ; 
			socketError(); 
		}
		return 0 ;
	}
	
	bool RTcpChannel::is_connected(){
		return socket_id > 0 ;
	}
	
	int RTcpChannel::getSocketId(){
		return socket_id ; 
	}
	
	void RTcpChannel::reset(){
		closesocket( socket_id ) ;
		socket_id = -1 ;
	}
	
	int RTcpChannel::send_(SEXP payload){
		int size = LENGTH( payload ) ;
		int bytesSent = 0 ;
		int sent ;
		Rbyte* p = RAW(payload); 
		while( bytesSent < size ){
			sent = send( socket_id, p, (size-bytesSent), 0 ) ;
			if( sent < 0 ){
				reset() ;
				socketError() ;
			}
			bytesSent = bytesSent + sent ;
			p = p + sent ;
		}
		return 0 ;
	}
	
	int RTcpChannel::send_rpc(Rpc* rpc){
		/* the message payload to send through the wire */
    	/* TODO: we should use th io classes to directly 
    	stream the message out rather than allocating memory 
    	for the string, etc ... */
    	int request_size = rpc->ByteSize() ;
    	
    	/* allocate a raw vector */
    	SEXP payload = PROTECT( Rf_allocVector( RAWSXP, request_size ) ) ;
    	rpc->SerializeToArray( RAW(payload) , request_size ) ;
    	
    	/* send the message to the socket */
    	int res = send_( payload ) ;
    	UNPROTECT( 1 ) ; /* payload */ 
    	
    	return res ;
	}
	
	int RTcpChannel::read_response( Rpc* response ){
		
		SocketCopyingInputStream socketStream( socket_id ); 
		io::CopyingInputStreamAdaptor stream( &socketStream, 1024 ) ;
		io::CodedInputStream coded_stream( &stream ) ; 
		
		response->MergePartialFromCodedStream(&coded_stream ) ;
		return 0 ;
	}
	
	void RTcpChannel::CallMethod(const MethodDescriptor* method,
                          RpcController* controller,
                          const Message* request,
                          Message* response,
                          Closure* done){
    	
    	id++ ;
    	uint32 this_id = id ;
    	
    	if( request->GetDescriptor() != method->input_type() ){
			Rf_error( "wrong message input type" ) ; 
		}
		
    	/* make the rpc message */
    	Rpc* rpc = new Rpc( ) ; 
    	Request* rpc_request = rpc->add_request() ; 
    	rpc_request->set_method( method->full_name() ) ;
    	rpc_request->set_serialized_request( request->SerializeAsString() ) ;
    	rpc_request->set_id( this_id ) ;
    	
    	/* send the rpc message through the socket */
    	if( send_rpc( rpc ) ){
    		Rf_error( "error sending the rpc message" ) ; 
    	}
    	
    	/* read the response from the socket */
    	Rpc* rpc_response = new Rpc() ;
    	if( read_response( rpc_response ) ){
    		Rf_error( "error reading the response" ) ; 
    	}
    	if( rpc_response->response_size() != 1 ){
    		Rf_error( "response Rpc does not contain a response" ) ; 
    	}
    	
    	const Response resp = rpc_response->response( 0 ) ;
    	
    	// we either have an error, or the actual message we want 
    	// as a bytes field
    	if( resp.has_error() ){
    		const Error err = resp.error() ;
    		Rf_error( "error [%d] : %s", 
    			err.has_code() ? err.code() : 0,
    			err.has_text() ? err.text().c_str() : "" ) ; 
    	}
    	
    	if( !resp.has_id() ){
    		Rf_error("response does not have the id of the request") ; 
    	}
    	uint32 resp_id = resp.id() ; 
    	if( resp_id != this_id ){
    		Rf_error( "id mistach, the id of the request does not match the id of the response" ) ; 
    	}
    	
    	std::string serialized_response = resp.serialized_response() ; 
    	response->ParsePartialFromString( serialized_response ) ;
    	
    }
	
    void RTcpChannel::socketError(){
    	THROW_SOCKET_ERROR( "socket error" ) ;
    }
    
    
    /* initialize */
	uint32 RTcpChannel::id = 0 ;
	
	
} // namespace rprotobuf

