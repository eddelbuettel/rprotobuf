// #include "rprotobuf.h"
// #include "RTcpChannel.h"
// 
// namespace rprotobuf {
// 	
// 	SEXP getChannel( SEXP host, SEXP port ){
// 		
// 		const char* h = CHAR( STRING_ELT(host, 0 ) ) ; 
// 		int p = INTEGER(port)[0] ;
// 		    
// 		RTcpChannel * channel = new RTcpChannel() ;
// 		channel->connect_socket( h, p ) ; 
// 		
// 		SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("RpcChannel")) );
//   		if (!Rf_inherits(oo, "RpcChannel"))
//   		  throwException("unable to create 'RpcChannel' S4 object", "CannotCreateObjectException" );
//   	  	
// 		SEXP ptr   = PROTECT( /* TODO: finalizer */
// 			R_MakeExternalPtr( (void*)channel , R_NilValue, R_NilValue));
// 		
// 		SET_SLOT( oo, Rf_install( "pointer") , ptr ); 
// 		SET_SLOT( oo, Rf_install( "host" ) , host ) ;
// 		SET_SLOT( oo, Rf_install( "port" ) , port ) ;
// 		UNPROTECT(2) ; /* oo, ptr ) ;*/ 
// 		
// 		return oo ; 
// 		
// 	}
// 	
// 	/**
// 	 * get the socket file descriptor associated with
// 	 * 
// 	 * @param xp (RTcpChannel*) external pointer
// 	 */
// 	SEXP getChannelId( SEXP xp){
// 		RTcpChannel* channel = (RTcpChannel*) EXTPTR_PTR( xp ) ;
// 		return Rf_ScalarInteger( channel->getSocketId() );  
// 	}
// 	
// 	
// 	SEXP invoke( SEXP method_xp, SEXP message_xp, SEXP channel_xp ){
// 		
// 		RTcpChannel* channel = (RTcpChannel*) EXTPTR_PTR( channel_xp ) ;
// 		GPB::MethodDescriptor* method = (GPB::MethodDescriptor*) EXTPTR_PTR( method_xp ) ;
// 		GPB::Message* message = (GPB::Message*) EXTPTR_PTR( message_xp ) ;
// 		GPB::Message* response = PROTOTYPE( method->output_type() )  ;
// 		
// 		if( !channel->is_connected() ){
// 			Rf_error( "channel is not connected" ) ; 
// 		}
// 		
// 		channel->CallMethod( method, (RpcController*)0, message, 
// 			response, (Closure*) 0 ) ;
// 		
// 		return new_RS4_Message_(response ) ;
// 		
// 	}
// 	
// 	
// } // namespace rprotobuf


