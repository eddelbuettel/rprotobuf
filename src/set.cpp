#include "rprotobuf.h"
#include "fieldtypes.h"

namespace rprotobuf {

	/**
	 * set the values of a repeated field
	 *
	 * @param xp (GPB::Message*) external pointer
	 * @param field field tag number or name
	 * @param index positions (0-based) 
	 * @param values new values
	 */
	SEXP set_field_values( SEXP xp, SEXP field, SEXP index, SEXP values ){
		
		GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
		GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
		if( !field_desc->is_repeated() ){
			Rf_error( "set can only be used on repeated fields" ) ;
		}
		
		const GPB::Reflection* ref = message->GetReflection(); 
		
		/* we know here that LENGTH(index) == LENGTH(values) */
		int n = LENGTH(index) ;
		switch( field_desc->type() ){
			
    			case TYPE_INT32:
    			case TYPE_SINT32:
    			case TYPE_SFIXED32:
					{	
						for( int i=0; i<n; i++){
							ref->SetRepeatedInt32( message, field_desc, 
								GET_int( index, i ), 
								GET_int32( values, i ) ) ;
						}
						break ;
					}
				case TYPE_INT64:
    			case TYPE_SINT64:
    			case TYPE_SFIXED64:
					{	
						for( int i=0; i<n; i++){
							ref->SetRepeatedInt64( message, field_desc, 
								GET_int( index, i ), 
								GET_int64( values, i ) ) ;
						}
						break ;
					}
	    		case TYPE_UINT32:
	    		case TYPE_FIXED32:
	    			{
						for( int i=0; i<n; i++){
							ref->SetRepeatedUInt32( message, field_desc, 
								GET_int( index, i ), 
								GET_uint32( values, i ) ) ;
						}
						break ;
	    			}
	    		case TYPE_UINT64:
	    		case TYPE_FIXED64:
	    			{
						for( int i=0; i<n; i++){
							ref->SetRepeatedUInt64( message, field_desc, 
								GET_int( index, i ), 
								GET_uint64( values, i ) ) ;
						}
						break ;
					}
				case TYPE_DOUBLE:
		    		{
		    			for( int i=0; i<n; i++){
							ref->SetRepeatedDouble( message, field_desc, 
								GET_int( index, i ), 
								GET_double( values, i ) ) ;
						}
						break ;

					}
				case TYPE_FLOAT:
					{
						for( int i=0; i<n; i++){
							ref->SetRepeatedFloat( message, field_desc, 
								GET_int( index, i ), 
								GET_float( values, i ) ) ;
						}
						break ;
					}
				case TYPE_BOOL:
					{
						for( int i=0; i<n; i++){
							ref->SetRepeatedBool( message, field_desc, 
								GET_int( index, i ), 
								GET_bool( values, i ) ) ;
						}
						break ;
					}
				case TYPE_STRING:
	    		case TYPE_BYTES:
	    			{
	    				
	    				for( int i=0; i<n; i++){
							ref->SetRepeatedString( message, field_desc, 
								GET_int( index, i ), 
								GET_stdstring( values, i ) ) ;
						}
						break ;
	    			}
	    		case TYPE_ENUM :
	    			{
	    				CHECK_values_for_enum( field_desc, values ) ;
	    				
	    				const GPB::EnumDescriptor* enum_desc = field_desc->enum_type() ;
	    				
	    				switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:
    							{
    								for( int i=0; i<n; i++){
	    								int val = GET_int(values, i ); 
	    								ref->SetRepeatedEnum( message, field_desc, i, 
	    									enum_desc->FindValueByNumber(val) ) ;
	    							}
	    							
    								break ;
    							}
    						case STRSXP:
    							{
    								
    								for( int i=0; i<n; i++){
	   									std::string val = CHAR( STRING_ELT( values, i) ) ;
	    								const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    								ref->SetRepeatedEnum( message, field_desc, i, evd ) ; 
	    							}
	    							
    								
    								break ;
    							}
    						default:
    							throwException( "impossible to convert to a enum" , "ConversionException" ) ; 
	    				}
	    				
	    				
	    			}
    			case TYPE_MESSAGE:
    			case TYPE_GROUP:
    				{
    					CHECK_messages( field_desc, values ) ; 
    					
    					for( int i=0; i<n; i++){
			    			GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( values, i) ) ; 
			    			ref->MutableRepeatedMessage(message, field_desc, i )->CopyFrom( *mess ) ; ; 
			    		}
			    		break ;  
    				}
    			default: 
    				throwException( "unknown type", "UnknownTypeException" ) ;
		}
		return ( R_NilValue ); 
	}
	
	
	/**
	 * fetch a subset of the values of a field
	 *
	 * @param (GPB::Message*) external pointer
	 * @param field name or tag number of the field
	 * @param index 
	 */
	SEXP get_field_values( SEXP xp, SEXP field, SEXP index ){
		
		GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
		GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
		if( !field_desc->is_repeated() ){
			Rf_error( "fetch can only be used on repeated fields" ) ;
		}
		
		int n = LENGTH( index ); 
		switch( field_desc->type() ){
			
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
			case TYPE_INT64:
    		case TYPE_SINT64:
    		case TYPE_SFIXED64:
			case TYPE_UINT32:
	    	case TYPE_FIXED32:
	    	case TYPE_UINT64:
	    	case TYPE_FIXED64:
	    	case TYPE_ENUM:
	    		{
	    			SEXP res = PROTECT( Rf_allocVector(INTSXP, n) ) ;
	    			for( int i=0; i<n; i++){
						INTEGER(res)[i] = MESSAGE_GET_REPEATED_INT( 
							message, field_desc, GET_int( index, i ) ) ;
					}
					UNPROTECT(1);
					return res; 
				}
			case TYPE_DOUBLE:
		    case TYPE_FLOAT:
				{
					SEXP res = PROTECT( Rf_allocVector(REALSXP, n) ) ;
	    			for( int i=0; i<n; i++){
						REAL(res)[i] = MESSAGE_GET_REPEATED_DOUBLE( 
							message, field_desc, GET_int( index, i ) ) ;
					}
					UNPROTECT(1);
					return res; 
				}
			case TYPE_BOOL:
				{
					SEXP res = PROTECT( Rf_allocVector(LGLSXP, n) ) ;
	    			for( int i=0; i<n; i++){
						LOGICAL(res)[i] = MESSAGE_GET_REPEATED_DOUBLE( 
							message, field_desc, GET_int( index, i ) ) ;
					}
					UNPROTECT(1);
					return res; 
				}
			case TYPE_STRING:
	    	case TYPE_BYTES:
	    		{
	    			const GPB::Reflection* ref = message->GetReflection() ; 
	    			SEXP res = PROTECT( Rf_allocVector( STRSXP, n )  );  
    				for( int i=0; i<n; i++){
    					SET_STRING_ELT( res, i, 
    						Rf_mkChar( ref->GetRepeatedString( *message, field_desc, GET_int( index, i ) ).c_str() ) ) ;
    				}
    			    UNPROTECT(1); 
    			    return res ;
	    		}
	    	case TYPE_MESSAGE:
    		case TYPE_GROUP:
    			{
	    			const GPB::Reflection* ref = message->GetReflection() ; 
	    			SEXP res = PROTECT( Rf_allocVector( VECSXP, n ) ) ;
    				for( int i=0; i<n; i++){
    					SET_VECTOR_ELT( res, i, 
    						new_RS4_Message_( CLONE( &ref->GetRepeatedMessage( *message, field_desc, i ) ) ) ) ;
    				} 
    				UNPROTECT(1);
    				return res ;
    			}
    		default: 
    			throwException( "unknown type", "UnknownTypeException" ) ;
		}
		return R_NilValue ; // -Wall 
	}
	
} // namespace rprotobuf
