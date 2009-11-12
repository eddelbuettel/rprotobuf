#include "rprotobuf.h" 
#include "fieldtypes.h" 
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */

/* need to actually copy the string */
#define COPYSTRING(s) s

namespace rprotobuf{

// {{{ GETDOUBLE
/**
 * get the index'th value of x, as an double
 *
 * @param x some R data
 * @param index the index
 * @return x[index], as an double
 * @throws CastException if x[index] cannot be converted to double
 */
/* FIXME: should we convert the NA's */
double GET_double( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (double)INTEGER(x)[index] ) ;
		case REALSXP: 
			return( REAL(x)[index] ) ;
		case LGLSXP:
			return( (double)LOGICAL(x)[index] );
		case RAWSXP:
			return( (double)RAW(x)[index] ) ;
		default:
				throwException( "cannot cast SEXP to double", "CastException" ) ; 
	}
	return 0.0  ; // -Wall 
}
// }}}

float GET_float( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (float)INTEGER(x)[index] ) ;
		case REALSXP: 
			return( (float)REAL(x)[index] ) ;
		case LGLSXP:
			return( (float)LOGICAL(x)[index] );
		case RAWSXP:
			return( (float)RAW(x)[index] ) ;
		default:
				throwException( "cannot cast SEXP to double", "CastException" ) ; 
	}
	return (float)0.0  ; // -Wall 
}

int GET_int( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( INTEGER(x)[index] );
		case REALSXP: 
			return( (int)REAL(x)[index] );
		case LGLSXP:
			return( (int)LOGICAL(x)[index] );
		case RAWSXP:
			return( (int)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to int32", "CastException" ) ; 
	}
	return 0 ; // -Wall, should not happen since we only call this when we know it works
}


int32 GET_int32( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (int32)INTEGER(x)[index] );
		case REALSXP: 
			return( (int32)REAL(x)[index] );
		case LGLSXP:
			return( (int32)LOGICAL(x)[index] );
		case RAWSXP:
			return( (int32)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to int32", "CastException" ) ; 
	}
	return (int32)0 ; // -Wall, should not happen since we only call this when we know it works
}


int64 GET_int64( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (int64)INTEGER(x)[index] );
		case REALSXP: 
			return( (int64)REAL(x)[index] );
		case LGLSXP:
			return( (int64)LOGICAL(x)[index] );
		case RAWSXP:
			return( (int64)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to int64", "CastException" ) ; 
	}
	return (int64)0 ; // -Wall, should not happen since we only call this when we know it works
}

uint32 GET_uint32( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (uint32)INTEGER(x)[index] );
		case REALSXP: 
			return( (uint32)REAL(x)[index] );
		case LGLSXP:
			return( (uint32)LOGICAL(x)[index] );
		case RAWSXP:
			return( (uint32)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to uint32", "CastException" ) ; 
	}
	return (uint32)0 ; // -Wall, should not happen since we only call this when we know it works
}

uint64 GET_uint64( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (uint64)INTEGER(x)[index] );
		case REALSXP: 
			return( (uint64)REAL(x)[index] );
		case LGLSXP:
			return( (uint64)LOGICAL(x)[index] );
		case RAWSXP:
			return( (uint64)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to uint64", "CastException" ) ; 
	}
	return (uint64)0 ; // -Wall, should not happen since we only call this when we know it works
}

bool GET_bool( SEXP x, int index ){
	switch( TYPEOF(x) ){
		case INTSXP: 
			return( (bool)INTEGER(x)[index] );
		case REALSXP: 
			return( (bool)REAL(x)[index] );
		case LGLSXP:
			return( (bool)LOGICAL(x)[index] );
		case RAWSXP:
			return( (bool)RAW(x)[index] ) ;
		default:
			throwException( "cannot cast SEXP to bool", "CastException" ) ; 
	}
	return (bool)0 ; // -Wall, should not happen since we only call this when we know it works
}


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
	// {{{ grab data
#ifdef RPB_DEBUG
Rprintf( "<setMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
PRINT_DEBUG_INFO( "value", value ) ;
#endif

	/* grab the Message pointer */
	Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer) ;

	/* the message descriptor */
	// const Descriptor* desc = message->GetDescriptor() ;
	
	/* {{{ check that we can get a file descriptor from name */
	FieldDescriptor* field_desc = getFieldDescriptor( message, name ); 
	// }}}
	
	const Reflection * ref = message->GetReflection() ;
    
	if( value == R_NilValue || LENGTH(value) == 0 ){
		ref->ClearField( message, field_desc ); 
		return R_NilValue ;
	}
	// }}}

	if( field_desc->is_repeated() ){
		// {{{ repeated fields
		int value_size = LENGTH(value); 
		int field_size = ref->FieldSize( *message, field_desc ) ;
		
		int need_clear = 0 ;
		
		/* {{{ in case of messages or enum, we have to check that all values
		  are ok before doing anything, othewise this could leed to modify a few values 
		  and then fail which is not good */
		
		switch( field_desc->type() ){
    		case TYPE_MESSAGE:
    		case TYPE_GROUP:
    			{
    				switch( TYPEOF( value ) ){
    					case VECSXP :
    						{
    							/* check that it is a list of Messages of the appropriate type */
    							for( int i=0; i<value_size; i++){
	    							if( !isMessage( VECTOR_ELT(value, i), field_desc->message_type()->full_name().c_str() ) ){
	    								/* TODO: include i, target type and actual type in the message */
	    								throwException( "incorrect type", "IncorrectMessageTypeException" ) ;
	    							}
	    						}
	    						break ;
	    					}
	    				case S4SXP: 
	    					{
	    						/* check that this is a message of the appropriate type */
	    						if( !isMessage( value, field_desc->message_type()->full_name().c_str() ) ){
    								throwException( "incorrect type", "IncorrectMessageTypeException" ) ;
    							}
    							break ;
    						}
    					default:
    						{
    							throwException( "impossible to convert to a message" , "ConversionException" ) ; 
    						}
    				}
    				break ;
    			}
    		case TYPE_ENUM : 
    			{
    				const EnumDescriptor* enum_desc = field_desc->enum_type() ;

    				/* check first, it means we have to loop twice, but 
    				   otherwise this could have some side effects before 
    				   the exception is thrown */
    				   
    				/* FIXME: the checking should go before the resizing */   
    				
    				switch( TYPEOF( value ) ){
    					// {{{ numbers 
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							int nenums = enum_desc->value_count() ;
    							int possibles [ nenums ] ;
    							for( int i=0; i< nenums; i++){
    								possibles[i] = enum_desc->value(i)->number(); 
    							}
    							
    							/* loop around the numbers to see if they are in the possibles */
    							for( int i=0; i<value_size; i++){
    								int val = GET_int(value, i ); 
    								int ok = 0; 
    								for( int j=0; j<nenums; j++){
    									if( val == possibles[j] ){
    										ok = 1; 
    										break ; 
    									}
    								}
    								if( !ok ){
    									throwException( "wrong value for enum", "WrongEnumValueException" ) ; 
    								}
    							}
    							
    							break ;
    						}
    					// }}}
    					
    					// {{{ STRSXP
    					case STRSXP:
    						{
    							int nenums = enum_desc->value_count() ;
    							char* possibles [ nenums ] ;
    							for( int i=0; i< nenums; i++){
    								possibles[i] = (char*)enum_desc->value(i)->name().c_str() ; 
    							}
    							
    							/* loop around the numbers to see if they are in the possibles */
    							for( int i=0; i<value_size; i++){
    								const char* val = CHAR( STRING_ELT(value, i )) ; 
    								int ok = 0; 
    								/* FIXME: there is probably something more efficient */
    								for( int j=0; j<nenums; j++){
    									if( !strcmp( val, possibles[j]) ){
    										ok = 1; 
    										break ; 
    									}
    								}
    								if( !ok ){
    									throwException( "wrong value for enum", "WrongEnumValueException" ) ; 
    								}
    							}
     							
    							break ;
    						}
    					// }}}
    					
    					default:
    						throwException( "impossible to convert to a enum" , "ConversionException" ) ; 
    				}
    				break ;
    			}
    		case TYPE_DOUBLE : 
    		case TYPE_FLOAT : 
    		case TYPE_INT64 : 
    		case TYPE_UINT64 : 
    		case TYPE_INT32 : 
    		case TYPE_FIXED64 : 
    		case TYPE_FIXED32 : 
    		case TYPE_BOOL : 
    		case TYPE_STRING : 
    		case TYPE_BYTES : 
    		case TYPE_UINT32 : 
    		case TYPE_SFIXED32 : 
    		case TYPE_SFIXED64 : 
    		case TYPE_SINT32 : 
    		case TYPE_SINT64 : 
    			{
					; // nothing, just to satisfy -Wall 
				}
		}
		// }}}
		  
		/* {{{ remove some items once if there are too many */
		if( field_size > value_size ) {
#if GOOGLE_PROTOBUF_VERSION < 2002001
			 need_clear = 1 ;
#else			
			/* we need to remove some */
			while( field_size > value_size ){
				ref->RemoveLast( message, field_desc ) ;
				field_size-- ;
			}
#endif
		}
		// }}}
		
		switch( field_desc->type() ){
			// {{{ int32
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							int i = 0;

#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddInt32( message, field_desc, GET_int32(value,i) ) ;
    								}
    							} else {
#endif    							

    								/* in any case, fill the values up to field_size */
    								for( ; i<field_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, GET_int32(value,i) ) ;
    								}
    								
    								/* then add some if needed */
    								if( value_size > field_size ){
    									for( ; i<value_size; i++){
    										ref->AddInt32( message, field_desc, GET_int32(value,i) ) ;
    									}
    								}
    							
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							}
#endif
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
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							int i = 0;

#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddInt64( message, field_desc, GET_int64(value,i) ) ;
    								}
    							} else {
#endif    						
	    							/* in any case, fill the values up to field_size */
	    							for( ; i<field_size; i++){
	    								ref->SetRepeatedInt64( message, field_desc, i, GET_int64(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddInt64( message, field_desc, GET_int64(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
    							break ;
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
    				switch( TYPEOF( value ) ){
   						case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddUInt32( message, field_desc, GET_uint32(value,i) ) ;
    								}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
	    							for( ; i<field_size; i++){
	    								ref->SetRepeatedUInt32( message, field_desc, i, GET_int32(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddUInt32( message, field_desc, GET_int32(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				switch( TYPEOF( value ) ){
	   					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddUInt64( message, field_desc, GET_uint64(value,i) ) ;
    								}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
									for( ; i<field_size; i++){
	    								ref->SetRepeatedUInt64( message, field_desc, i, GET_uint64(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddUInt64( message, field_desc, GET_uint64(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddDouble( message, field_desc, GET_double(value,i) ) ;
    								}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
									for( ; i<field_size; i++){
	    								ref->SetRepeatedDouble( message, field_desc, i, GET_double(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddDouble( message, field_desc, GET_double(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddFloat( message, field_desc, GET_float(value,i) ) ;
    								}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
	    							for( ; i<field_size; i++){
	    								ref->SetRepeatedFloat( message, field_desc, i, GET_float(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddFloat( message, field_desc, GET_float(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				switch( TYPEOF( value ) ){
     					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:	
    						{
    							
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddBool( message, field_desc, GET_bool(value,i) ) ;
    								}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
	    							for( ; i<field_size; i++){
	    								ref->SetRepeatedBool( message, field_desc, i, GET_bool(value,i) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									ref->AddBool( message, field_desc, GET_bool(value,i) ) ;
	    								}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				if( TYPEOF(value) == STRSXP ){ 
    					/* in any case, fill the values up to field_size */
    					int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								for( ; i<value_size; i++){
    									ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
    								}
    							} else {
#endif    							
			    					for( ; i<field_size; i++){
			    						ref->SetRepeatedString( message, field_desc, i, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
			    					}
			    					
			    					/* then add some if needed */
			    					if( value_size > field_size ){
			    						for( ; i<value_size; i++){
			    							ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
			    						}
			    					}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				if( TYPEOF( value ) == S4SXP ) { 
    					/* we know it is a message of the correct type (tested above) */
    					Message* mess = GET_MESSAGE_POINTER_FROM_S4( value ) ; 
    					
    					if( field_size == 1 ) {
    						/* FIXME: we should not __copy__ the message */ 
    						ref->MutableRepeatedMessage(message, field_desc, 0 )->CopyFrom( *mess ) ;
    					} else {
    						/* FIXME */
    						ref->ClearField( message, field_desc ); 
    						
    						/* FIXME: we should not __copy__ the message */
    						ref->AddMessage( message, field_desc )->CopyFrom( *mess ) ; 
    					}
    				} else if( TYPEOF(value) == VECSXP )  {
    					/* in any case, fill the values up to field_size */
    					int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								
    								for( ; i<value_size; i++){
    									
    									Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
			    						/* we already know it is of the correct type because of the 
			    						  premptive chjeck above */
			    						
			    						/* FIXME: we should not __copy__ */
			    						ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ;
    									
    								}
    							} else {
#endif    							
			    					for( ; i<field_size; i++){
			    						Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
			    						/* we already know it is of the correct type because of the 
			    						  premptive chjeck above */
			    						
			    						ref->MutableRepeatedMessage(message, field_desc, i )->CopyFrom( *mess ) ; ; 
			    					}
			    					
			    					/* then add some if needed */
			    					if( value_size > field_size ){
			    						for( ; i<value_size; i++){
			    							Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
			    							/* we already know it is of the correct type because of the 
			    							  premptive chjeck above */
			    							
			    							ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ; 
			    						}
			    					}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
    				} else{
    					throwException( "type mismatch, expecting a 'protobufMessage' object or a list of them", "TypeMismatchException" ) ;
    				}
    				break ;
    			}
    			// }}}
    		
			// {{{ enum
    		case TYPE_ENUM : 
    			{
    				const EnumDescriptor* enum_desc = field_desc->enum_type() ;

    				switch( TYPEOF( value ) ){
    					// {{{ INSXP 
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							int i = 0;
#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								
    								for( ; i<value_size; i++){
    									int val = GET_int(value, i ); 
	    								ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
									}
    							} else {
#endif    							
	    							/* in any case, fill the values up to field_size */
	    							for( ; i<field_size; i++){
	    								int val = GET_int(value, i ); 
	    								ref->SetRepeatedEnum( message, field_desc, i, enum_desc->FindValueByNumber(val) ) ;
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									int val = GET_int(value, i ); 
	    									ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
										}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
    							break ;
    						}
						// }}}

						// {{{ STRSXP
    					case STRSXP:
    						{
    							/* in any case, fill the values up to field_size */
    							int i = 0;

#if GOOGLE_PROTOBUF_VERSION < 2002001
    							if( need_clear ){
    								ref->ClearField( message, field_desc ) ; 
    								
    								for( ; i<value_size; i++){
    									std::string val = CHAR( STRING_ELT( value, i) ) ;
	    								const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    								ref->AddEnum( message, field_desc, evd ) ;
									}
									
    							} else {
#endif    							
	    							for( ; i<field_size; i++){
	   									std::string val = CHAR( STRING_ELT( value, i) ) ;
	    								const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    								ref->SetRepeatedEnum( message, field_desc, i, evd ) ; 
	    							}
	    							
	    							/* then add some if needed */
	    							if( value_size > field_size ){
	    								for( ; i<value_size; i++){
	    									std::string val = CHAR( STRING_ELT( value, i) ) ;
	    									const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    									ref->AddEnum( message, field_desc, evd ) ; 
										}
	    							}
#if GOOGLE_PROTOBUF_VERSION < 2002001
								}
#endif
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
    				
    			}
				// }}}
    			
    	}
		// }}}
	} else {
		// {{{ non repeated fields
		switch( field_desc->type() ){
			// {{{ int32
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetInt32(message, field_desc, GET_int32( value, 0 ) ); 
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
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetInt64(message, field_desc, GET_int64( value, 0 ) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    						}
    				}
    				break ;
    			}
    			// }}}	
    			
    		// {{{ uint32
    		case TYPE_UINT32:
    		case TYPE_FIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetUInt32(message, field_desc, GET_uint32( value, 0) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to uint32", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
			// }}}
     		
			// {{{ uint64
    		case TYPE_UINT64:
    		case TYPE_FIXED64:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetUInt64(message, field_desc, GET_int64( value, 0) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to int64", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
			// }}}
  
			// {{{ double
    		case TYPE_DOUBLE:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetDouble(message, field_desc, GET_double(value, 0) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to double", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
			// }}}	
    			
			// {{{ float
    		case TYPE_FLOAT:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetFloat(message, field_desc, GET_float(value, 0) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
			// }}}	
    		
			// {{{ bool
			case TYPE_BOOL:
   			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							ref->SetBool(message, field_desc, GET_bool(value, 0) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to float", "ConversionException" ) ; 
    						}
    				}
    				break ;   
    			}
			// }}}
			
     		// {{{ string
			case TYPE_STRING:
    		case TYPE_BYTES:
    			{
    				switch( TYPEOF( value ) ){
    					case STRSXP:
    						{
    							ref->SetString(message, field_desc, COPYSTRING( CHAR(STRING_ELT(value,0 )) ) ) ;
    							break ;
    						}
    					default: 
    						{
    							throwException( "Cannot convert to string", "ConversionException" ) ;
    						}
    				}
    				break ; 
    			}
			// }}}
    		
			// {{{ message
    		case TYPE_MESSAGE:
    		case TYPE_GROUP: 
    			{
    				if( TYPEOF( value ) == S4SXP && Rf_inherits( value, "protobufMessage" ) ){
    					Message* mess = (Message*) EXTPTR_PTR( GET_SLOT( value, Rf_install("pointer") ) ) ;
    					const char* type = mess->GetDescriptor()->full_name().c_str() ;
    					const char* target = field_desc->message_type()->full_name().c_str() ; 
    					if( strcmp( type, target ) ){
    						throwException( "wrong message type", "WrongMessageException" ) ;
    					}
    					Message* m = ref->MutableMessage( message, field_desc ) ; 
    					m->CopyFrom( *mess ) ;
    				} else {
    					throwException( "type mismatch, expecting a 'protobufMessage' object", "TypeMismatchException" ) ;
    				}
    				break ;
    			}
    			// }}}
    		
			// {{{ enum
    		case TYPE_ENUM : 
    			{
    				const EnumDescriptor* enum_desc = field_desc->enum_type() ;
    				
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    					case REALSXP:
    					case LGLSXP:
    					case RAWSXP:
    						{
    							int val = GET_int(value, 0 ) ;
    							const EnumValueDescriptor* evd = enum_desc->FindValueByNumber(val) ;
    							if( !evd ){
    								throwException( "wrong value for enum", "WrongEnumValueException" ) ; 
    							} else {
    								ref->SetEnum( message, field_desc, evd ); 
    							}
    							break ;
    						}
    					case STRSXP:
    						{
    							std::string val = CHAR( STRING_ELT( value, 0) ) ;
    							const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
    							if( !evd ){
    								throwException( "wrong value for enum", "WrongEnumValueException" ) ; 
    							} else {
    								ref->SetEnum( message, field_desc, evd ); 
    							}
    							break ;
    						}
    					default: 
    						{
    							throwException( "cannot set enum value", "WrongTypeEnumValueException" ) ; 
    						}
    				}
    				
    			}
			// }}}
    			
    	}
    	// }}}
	}
	
#ifdef RPB_DEBUG
Rprintf( "</setMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
}

} // namespace rprotobuf

