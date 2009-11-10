#include "rprotobuf.h" 
#include "fieldtypes.h" 
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */

/* this contains a lot of redundant code due to the cpp type 
          in proto and the R SEXP type (INTSXP, ...) */

/* need to actually copy the string */
#define COPYSTRING(s) s

namespace rprotobuf{

// {{{ GETINT
/**
 * get the index'th value of x, as an int
 *
 * @param x some R data
 * @param index the index
 * @return x[index], as an int
 * @throws CastException if x[index] cannot be converted to int
 */ 
int GETINT( SEXP x, int index ){
	int res = 0;  // default value to quieten g++ -Wall
	switch( TYPEOF(x) ){
		case INTSXP: 
			{
				res = INTEGER(x)[index] ;
				break ; 
			}
		case REALSXP: 
			{
				res = (int)REAL(x)[index] ;
				break ;
			}
		case LGLSXP:
			{
				res = (int)LOGICAL(x)[index];
				break ;
			}
		case RAWSXP:
			{
				res = (int)RAW(x)[index];
			}
		default:
			{
				throwException( "cannot cast SEXP to int", "CastException" ) ; 
			}
	}
	return res ;
}
// }}}	
	
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
	Message* message = (Message*)EXTPTR_PTR(pointer) ;

	/* the message descriptor */
	const Descriptor* desc = message->GetDescriptor() ;
	
	/* the field descriptor */
	FieldDescriptor* field_desc = (FieldDescriptor*)0;
	switch( TYPEOF(name) ){
		case STRSXP:
			{
				const char * what = CHAR( STRING_ELT(name, 0 ) ) ;
	
				field_desc = (FieldDescriptor*)desc->FindFieldByName( what ) ;
				
				break ;
			}
		case REALSXP: 
			{
				
				field_desc = (FieldDescriptor*)desc->FindFieldByNumber( (int)REAL(name)[0] ) ;
			
				break ;
			}
		case INTSXP:
			{
				field_desc = (FieldDescriptor*)desc->FindFieldByNumber( INTEGER(name)[0] ) ;
				
				break ;
			}
	}
	
	if( !field_desc ){
		throwException( "could not get FieldDescriptor for field", "NoSuchFieldException" ) ;
	}
	
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
		
		switch( field_desc->type() ){
			// {{{ int32
    		case TYPE_INT32:
    		case TYPE_SINT32:
    		case TYPE_SFIXED32:
    			{
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}
    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}
    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}
    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt32( message, field_desc, i, (int32) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt32( message, field_desc, (int32) RAW(value)[i] ) ;
    								}
    								
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
    				switch( TYPEOF( value ) ){
    					case INTSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}
    					
    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case RAWSXP: 
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedInt64( message, field_desc, i, (int64) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddInt64( message, field_desc, (int64) RAW(value)[i] ) ;
    								}
    								
    							}
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
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt32( message, field_desc, i, (uint32) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt32( message, field_desc, (uint32) RAW(value)[i] ) ;
    								}
    								
    							}
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
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedUInt64( message, field_desc, i, (uint64) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddUInt64( message, field_desc, (uint64) RAW(value)[i] ) ;
    								}
    								
    							}
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
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedDouble( message, field_desc, i, (double) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddDouble( message, field_desc, (double) RAW(value)[i] ) ;
    								}
    								
    							}
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
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedFloat( message, field_desc, i, (float) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddFloat( message, field_desc, (float) RAW(value)[i] ) ;
    								}
    								
    							}
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
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) INTEGER(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) INTEGER(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) INTEGER(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) INTEGER(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case REALSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) REAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) REAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) REAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) REAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}

    					case LGLSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) LOGICAL(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) LOGICAL(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) LOGICAL(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) LOGICAL(value)[i] ) ;
    								}
    								
    							}
    							break ;
    						}
    						
    					case RAWSXP:
    						{
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) RAW(value)[i] ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedBool( message, field_desc, i, (bool) RAW(value)[i] ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) RAW(value)[i] ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddBool( message, field_desc, (bool) RAW(value)[i] ) ;
    								}
    								
    							}
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
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									ref->SetRepeatedString( message, field_desc, i, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									ref->SetRepeatedString( message, field_desc, i, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(value,i )) ) ) ;
    								}
    								
    							}
    							break ;
    						}

    				}
    				break ; 
    			}
			// }}}
    		
			// {{{ message
    		case TYPE_MESSAGE:
    		case TYPE_GROUP: 
    			{
    				if( TYPEOF( value ) == S4SXP ) { 
    					/* probably a single message */
    					if( !isMessage( value, field_desc->message_type()->full_name().c_str() ) ){
    						throwException( "incorrect type", "IncorrectMessageTypeException" ) ;
    					}
    					Message* mess = GET_MESSAGE_POINTER_FROM_S4( value ) ; 
    					
    					if( field_size == 1 ) {
    						ref->MutableRepeatedMessage(message, field_desc, 0 )->CopyFrom( *mess ) ;
    					} else {
    						ref->ClearField( message, field_desc ); 
    						ref->AddMessage( message, field_desc )->CopyFrom( *mess ) ; 
    					}
    				} else if( TYPEOF(value) == VECSXP )  {
    					/* probably a list of messages */
    					/* first of all, check that all elements of the list 
    						are message of the correct type, so that if one is not
    						we generate the exception first without side effect of altering
    						the previous messages */
    					
    					for( int i=0; i<value_size; i++){
    						if( !isMessage( VECTOR_ELT(value, i), field_desc->message_type()->full_name().c_str() ) ){
    							/* TODO: include i, target type and actual type in the message */
    							throwException( "incorrect type", "IncorrectMessageTypeException" ) ;
    						}
    					}
    					
    					if( field_size == value_size ){
    						/* same size : set all the messages */
    						for(int i=0 ;i<value_size; i++){
    							
    							Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
    							/* we already know it is of the correct type because of the 
    							  premptive chjeck above */
    							
    							ref->MutableRepeatedMessage(message, field_desc, i )->CopyFrom( *mess ) ; ; 
    							
    						}
    					
    					} else if( field_size < value_size )  {
    						
    						int i;
    						/* first set the values up to the current field size */
    						for( i=0; i<field_size; i++){
    							Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
    							/* we already know it is of the correct type because of the 
    							  premptive chjeck above */
    							
    							ref->MutableRepeatedMessage(message, field_desc, i )->CopyFrom( *mess ) ; 
    						}
    						
    						/* then add the remaining messages */
    						for( ;i<value_size; i++){
    							Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
    							/* we already know it is of the correct type because of the 
    							  premptive chjeck above */
    							
    							ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ; 
    						}
    						
    					} else{ 
    						/* FIXME : do we really have to clear ? */
    						
    						ref->ClearField( message, field_desc );
    						
    						for(int i=0 ;i<value_size; i++){
    							Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( value, i) ) ; 
    							/* we already know it is of the correct type because of the 
    							  premptive chjeck above */
    							
    							ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ; 
    						}
    					}
    								
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

    				/* check first, it means we have to loop twice, but 
    				   otherwise this could have some side effects before 
    				   the exception is thrown */
    				
    				switch( TYPEOF( value ) ){
    					// {{{ INSXP 
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
    								int val = GETINT(value, i ); 
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
    							
    							/* we are ok now, all values are suitable */
    							
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									int val = GETINT(value, i ); 
    									ref->SetRepeatedEnum( message, field_desc, i, enum_desc->FindValueByNumber(val) ) ; 
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									int val = GETINT(value, i ); 
    									ref->SetRepeatedEnum( message, field_desc, i, enum_desc->FindValueByNumber(val) ) ;
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									int val = GETINT(value, i ); 
    									ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									int val = GETINT(value, i ); 
    									ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
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
    							
    							/* we are ok now, all values are suitable */
    							
    							
    							
    							if( value_size == field_size ){
    								/* just set the values */
    								for( int i=0; i<value_size; i++){
    									std::string val = CHAR( STRING_ELT( value, i) ) ;
    									const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
    									ref->SetRepeatedEnum( message, field_desc, i, evd ) ; 
    								}
    							} else if( value_size < field_size ) {
    								int i;
    								/* first set the values up to the current field size */
    								for( i=0; i<field_size; i++){
    									std::string val = CHAR( STRING_ELT( value, i) ) ;
    									const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
    									ref->SetRepeatedEnum( message, field_desc, i, evd ) ; 
    								}
    								/* then add the remaining */
    								for( ;i<value_size; i++){
    									std::string val = CHAR( STRING_ELT( value, i) ) ;
    									const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
    									ref->AddEnum( message, field_desc, evd ) ; 
    								}
    								
    							} else{
    								/* need to reset */
    								ref->ClearField( message, field_desc ); 
    								
    								/* and add all */
    								for(int i=0 ;i<value_size; i++){
    									std::string val = CHAR( STRING_ELT( value, i) ) ;
    									const EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
    									ref->AddEnum( message, field_desc, evd ) ; 
    								}
    								
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
			// }}}
    		
			// {{{ int64
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
    			// }}}	
    			
    		// {{{ uint32
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
			// }}}
     		
			// {{{ uint64
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
			// }}}
  
			// {{{ double
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
			// }}}	
    			
			// {{{ float
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
			// }}}	
    		
			// {{{ bool
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
    					
    					Rf_warning( "setting 'messages' fields not yet implemented , patches welcome" ) ;		
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
    							int val = GETINT(value, 0 ) ;
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

