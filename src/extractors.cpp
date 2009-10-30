#include "rprotobuf.h"
#include "fieldtypes.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

SEXP extractFieldAsSEXP( const Message * message, const Descriptor* desc, const FieldDescriptor * fieldDesc ){
	
	/* depending on the type, we need to create some regular SEXP (INTSXP) 
       or a message */
	
    const Reflection * ref = message->GetReflection() ;
       
    if( fieldDesc->is_repeated() ){
    	
    	// TODO
    	Rf_warning( "repeated fields are not implemented yet" ) ;
    	return( R_NilValue ) ; 
   	
    } else {
 
    	
    	SEXP res ;
    	
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
    			Rf_error( "CPPTYPE_ENUM not yet implemented" ) ;
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


} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

