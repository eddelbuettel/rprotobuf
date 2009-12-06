#include "rprotobuf.h"
#include "fieldtypes.h"
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */

namespace rprotobuf{

	/**
	 * Add values to a repeated field
	 *
	 * @param xp (Message*) external pointer
	 * @param field field tag number or name
	 * @param values values to append
	 */ 
	SEXP message_add_values( SEXP xp, SEXP field, SEXP values){
#ifdef RPB_DEBUG
Rprintf( "<message_add_values>\n" ) ;
#endif		
		Message* message = GET_MESSAGE_POINTER_FROM_XP( xp) ; 
		const Reflection * ref = message->GetReflection() ;
		FieldDescriptor* field_desc = getFieldDescriptor( message, field );
		
		if( values == R_NilValue || LENGTH(values) == 0 ){
			return(R_NilValue); 
		}
		
		if( field_desc->is_repeated() ){
			/* first check */
			switch( field_desc->type() ){
				case TYPE_ENUM:
					{
						CHECK_values_for_enum( field_desc, values) ; 
						break ;
					}
				case TYPE_MESSAGE:
				case TYPE_GROUP:
					{
						CHECK_messages( field_desc, values ) ;
						break ;
					}
				default:
					{// nothing
					}
			}

			int value_size = LENGTH( values ) ;
			/* then add the values */
			switch( field_desc->type() ){
				// {{{ int32
    			case TYPE_INT32:
    			case TYPE_SINT32:
    			case TYPE_SFIXED32:
    				{
    					switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								for( int i=0; i<value_size; i++){
    									ref->AddInt32( message, field_desc, GET_int32(values,i) ) ;
    								}
    								break ;
    							}
    						default: 
    							{
    								throwException( "Cannot convert to int32", "ConversionException" ) ; 
    							}
    					}
    					break ;   
    				}
				// }}}
    			
				// {{{ int64
				case TYPE_INT64:
    			case TYPE_SINT64:
    			case TYPE_SFIXED64:
    				{
    					switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							for( int i=0; i<value_size; i++){
	    							ref->AddInt64( message, field_desc, GET_int64(values,i) ) ;
	    						}
	    					default: 
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    					}
    					break ;
    				}
    				// }}}	
    				
    			// {{{ uint32
    			case TYPE_UINT32:
    			case TYPE_FIXED32:
    				{
    					switch( TYPEOF( values ) ){
   							case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								for( int i=0; i<value_size; i++){
	    								ref->AddUInt32( message, field_desc, GET_int32(values,i) ) ;
	    							}
	    							break ;
    							}
    						default: 
    							throwException( "Cannot convert to uint32", "ConversionException" ) ; 
    					}
    					break ;   
    				}
				// }}}
     			
				// {{{ uint64
    			case TYPE_UINT64:
    			case TYPE_FIXED64:
    				{
    					switch( TYPEOF( values ) ){
	   						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								for( int i=0; i<value_size; i++){
	    								ref->AddUInt64( message, field_desc, GET_uint64(values,i) ) ;
	    							}
	    							break ;
    							}
    						default: 
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    					}
    					break ;   
    				}
				// }}}
        	
				// {{{ double
    			case TYPE_DOUBLE:
    				{
    					switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								
    								for( int i=0; i<value_size; i++){
	    								ref->AddDouble( message, field_desc, GET_double(values,i) ) ;
	    							}
	    							break ;
    							}
    						default: 
    							throwException( "Cannot convert to double", "ConversionException" ) ; 
    					}
    					break ;   
    				}
				// }}}	
    				
				// {{{ float
    			case TYPE_FLOAT:
    				{
    					switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								
    								for( int i=0; i<value_size; i++){
	    								ref->AddFloat( message, field_desc, GET_float(values,i) ) ;
	    							}
	    							break ;
    							}
    						default: 
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    					}
    					break ;   
    				}
				// }}}	
    			
				// {{{ bool
				case TYPE_BOOL:
   				{
    					switch( TYPEOF( values ) ){
     						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:	
    							{
    								
    								for( int i=0; i<value_size; i++){
	    								ref->AddBool( message, field_desc, GET_bool(values,i) ) ;
	    							}
	    							break ;
    							}
   							default: 
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    					}
    					break ;   
    				}
				// }}}
				
     			// {{{ string
				case TYPE_STRING:
    			case TYPE_BYTES:
    				{
    					if( TYPEOF(values) == STRSXP ){ 
    						for( int i=0 ; i<value_size; i++){
				    			ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(values,i )) ) ) ;
				    		}
    					} else{
    						throwException( "Cannot convert to string", "ConversionException" ) ;
    					}
    					break ; 
    				}
				// }}}
    			
				// {{{ message
    			case TYPE_MESSAGE:
    			case TYPE_GROUP: 
    				{    
    					if( TYPEOF(values) == VECSXP )  {
    						for( int i=0; i<value_size; i++){
				    			Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( values, i) ) ; 
				    			/* we already know it is of the correct type because of the 
				    			  premptive chjeck above */
				    			
				    			ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ; 
				    		}
				    					
    					} else{
    						throwException( "type mismatch, expecting a list of 'Message' objects", "TypeMismatchException" ) ;
    					}
    					break ;
    				}
    				// }}}
    			
				// {{{ enum
    			case TYPE_ENUM : 
    				{
    					const EnumDescriptor* enum_desc = field_desc->enum_type() ;
        	
    					switch( TYPEOF( values ) ){
    						// {{{ numbers 
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:
    							{
    								for( int i=0; i<value_size; i++){
	    								int val = GET_int(values, i ); 
	    								ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
									}
	    							break ;
    							}
							// }}}
        	
							// {{{ STRSXP
    						case STRSXP:
    							{
    								for( int i=0; i<value_size; i++){
	    								std::string val = CHAR( STRING_ELT( values, i) ) ;
	    								const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    								ref->AddEnum( message, field_desc, evd ) ; 
									}
	    							break ;
    							}
							// }}}
    							
							// {{{ default
    						default: 
    							{
    								throwException( "cannot set enum value", "WrongTypeEnumValueException" ) ; 
    							}
							// }}}
    					}
    					break; 
    				}
					// }}}
    			default:
    				{
    					// nothing
    				}
    		}
		} else{
			throwException( "add can only be used on repeated fields", "NotRepeatedFieldException" ) ;
		}
		
		
#ifdef RPB_DEBUG
Rprintf( "</message_add_values>\n" ) ;
#endif		
		return( R_NilValue) ; 
	}
	
}

