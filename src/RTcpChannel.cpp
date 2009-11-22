#include "RTcpChannel.h"

namespace rprotobuf{
	
	RTcpChannel::RTcpChannel(){
		socket_id = 0 ; 
	}
	
	int RTcpChannel::connect_socket(const char* host, int port){
		SAIN sa ;
		int opt = 1; 
		socket_id = socket( AF_INET, SOCK_STREAM, 0 ) ;
		setsockopt( socket_id , IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
		if (connect(socket_id, (SA*)&sa, sizeof(sa))==-1) {
			closesocket( socket_id ) ;
			socket_id = -1 ;
			Rprintf( "RTcpChannel::connect( '%s', %d) : cannot connect\n", host, port ) ;
			return -1 ;
		}
		/* TODO : send a greeting message */
		return 0 ;
	}
	
	int RTcpChannel::send_(SEXP payload){
		int size = LENGTH( payload ) ;
		int bytesSent = 0 ;
		int sent ;
		Rbyte* p = RAW(payload); 
		while( bytesSent < size ){
			sent = send( socket_id, p, (size-bytesSent), 0 ) ;
			if( sent < 0 ){
				// FIXME : there was an error, do something
				// sockerrno contains the error number
				return -1 ;
			}
			bytesSent = bytesSent + sent ;
			p = p + sent ;
		}
		return 0 ;
	}
	
	void RTcpChannel::CallMethod(const MethodDescriptor* method,
                          RpcController* controller,
                          const Message* request,
                          Message* response,
                          Closure* done){
    	
    	id++ ;
    
    	/* TODO: check that the request matches the expected
    	         type of the method input */
    	
    	/* make the rpc message */
    	Rpc* rpc = new Rpc( ) ; 
    	Request* rpc_request = rpc->add_request() ; 
    	rpc_request->set_method( method->full_name() ) ;
    	rpc_request->set_serialized_request( request->SerializeAsString() ) ;
    	rpc_request->set_id( id ) ;
    	
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
    	
    	/* read the response from the socket */
    	
    	/* unserialize the response */
    	
    	Rf_error( "RTcpChannel::CallMethod is not yet implemented, patches welcome" ) ; 
    }
	
	uint32 RTcpChannel::id = 0 ;
	
	
} // namespace rprotobuf

