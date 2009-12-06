#include "rprotobuf.h"

namespace rprotobuf{

/**
 * clone a message
 *
 * @param xp external pointer to a message
 * @return a new message, clone of the input message
 */
SEXP clone_message( SEXP xp ){
	
#ifdef RPB_DEBUG
Rprintf( "<clone_message>\n" ) ;
#endif

	/* grab the Message pointer */
	GPB::Message* message = (GPB::Message*)EXTPTR_PTR(xp) ;

	/* cloning message as sheep */
	GPB::Message* sheep = message->New() ;
	sheep->CopyFrom( *message );
	
	SEXP sheep_xp = PROTECT( new_RS4_Message_( sheep ) ) ;
	UNPROTECT(1); 
	
#ifdef RPB_DEBUG
Rprintf( "</clone_message>\n" ) ;
#endif
	
	return sheep_xp; 

}
	
} // namespace rprotobuf

