#include "rprotobuf.h"

namespace rprotobuf{

	/** 
	 * clear a message
	 * 
	 * @param xp external pointer to the message
	 */
	SEXP clear_message( SEXP xp ){
		
		Message* m = GET_MESSAGE_POINTER_FROM_XP( xp ) ; 
		
		m->Clear() ;
		
		return( R_NilValue ); 
		
	}
	
} // namespace rprotobuf
