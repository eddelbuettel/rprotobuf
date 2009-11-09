#include "rprotobuf.h"

namespace rprotobuf{

/**
 * Check if all required fields are set
 *
 * @param xp external pointer to the Message
 */
SEXP is_message_initialized( SEXP xp ){
#ifdef RPB_DEBUG
Rprintf( "<is_message_initialized>\n" ) ;
#endif

	/* grab the Message pointer */
	Message* message = GET_MESSAGE_POINTER_FROM_XP(xp) ;
	
	SEXP ans = PROTECT( Rf_ScalarLogical( (int) message->IsInitialized() ) );
	UNPROTECT(1) ; /* ans */
	
#ifdef RPB_DEBUG
Rprintf( "</is_message_initialized>\n" ) ;
#endif
	
	return ans ;

}

} // namespace rprotobuf

