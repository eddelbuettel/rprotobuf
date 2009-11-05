#include "rprotobuf.h"

namespace rprotobuf{

/**
 * creates a new message by merging two messages of the same type
 *
 * @param xp1 external pointer to a Message*
 * @param xp2 external pointer to a Message*
 *
 * @return a new message, as an R object of "protobufMessage" S4 class
 */
SEXP merge_message( SEXP xp1, SEXP xp2){

#ifdef RPB_DEBUG
Rprintf( "<merge_message>\n" ) ;
#endif

	// we assume both messages are of the same type
	// this is checked on the R side	
	Message* m1 = GET_MESSAGE_POINTER_FROM_XP( xp1 );
	Message* m2 = GET_MESSAGE_POINTER_FROM_XP( xp2 );
	Message* merged = m1->New() ; 
	merged->MergeFrom( *m1 ) ; 
	merged->MergeFrom( *m2 ); 
	SEXP res = PROTECT( new_RS4_Message_( merged ) ) ;
	UNPROTECT(1) ; /* res */
	
#ifdef RPB_DEBUG
Rprintf( "<merge_message>\n" ) ;
#endif
	return res ;
}

} // namespace rprotobuf
