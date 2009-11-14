#include "rprotobuf.h"
#include "fieldtypes.h"

#define SAME(x,y,tol) ( (tol==0.0 && x == y ) ||  ( ( (x-y)*(x-y) < tol*tol ) ? 1 : 0 ) ) 

namespace rprotobuf {

	Rboolean identical_messages_( Message* m1,  Message* m2, double tol ){
		const Descriptor* d1 = m1->GetDescriptor() ;
		const Descriptor* d2 = m2->GetDescriptor() ;
		
		/* first of all, check if this is the same message type */
		if( d1 != d2 ){
			return _FALSE_ ;
		}
		
		const Reflection* ref = m2->GetReflection() ;
		
		/* iterate field descriptors */
		int nf = d1->field_count() ;
		for( int i=0; i<nf; i++){
			const FieldDescriptor* field_desc = d1->field( i ) ;
			
			if( field_desc->is_repeated() ){
				
				/* test if the size differs */
				int fs = ref->FieldSize( *m1, field_desc) ;
				if( fs != ref->FieldSize( *m2, field_desc) ) return _FALSE_ ;
				
				/* test all items */
				switch( field_desc->type() ){
					case TYPE_INT32:
    				case TYPE_SINT32:
    				case TYPE_SFIXED32:
    					{
    						for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedInt32( *m1, field_desc, j ) != ref->GetRepeatedInt32( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;
    					}
    				case TYPE_INT64:
    				case TYPE_SINT64:
    				case TYPE_SFIXED64:
    					{
    						for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedInt64( *m1, field_desc, j ) != ref->GetRepeatedInt64( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;
    					}
	    			case TYPE_UINT32:
	    			case TYPE_FIXED32:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedUInt32( *m1, field_desc, j ) != ref->GetRepeatedUInt32( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;
	    				}
	    			case TYPE_UINT64:
	    			case TYPE_FIXED64:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedUInt64( *m1, field_desc, j ) != ref->GetRepeatedUInt64( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;	    					
	    				}
	    			case TYPE_DOUBLE:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( !SAME( ref->GetRepeatedDouble( *m1, field_desc, j ), ref->GetRepeatedDouble( *m2, field_desc, j ), tol) ) return _FALSE_ ; 
    						}
    						break ;	    					
	    				}
	    			case TYPE_FLOAT:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( !SAME( ref->GetRepeatedFloat( *m1, field_desc, j ), ref->GetRepeatedFloat( *m2, field_desc, j ), tol) ) return _FALSE_ ; 
    						}
    						break ;	    					
	    				}
	    			case TYPE_BOOL:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedBool( *m1, field_desc, j ) != ref->GetRepeatedBool( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;	    					
	    				}
					case TYPE_STRING:
	    			case TYPE_BYTES:
	    				{
	    					for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedString( *m1, field_desc, j ) != ref->GetRepeatedString( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;	    					
	    				}
	    			case TYPE_ENUM :
	    				{
	    					for( int j=0; j<fs; j++){
    							if( ref->GetRepeatedEnum( *m1, field_desc, j ) != ref->GetRepeatedEnum( *m2, field_desc, j ) ) return _FALSE_ ; 
    						}
    						break ;
	    				}
	    			case TYPE_MESSAGE:
	    			case TYPE_GROUP:
	    				{
	    					for( int j=0; j<fs; j++){
    							const Message *mm1 = &ref->GetRepeatedMessage( *m1, field_desc, j ) ;
    							const Message *mm2 = &ref->GetRepeatedMessage( *m2, field_desc, j ) ;
	    						if( !identical_messages_( (Message*)mm1, (Message*)mm2, tol ) ){
	    							return _FALSE_ ;
	    						}
    						}
    						break ;
	    				}
	    			default:
	    				throwException( "unknown type" , "UnknownTypeException" ) ;
				}
				
			} else {
				
				switch( field_desc->type() ){
					case TYPE_INT32:
    				case TYPE_SINT32:
    				case TYPE_SFIXED32:
    					{
    						if( ref->GetInt32( *m1, field_desc) != ref->GetInt32( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;
    					}
    				case TYPE_INT64:
    				case TYPE_SINT64:
    				case TYPE_SFIXED64:
    					{
    						if( ref->GetInt64( *m1, field_desc) != ref->GetInt64( *m2, field_desc) ) return _FALSE_ ; 
    						break ;
    					}
	    			case TYPE_UINT32:
	    			case TYPE_FIXED32:
	    				{
	    					if( ref->GetUInt32( *m1, field_desc ) != ref->GetUInt32( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;
	    				}
	    			case TYPE_UINT64:
	    			case TYPE_FIXED64:
	    				{
	    					if( ref->GetUInt64( *m1, field_desc ) != ref->GetUInt64( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;	    					
	    				}
	    			case TYPE_DOUBLE:
	    				{
	    					if( ref->GetDouble( *m1, field_desc ) != ref->GetDouble( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;	    					
	    				}
	    			case TYPE_FLOAT:
	    				{
	    					if( ref->GetFloat( *m1, field_desc ) != ref->GetFloat( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;	    					
	    				}
	    			case TYPE_BOOL:
	    				{
	    					if( ref->GetBool( *m1, field_desc ) != ref->GetBool( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;	    					
	    				}
					case TYPE_STRING:
	    			case TYPE_BYTES:
	    				{
	    					if( ref->GetString( *m1, field_desc ) != ref->GetString( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;	    					
	    				}
	    			case TYPE_ENUM :
	    				{
	    					if( ref->GetEnum( *m1, field_desc) != ref->GetEnum( *m2, field_desc ) ) return _FALSE_ ; 
    						break ;
	    				}
	    			case TYPE_MESSAGE:
	    			case TYPE_GROUP:
	    				{
	    					const Message *mm1 = &ref->GetMessage( *m1, field_desc ) ;
    						const Message *mm2 = &ref->GetMessage( *m2, field_desc ) ;
	    					if( !identical_messages_( (Message*)mm1, (Message*)mm2, tol ) ){
	    						return _FALSE_ ;
	    					}
    						break ;
	    				}
	    			default:
	    				throwException( "unknown type" , "UnknownTypeException" ) ;
				}
				
			}
		}
		
		/* finally */
		return _TRUE_ ;
		
	}
	
	SEXP identical_messages( SEXP xp1, SEXP xp2){
		Message* m1 = GET_MESSAGE_POINTER_FROM_XP( xp1 ) ;
		Message* m2 = GET_MESSAGE_POINTER_FROM_XP( xp2 ) ;
		return Rf_ScalarLogical( identical_messages_( m1, m2, 0.0 ) ) ;
	}
	
	SEXP all_equal_messages( SEXP xp1, SEXP xp2, SEXP tol){
		Message* m1 = GET_MESSAGE_POINTER_FROM_XP( xp1 ) ;
		Message* m2 = GET_MESSAGE_POINTER_FROM_XP( xp2 ) ;
		return Rf_ScalarLogical( identical_messages_( m1, m2, REAL(tol)[0] ) ) ;
	}
	

} // namespace rprotobuf
