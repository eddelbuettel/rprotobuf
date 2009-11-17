#include "rprotobuf.h"
#include "fieldtypes.h" 

namespace rprotobuf{

/** 
 * get the number of bytes the message will take on the wire
 * 
 * @param xp external pointer to a Message*
 * @return the number of bytes 
 */
SEXP get_message_bytesize( SEXP xp ){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	SEXP size = PROTECT( Rf_ScalarInteger( message->ByteSize() ) );
	UNPROTECT( 1 ) ; /* size */
	return size ; 
}

SEXP get_field_size(SEXP xp, SEXP field){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	
	SEXP res = PROTECT( Rf_allocVector( INTSXP, 1 ) ) ;
	if( field_desc->is_repeated() ){
		INTEGER(res)[0] = message->GetReflection()->FieldSize(*message, field_desc ) ;
	} else{
		INTEGER(res)[0] = message->GetReflection()->HasField(*message, field_desc) ? 1: 0 ;
	}
	UNPROTECT(1) ;
	return res ;
}

SEXP set_field_size(SEXP xp, SEXP field, SEXP newsize){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	const Reflection* ref = message->GetReflection() ;
	
	int target = INTEGER(newsize)[0] ;
	if( field_desc->is_repeated() ){
		int current = ref->FieldSize(*message, field_desc ) ;
		
		if( target == 0){
			ref->ClearField( message, field_desc );
		} else if( current > target ){
			while( current != target ){
				ref->RemoveLast( message, field_desc ) ;
				current-- ;
			}
		} else if( current == target ) {
			/* nothing to do */
		} else { /* current < target */
			
			while( current != target ){
			
				switch( field_desc->type() ){
						case TYPE_INT32:
    					case TYPE_SINT32:
    					case TYPE_SFIXED32:
    				        {
    				        	ref->AddInt32(message, field_desc, (int32)0 ) ;
    				        	break ;
    				        }
    					case TYPE_INT64:
						case TYPE_SINT64:
						case TYPE_SFIXED64:
    				        {
    				        	ref->AddInt64(message, field_desc, (int64)0 ) ;
    				        	break ;
    				        }
		    			case TYPE_UINT32:
    					case TYPE_FIXED32:
    						{
    							ref->AddUInt32(message, field_desc, (uint32)0 ) ;
    				        	break ;
    				        }
    					case TYPE_UINT64:
    					case TYPE_FIXED64:
    						{
    							ref->AddUInt32(message, field_desc, (uint64)0 ) ;
    				        	break ;
    						}
    				    case TYPE_DOUBLE:
    				    	{
    				    		ref->AddDouble(message, field_desc, (double)0.0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_FLOAT:
    				    	{
    				    		ref->AddFloat(message, field_desc, (float)0.0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_BOOL:
    				    	{
    				    		ref->AddBool(message, field_desc, (bool)0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_STRING:
    				    case TYPE_BYTES:
    				    	{
    				    		ref->AddString(message, field_desc, "" ) ;
    							break ;
    				    	}
    				    case TYPE_MESSAGE:
    				    case TYPE_GROUP:
    				    	{
    				    		/* fill with the prototype for that message type */
    				    		Rf_error( "growing repeated messages not implemented yet, patches welcome" ) ;
    				    		break ;
    				    	}
    				    case TYPE_ENUM:
    				    	{ 
    				    		/* fill with the prototype for that message type */
    				    		Rf_error( "growing repeated enum not implemented yet, patches welcome" ) ;
    				    		break ;
    				    	}
    				} /* switch */
    			
    			current++ ;
    		} /* while */
			
			
		}
		
	} else{
		if( target == 0 ){
			if( ref->HasField( *message, field_desc ) ){
				ref->ClearField( message, field_desc );
			}
		} else {
			if( !ref->HasField( *message, field_desc ) ){
				switch( field_desc->type() ){
					case TYPE_INT32:
    				case TYPE_SINT32:
    				case TYPE_SFIXED32:
    			        {
    			        	ref->SetInt32(message, field_desc, (int32)0 ) ;
    			        	break ;
    			        }
    				case TYPE_INT64:
					case TYPE_SINT64:
					case TYPE_SFIXED64:
    			        {
    			        	ref->SetInt64(message, field_desc, (int64)0 ) ;
    			        	break ;
    			        }
		    		case TYPE_UINT32:
    				case TYPE_FIXED32:
    					{
    						ref->SetUInt32(message, field_desc, (uint32)0 ) ;
    			        	break ;
    			        }
    				case TYPE_UINT64:
    				case TYPE_FIXED64:
    					{
    						ref->SetUInt32(message, field_desc, (uint64)0 ) ;
    			        	break ;
    					}
    			    case TYPE_DOUBLE:
    			    	{
    			    		ref->SetDouble(message, field_desc, (double)0.0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_FLOAT:
    			    	{
    			    		ref->SetFloat(message, field_desc, (float)0.0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_BOOL:
    			    	{
    			    		ref->SetBool(message, field_desc, (bool)0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_STRING:
    			    case TYPE_BYTES:
    			    	{
    			    		ref->SetString(message, field_desc, "" ) ;
    						break ;
    			    	}
    			    case TYPE_MESSAGE:
    			    case TYPE_GROUP:
    			    	{
    			    		/* fill with the prototype for that message type */
    			    		Rf_error( "not implemented yet, patches welcome" ) ;
    			    		break ;
    			    	}
    			    case TYPE_ENUM:
    			    	{ 
    			    		/* fill with the prototype for that message type */
    			    		Rf_error( "not implemented yet, patches welcome" ) ;
    			    		break ;
    			    	}
    				}
    			}
		}
	}
	return R_NilValue ;
}



} // namespace rprotobuf
