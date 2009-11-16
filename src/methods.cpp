#include "rprotobuf.h"

namespace rprotobuf{

	/**
	 * Get the descriptor for the input type of a method
	 */
	SEXP get_method_input_type( SEXP xp ){
		
		MethodDescriptor* method = GET_METHOD( xp) ;
		return new_RS4_Descriptor(method->input_type() );
		
	}
	
	/**
	 * Get the descriptor for the input type of a method
	 */
	SEXP get_method_output_type( SEXP xp ){
		
		MethodDescriptor* method = GET_METHOD( xp) ;
		return new_RS4_Descriptor(method->output_type() );
		
	}
	
	
	SEXP get_method_input_prototype( SEXP xp ){
		
		MethodDescriptor* method = GET_METHOD( xp) ;
		const Descriptor* desc = method->input_type();
		Message * message = (Message*)MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
		return( new_RS4_Message_( message ) ) ;
	}
	
	
	SEXP get_method_output_prototype( SEXP xp ){
		
		MethodDescriptor* method = GET_METHOD( xp) ;
		const Descriptor* desc = method->output_type();
		Message * message = (Message*)MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
		return( new_RS4_Message_( message ) ) ;
	}
	

	
	SEXP valid_input_message( SEXP method_xp, SEXP message_xp ){
		
		Message* message = GET_MESSAGE_POINTER_FROM_XP( message_xp ); 
		MethodDescriptor* method = GET_METHOD( method_xp ) ;
		
		return Rf_ScalarLogical( message->GetDescriptor() == method->input_type() ? _TRUE_ : FALSE );
	}
	
	SEXP valid_output_message( SEXP method_xp, SEXP message_xp ){
		
		Message* message = GET_MESSAGE_POINTER_FROM_XP( message_xp ); 
		MethodDescriptor* method = GET_METHOD( method_xp ) ;
		
		return Rf_ScalarLogical( message->GetDescriptor() == method->output_type() ? _TRUE_ : FALSE );
	}
	
} // namespace rprotobuf




