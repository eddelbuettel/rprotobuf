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

} // namespace rprotobuf
