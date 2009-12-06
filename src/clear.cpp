#include "rprotobuf.h"

namespace rprotobuf{

	/** 
	 * clear a message
	 * 
	 * @param xp external pointer to the message
	 */
	SEXP clear_message( SEXP xp ){
		GPB::Message* m = GET_MESSAGE_POINTER_FROM_XP( xp ) ; 
		m->Clear() ;
		return( R_NilValue ); 
	}
	
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
