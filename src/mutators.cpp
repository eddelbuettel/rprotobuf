#include "rprotobuf.h" 
#include "fieldtypes.h" 

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

/**
 * set a message field to a new value
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 * @param value new value for the field
 *
 * @return allways NULL, the message is modified by reference
 */
SEXP setMessageField( SEXP pointer, SEXP name, SEXP value ){
	
#ifdef RPB_DEBUG
Rprintf( "<setMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
PRINT_DEBUG_INFO( "value", value ) ;
#endif

/* grab the Message pointer */
	Message* message = (Message*)EXTPTR_PTR(pointer) ;

	/* what we are looking for */
	const char * what = CHAR( STRING_ELT(name, 0 ) ) ;
	
	/* the message descriptor */
	const Descriptor* desc = message->GetDescriptor() ;
	
	/* the field descriptor */
	const FieldDescriptor* field_desc = desc->FindFieldByName( what ) ;
	if( !field_desc ){
		throwException( "could not get FieldDescriptor for field", "NoSuchFieldException" ) ;
	}
	
	const Reflection * ref = message->GetReflection() ;
    
	/* TODO: deal with value == NULL */
	
	if( field_desc->is_repeated() ){
		Rf_warning( "mutating repeated fields not yet implemented, patches welcome" ) ; 
	} else {
		switch( field_desc->type() ){
			
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetInt32(message, field_desc, (int32) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetInt32(message, field_desc, (int32) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetInt32(message, field_desc, (int32) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetInt32(message, field_desc, (int32) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to int32", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
    		
    		case TYPE_INT64:
    		case TYPE_SINT64:
    		case TYPE_SFIXED64:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetInt64(message, field_desc, (int64) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetInt64(message, field_desc, (int64) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetInt64(message, field_desc, (int64) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetInt64(message, field_desc, (int64) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    						}
    				}
    				break ;
    			}	
    		case TYPE_UINT32:
    		case TYPE_FIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetUInt32(message, field_desc, (uint32) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetUInt32(message, field_desc, (uint32) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetUInt32(message, field_desc, (uint32) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetUInt32(message, field_desc, (uint32) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to uint32", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
    		
     		
    		case TYPE_UINT64:
    		case TYPE_FIXED64:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetUInt64(message, field_desc, (int64) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetUInt64(message, field_desc, (int64) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetUInt64(message, field_desc, (int64) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetUInt64(message, field_desc, (int64) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
    		
  
    		case TYPE_DOUBLE:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetDouble(message, field_desc, (double) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetDouble(message, field_desc, (double) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetDouble(message, field_desc, (double) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetDouble(message, field_desc, (double) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to double", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
    			
    			
    		case TYPE_FLOAT:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetFloat(message, field_desc, (float) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetFloat(message, field_desc, (float) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetFloat(message, field_desc, (float) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetFloat(message, field_desc, (float) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
     			
    		case TYPE_BOOL:
   			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							ref->SetBool(message, field_desc, (bool) INTEGER(value)[0] ) ;
    							break ;
    						}
    					case REALSXP:
    						{
    							ref->SetBool(message, field_desc, (bool) REAL(value)[0] ) ;
    							break ;
    						}
    					case LGLSXP:
    						{
    							ref->SetBool(message, field_desc, (bool) LOGICAL(value)[0] ) ;
    							break ;
    						}
    					case RAWSXP:
    						{
    							ref->SetBool(message, field_desc, (bool) RAW(value)[0] ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
     		case TYPE_STRING:
    		case TYPE_BYTES:
    			{
    				switch( TYPEOF( value ) ){
    					case STRSXP:
    						{
    							/* FIXME: probably need to copy the string */
    							ref->SetString(message, field_desc, CHAR(STRING_ELT(value,0 )) ) ;
    							break ;
    						}
    				}
    				break ; 
    			}
    		
    		case TYPE_ENUM : 
    		case TYPE_MESSAGE:
    		case TYPE_GROUP: 
    			{
    				Rf_warning( "not yet implemented, patches welcome" ) ; 
    			}
    	}
    	
	}
	
	
	
#ifdef RPB_DEBUG
Rprintf( "</setMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
}

} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

