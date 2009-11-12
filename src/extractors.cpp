#include "rprotobuf.h"
#include "fieldtypes.h"

namespace rprotobuf{

/**
 * extract a field from a message
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 *
 * @return the field called "name" of the message if the 
 *         message has the field, otherwise an error is generated
 */
SEXP getMessageField( SEXP pointer, SEXP name ){
	
#ifdef RPB_DEBUG
Rprintf( "<getMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
#endif

	/* grab the Message pointer */
	Message* message = (Message*)EXTPTR_PTR(pointer) ;

	/* the message descriptor */
	const Descriptor* desc = message->GetDescriptor() ;
	
	FieldDescriptor* field_desc = (FieldDescriptor*)0;
	
	switch( TYPEOF( name) ){
	case STRSXP:
		{
			/* what we are looking for */
			const char * what = CHAR( STRING_ELT(name, 0 ) ) ;
			
			/* the field descriptor */
			field_desc = (FieldDescriptor*)desc->FindFieldByName( what ) ;
			
			break ;
		}
	case REALSXP:
		{
			
			/* the field descriptor */
			field_desc = (FieldDescriptor*)desc->FindFieldByNumber( (int)REAL(name)[0] ) ;
			
			break ;
		}
	case INTSXP: 
		{
			/* the field descriptor */
			field_desc = (FieldDescriptor*)desc->FindFieldByNumber( INTEGER(name)[0] ) ;
			
			break ;
		}
	}
	
	if( !field_desc ){
		throwException( "could not get FieldDescriptor for field", "NoSuchFieldException" ) ;
	}
	
#ifdef RPB_DEBUG
Rprintf( "</getMessageField>\n" ) ;
#endif

	return( extractFieldAsSEXP(message, desc, field_desc) ) ;
	
}

SEXP extractFieldAsSEXP( const Message * message, const Descriptor* desc, const FieldDescriptor * fieldDesc ){
	
	/* depending on the type, we need to create some regular SEXP (INTSXP) 
       or a message */
	
    const Reflection * ref = message->GetReflection() ;
       
    if( fieldDesc->is_repeated() ){
    	
    	SEXP res = R_NilValue;
    	
    	int size = ref->FieldSize(*message, fieldDesc ); 
    	switch( fieldDesc->type() ){
    		
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			res = PROTECT( Rf_allocVector( INTSXP, size ) ); 
    			for( int i=0; i<size; i++){
    				INTEGER(res)[i] = (int) ref->GetRepeatedInt32( *message, fieldDesc, i ) ;
    				i++ ;
    			}
    			break ;
    		
    		case TYPE_INT64:
    		case TYPE_SINT64:
    		case TYPE_SFIXED64:
    			res = PROTECT( Rf_allocVector( INTSXP, size )) ; 
    			for( int i=0; i<size; i++){
    				INTEGER(res)[i] = (int) ref->GetRepeatedInt64( *message, fieldDesc, i ) ;
    			}
    			break ;
    		
    		case TYPE_UINT32:
    		case TYPE_FIXED32:
    			res = PROTECT( Rf_allocVector( INTSXP, size )) ; 
    			for( int i=0; i<size; i++){
    				INTEGER(res)[i] = (int) ref->GetRepeatedUInt32( *message, fieldDesc, i) ;
    			}
    			break ;
    		
    		case TYPE_UINT64:
    		case TYPE_FIXED64:
    			res = PROTECT( Rf_allocVector( INTSXP, size )) ; 
    			for( int i=0; i<size; i++){
    				INTEGER(res)[i] = (int) ref->GetRepeatedUInt64( *message, fieldDesc, i ) ;
    			}
    			break ;
 
    		case TYPE_DOUBLE:
    			res = PROTECT( Rf_allocVector( REALSXP, size )) ; 
    			for( int i=0; i<size; i++){
    				REAL(res)[i] = (double) ref->GetRepeatedDouble( *message, fieldDesc, i ) ;
    			}
    			break ;
    		
    		case TYPE_FLOAT:
    			res = PROTECT( Rf_allocVector( REALSXP, size )) ; 
    			for( int i=0; i<size; i++){
    				REAL(res)[i] = (double) ref->GetRepeatedFloat( *message, fieldDesc, i ) ;
    			}
    			break ;
    			
    		case TYPE_BOOL:
    			res = PROTECT( Rf_allocVector( LGLSXP, size ) );
    			for( int i=0; i<size; i++){
    				LOGICAL(res)[i] = ref->GetRepeatedBool( *message, fieldDesc, i ) ? 1 : 0;
    			}
    			break ;
    		
    		case TYPE_ENUM : 
    			res = PROTECT( Rf_allocVector( INTSXP, size )  ); 
    			for( int i=0; i<size; i++){
    				INTEGER(res)[i] = ref->GetRepeatedEnum( *message, fieldDesc, i )->number() ;
    			}
    			break ;	
    			
    		
    		case TYPE_STRING:
    		case TYPE_BYTES:
    			res = PROTECT( Rf_allocVector( STRSXP, size )  );  
    			for( int i=0; i<size; i++){
    				SET_STRING_ELT( res, i, Rf_mkChar( ref->GetRepeatedString( *message, fieldDesc, i ).c_str() ) ) ;
    			}
    			break ;
    		
    		case TYPE_MESSAGE:
    		case TYPE_GROUP:
    			res = PROTECT( Rf_allocVector( VECSXP, size ) ) ;
    			for( int i=0; i<size; i++){
    				SET_VECTOR_ELT( res, i, 
    					new_RS4_Message_( &ref->GetRepeatedMessage( *message, fieldDesc, i ) ) ) ;
    			}
    			break ;
    	}
    	
    	UNPROTECT(1); /* res */
    	return( res ); 
     	
    	
    } else {
 
    	
    	SEXP res = R_NilValue;
    	
    	switch( fieldDesc->type() ){
    		
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			res = PROTECT( Rf_allocVector( INTSXP, 1 ) ); 
    			INTEGER(res)[0] = (int) ref->GetInt32( *message, fieldDesc ) ;
    			break ;
    		
    		case TYPE_INT64:
    		case TYPE_SINT64:
    		case TYPE_SFIXED64:
    			res = PROTECT( Rf_allocVector( INTSXP, 1 )) ; 
    			INTEGER(res)[0] = (int) ref->GetInt64( *message, fieldDesc ) ;
    			break ;
    		
    		case TYPE_UINT32:
    		case TYPE_FIXED32:
    			res = PROTECT( Rf_allocVector( INTSXP, 1 ) ) ; 
    			INTEGER(res)[0] = (int) ref->GetUInt32( *message, fieldDesc ) ;
    			break ;
    		
    		case TYPE_UINT64:
    		case TYPE_FIXED64:
    			res = PROTECT( Rf_allocVector( INTSXP, 1 )  ); 
    			INTEGER(res)[0] = (int) ref->GetUInt64( *message, fieldDesc ) ;
    			break ;
 
    		case TYPE_DOUBLE:
    			res = PROTECT( Rf_allocVector( REALSXP, 1 ) ) ;
    			REAL(res)[0] = (double) ref->GetDouble( *message, fieldDesc ) ;
    			break ;
    		
    		case TYPE_FLOAT:
    			res = PROTECT( Rf_allocVector( REALSXP, 1 ) ) ;
    			REAL(res)[0] = (double) ref->GetFloat( *message, fieldDesc ) ;
    			break ;
    			
    		case TYPE_BOOL:
    			res = PROTECT( Rf_allocVector( LGLSXP, 1 ) );
    			LOGICAL(res)[0] = ref->GetBool( *message, fieldDesc ) ? 1 : 0;
    			break ;
    		
    		case TYPE_ENUM : 
    			res = PROTECT( Rf_allocVector( INTSXP, 1 )  ); 
    			INTEGER(res)[0] = ref->GetEnum( *message, fieldDesc )->number() ;
    			break ;	
    			
    		
    		case TYPE_STRING:
    		case TYPE_BYTES:
    			res = PROTECT( Rf_mkString( ref->GetString( *message, fieldDesc ).c_str() ) ) ;
    			break ;
    		
    		case TYPE_MESSAGE:
    		case TYPE_GROUP:
    			res = PROTECT( new_RS4_Message_( &ref->GetMessage( *message, fieldDesc ) ) ) ;
    			break ;
    	}
    	
    	UNPROTECT(1); /* res */
    	return( res ); 
     	
    }
}

/**
 * Get the message descriptor of a Message
 * 
 * @param xp (Message*) external pointer
 * @return the descriptor, as a protobufDescriptor R S4 object
 */
SEXP get_message_descriptor( SEXP xp){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
	return( new_RS4_Descriptor( message->GetDescriptor() ) ) ;
}


} // namespace rprotobuf

