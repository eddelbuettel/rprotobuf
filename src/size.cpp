#include "rprotobuf.h"

namespace rprotobuf{

/** 
 * get the number of bytes the message will take on the wire
 * 
 * @param xp external pointer to a Message*
 * @return the number of bytes 
 */
SEXP get_message_bytesize( SEXP xp ){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	SEXP size = PROTECT( Rf_ScalarInteger( message->ByteSize() ) );
	UNPROTECT( 1 ) ; /* size */
	return size ; 
}

SEXP get_field_size(SEXP xp, SEXP field){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	
	SEXP res = PROTECT( Rf_allocVector( INTSXP, 1 ) ) ;
	if( field_desc->is_repeated() ){
		INTEGER(res)[0] = message->GetReflection()->FieldSize(*message, field_desc ) ;
	} else{
		INTEGER(res)[0] = 1 ;
	}
	UNPROTECT(1) ;
	return res ;
}

} // namespace rprotobuf
