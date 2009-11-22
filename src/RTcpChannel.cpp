#include "RTcpChannel.h"

namespace rprotobuf{
	
	RTcpChannel::RTcpChannel(){
		socket_id = 0 ; 
	}
	
	void RTcpChannel::connect(const char* host, int port){
		socket_id = socket( AF_INET, SOCK_STREAM, 0 ) ;
		/* TODO : check the results */
		// build_sin(&sa, host, port);
		// setsockopt(xd->sock, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
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
    	std::string serialized_rpc = rpc->SerializeAsString() ;
    	
    	/* send the message to the socket */
    	
    	/* read the response from the socket */
    	
    	/* unserialize the response */
    	
    	Rf_error( "RTcpChannel::CallMethod is not yet implemented, patches welcome" ) ; 
    }
	
	uint32 RTcpChannel::id = 0 ;
	
	
} // namespace rprotobuf

