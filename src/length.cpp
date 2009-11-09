#include "rprotobuf.h"

namespace rprotobuf{

/**
 * The number of fields the message has. A field counts in these two situations :
 * - it is repeated and the array size is greater than 0
 * - it is not repeated and the message has it
 *
 * @param xp external pointer to the Message
 */
SEXP get_message_length( SEXP xp ){
#ifdef RPB_DEBUG
Rprintf( "<get_message_length>\n" ) ;
#endif

	/* grab the Message pointer */
	Message* message = GET_MESSAGE_POINTER_FROM_XP(xp) ;
	
	const Descriptor* desc = message->GetDescriptor(); 
	const Reflection * ref = message->GetReflection() ;
	
	int nfields = desc->field_count() ;
	
	int res = 0; 
	
	for( int i=0; i<nfields; i++){
		const FieldDescriptor* field_desc = desc->field( i ) ;
		if( field_desc->is_repeated() ){
			if( ref->FieldSize( *message, field_desc ) > 0 ){
				res++ ;
			}
		} else{
			if( ref->HasField( *message, field_desc ) ){
				res++ ;
			}
		}
	}
	
	SEXP ans = PROTECT( Rf_ScalarInteger( res ) ); 
	UNPROTECT(1); /* ans */
	
#ifdef RPB_DEBUG
Rprintf( "</get_message_length>\n" ) ;
#endif
	
	return ans ;

}

} // namespace rprotobuf

