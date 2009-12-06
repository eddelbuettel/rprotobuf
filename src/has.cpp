#include "rprotobuf.h"

namespace rprotobuf{

/**
 * TRUE if the message has the field name
 *
 * @param xp external pointer to the Message
 * @param name name of the field
 */
SEXP message_has_field( SEXP xp, SEXP name ){
#ifdef RPB_DEBUG
Rprintf( "<message_has_field>\n" ) ;
#endif

	/* grab the Message pointer */
	GPB::Message* message = (GPB::Message*)EXTPTR_PTR(xp) ;
	
	const GPB::Descriptor* desc = message->GetDescriptor(); 
	
	const char* what= CHAR(STRING_ELT(name,0));
	
	const GPB::FieldDescriptor* field_desc = desc->FindFieldByName( what ) ;
	
	SEXP res = PROTECT( Rf_allocVector( LGLSXP, 1 ) );  
	
	if( !field_desc ){
		LOGICAL(res)[0] = 0 ;
	} else{
		const GPB::Reflection * ref = message->GetReflection() ;
		if( field_desc->is_repeated() ){
			LOGICAL(res)[0] = ref->FieldSize( *message, field_desc ) > 0 ? 1 : 0 ;
		} else{
			LOGICAL(res)[0] = ref->HasField( *message, field_desc ) ? 1 : 0 ;
		}
	}
	UNPROTECT(1); 
	
#ifdef RPB_DEBUG
Rprintf( "</message_has_field>\n" ) ;
#endif
	
	return res ;

}

} // namespace rprotobuf

