#include "rprotobuf.h"

namespace rprotobuf{

	RCPP_XP_METHOD_VOID_0(clear_message, GPB::Message, Clear )
	
	/**
	 * Clear a field of a message
	 *
	 * @param xp (GPB::Message*) external pointer
	 * @param field name or tag of the field
	 */
	SEXP clear_message_field( SEXP xp, SEXP field ){
		GPB::Message* m = GET_MESSAGE_POINTER_FROM_XP( xp ) ; 
		GPB::FieldDescriptor* field_desc = getFieldDescriptor( m, field ) ;
		const GPB::Reflection* ref = m->GetReflection(); 
		ref->ClearField( m, field_desc ) ;
		return( R_NilValue );
	}
	
} // namespace rprotobuf
