#include "rprotobuf.h"

#if GOOGLE_PROTOBUF_VERSION < 2002001
#include "fieldtypes.h"
#endif

namespace rprotobuf{

	SEXP message_swap_fields(SEXP xp, SEXP field, SEXP left, SEXP right ){
		
		Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ; 
		FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
		const Reflection* ref = message->GetReflection(); 
		if( ! field_desc->is_repeated() ){
			Rf_error( "swap can only be used with repeated fields" ) ; 
		}
		int n = LENGTH(left); /* we know that length(left) == length(right) */ 
		for( int i=0; i<n; i++){
#if GOOGLE_PROTOBUF_VERSION < 2002001
			
			/* no SwapElements in protobuf < 2.2 so we cook our own */
			int i_left  = GET_int(left, i) ;
			int i_right = GET_int(right, i) ;
						
			switch( field_desc->type( ) ){
    			case TYPE_INT32:
    			case TYPE_SINT32:
    			case TYPE_SFIXED32:
					{	
						int32 v_left  = ref->GetRepeatedInt32( *message, field_desc, i_left ) ;
						int32 v_right = ref->GetRepeatedInt32( *message, field_desc, i_right ) ;
						ref->SetRepeatedInt32( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedInt32( message, field_desc, i_right, v_left ) ;
						break ;
					}
				case TYPE_INT64:
    			case TYPE_SINT64:
    			case TYPE_SFIXED64:
					{	
						int64 v_left  = ref->GetRepeatedInt64( *message, field_desc, i_left ) ;
						int64 v_right = ref->GetRepeatedInt64( *message, field_desc, i_right ) ;
						ref->SetRepeatedInt64( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedInt64( message, field_desc, i_right, v_left ) ;
						break ;
					}
	    		case TYPE_UINT32:
	    		case TYPE_FIXED32:
	    			{
    					uint32 v_left  = ref->GetRepeatedUInt32( *message, field_desc, i_left ) ;
						uint32 v_right = ref->GetRepeatedUInt32( *message, field_desc, i_right ) ;
						ref->SetRepeatedUInt32( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedUInt32( message, field_desc, i_right, v_left ) ;
						break ;
	    			}
	    		case TYPE_UINT64:
	    		case TYPE_FIXED64:
	    			{
    					uint64 v_left  = ref->GetRepeatedUInt64( *message, field_desc, i_left ) ;
						uint64 v_right = ref->GetRepeatedUInt64( *message, field_desc, i_right ) ;
						ref->SetRepeatedUInt64( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedUInt64( message, field_desc, i_right, v_left ) ;
						break ;
					}
				case TYPE_DOUBLE:
		    		{
		    			double v_left  = ref->GetRepeatedDouble( *message, field_desc, i_left ) ;
						double v_right = ref->GetRepeatedDouble( *message, field_desc, i_right ) ;
						ref->SetRepeatedDouble( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedDouble( message, field_desc, i_right, v_left ) ;
						break ;
					}
				case TYPE_FLOAT:
					{
						float v_left  = ref->GetRepeatedFloat( *message, field_desc, i_left ) ;
						float v_right = ref->GetRepeatedFloat( *message, field_desc, i_right ) ;
						ref->SetRepeatedFloat( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedFloat( message, field_desc, i_right, v_left ) ;
						break ;
					}
				case TYPE_BOOL:
					{
						bool v_left  = ref->GetRepeatedBool( *message, field_desc, i_left ) ;
						bool v_right = ref->GetRepeatedBool( *message, field_desc, i_right ) ;
						ref->SetRepeatedFloat( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedFloat( message, field_desc, i_right, v_left ) ;
						break ;
					}
				case TYPE_STRING:
	    		case TYPE_BYTES:
	    			{
	    				std::string v_left  = ref->GetRepeatedString( *message, field_desc , i_left ) ;
	    				std::string v_right = ref->GetRepeatedString( *message, field_desc , i_right ) ;
						ref->SetRepeatedString( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedString( message, field_desc, i_right, v_left ) ;
						break ;
	    			}
	    		case TYPE_ENUM :
	    			{
	    				const EnumValueDescriptor* v_left  = ref->GetRepeatedEnum( *message, field_desc, i_left ) ;
	    				const EnumValueDescriptor* v_right = ref->GetRepeatedEnum( *message, field_desc, i_right ) ;
						ref->SetRepeatedEnum( message, field_desc, i_left, v_right ) ;
						ref->SetRepeatedEnum( message, field_desc, i_right, v_left ) ;
						break ;
	    			}
    			case TYPE_MESSAGE:
    			case TYPE_GROUP:
    				{
    					 /* we probably can do with less copy */
    					 Message* m_left = (&ref->GetRepeatedMessage( *message, field_desc, i_left ))->New() ;
    					 Message* m_right = (&ref->GetRepeatedMessage( *message, field_desc, i_left ))->New() ;
    					 m_left->CopyFrom( ref->GetRepeatedMessage( *message, field_desc, i_right ) ) ; 
    					 m_right->CopyFrom(ref->GetRepeatedMessage( *message, field_desc, i_left ) ) ;
    					 ref->MutableRepeatedMessage(message, field_desc, i_left )->Clear() ; 
    					 ref->MutableRepeatedMessage(message, field_desc, i_left )->CopyFrom( *m_right ) ;
    					 ref->MutableRepeatedMessage(message, field_desc, i_right )->Clear() ; 
    					 ref->MutableRepeatedMessage(message, field_desc, i_right )->CopyFrom( *m_left ) ;
    					 break ;
    				}

			}
#else
			ref->SwapElements(message, field_desc, GET_int(left, i) , GET_int(right,i) ) ;
#endif			
		}
		return( R_NilValue ); 
	}

} // namespace rprotobuf
