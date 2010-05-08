#include "rprotobuf.h"
#include "fieldtypes.h"

namespace rprotobuf{
	
#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Message__,__NAME__)

/* same as above, but get the type from the message */
SEXP new_RS4_Message_( const GPB::Message* message ){
	
	Rcpp::S4 oo( "Message" ) ;
	Rcpp::XPtr<GPB::Message> xp(message, true ) ;
	oo.slot("pointer") = xp ;
	oo.slot("type"   ) = message->GetDescriptor()->full_name() ;
	return oo ;
}

/**
 * clone a message
 *
 * @param xp external pointer to a message
 * @return a new message, clone of the input message
 */
RCPP_FUNCTION_1( S4_Message, METHOD(clone) , Rcpp::XPtr<GPB::Message> message ){
	/* cloning message as sheep */
	GPB::Message* sheep = message->New() ;
	sheep->CopyFrom( *message );
	
	return S4_Message( sheep ) ;
}

/**
 * TRUE if the message has the field name
 *
 * @param xp external pointer to the Message
 * @param name name of the field
 */
RCPP_FUNCTION_2(bool, METHOD(has_field), Rcpp::XPtr<GPB::Message> message, std::string name ){

	const GPB::Descriptor* desc = message->GetDescriptor(); 
	const GPB::FieldDescriptor* field_desc = desc->FindFieldByName( name ) ;
	
	bool res = false ;
	if( field_desc ){
		const GPB::Reflection * ref = message->GetReflection() ;
		if( field_desc->is_repeated() ){
			res = ref->FieldSize( *message, field_desc ) > 0 ;
		} else{
			res = ref->HasField( *message, field_desc ) ;
		}
	}
	return res ;
}


/**
 * Check if all required fields are set
 *
 * @param xp external pointer to the Message
 */
RCPP_FUNCTION_1( bool, METHOD(is_initialized), Rcpp::XPtr<GPB::Message> message){
	return message->IsInitialized() ;
}


/** 
 * serialize a message to a file
 *
 * @param xp external pointer to a GPB::Message*
 * @param filename file name where to serialize
 */
RCPP_FUNCTION_VOID_2( METHOD(serialize_to_file) , Rcpp::XPtr<GPB::Message> message, const char* filename){
	
	/* open the file in binary mode to write */
	/* we make sure in the R side that filename is the full path of the file */
	int file = open( filename, 
		O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666); 
	
	/* using partial to allow partially filled messages */
	message->SerializePartialToFileDescriptor( file ) ;
	
	close( file ) ; 
}

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
RCPP_FUNCTION_1( Rcpp::RawVector, METHOD(get_payload), Rcpp::XPtr<GPB::Message> message ){

	/* create a raw vector of the appropriate size */
	int size = message->ByteSize() ;
	Rcpp::RawVector payload( size ) ;
	
	/* fill the array */
	message->SerializePartialToArray( payload.begin(), size ); 
	
	return( payload ) ;
}

RCPP_XP_METHOD_VOID_0(METHOD(clear), GPB::Message, Clear )

/**
 * Clear a field of a message
 *
 * @param xp (GPB::Message*) external pointer
 * @param field name or tag of the field
 */
RCPP_FUNCTION_VOID_2(METHOD(clear_field), Rcpp::XPtr<GPB::Message> m, SEXP field ){
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( m, field ) ;
	const GPB::Reflection* ref = m->GetReflection(); 
	ref->ClearField( m, field_desc ) ;
}


/**
 * @param xp external pointer to a Message
 * @return the message as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::Message> message ){
    
	Rcpp::CharacterVector fieldNames = getMessageFieldNames_(message) ;
	int nf = fieldNames.size() ;
	Rcpp::List val( nf ) ;
	for( int i=0; i<nf; i++){
		val[i] = getMessageField( message, Rcpp::CharacterVector::create( fieldNames[i] ) ) ; 
	}
	val.names() = fieldNames ;
	return val ;
}

/**
 * The number of fields the message has. A field counts in these two situations :
 * - it is repeated and the array size is greater than 0
 * - it is not repeated and the message has it
 *
 * @param xp external pointer to the Message
 */
RCPP_FUNCTION_1(int, METHOD(length), Rcpp::XPtr<GPB::Message> message){
	const GPB::Descriptor* desc = message->GetDescriptor(); 
	const GPB::Reflection * ref = message->GetReflection() ;
	
	int nfields = desc->field_count() ;
	
	int res = 0; 
	
	for( int i=0; i<nfields; i++){
		const GPB::FieldDescriptor* field_desc = desc->field( i ) ;
		if( field_desc->is_repeated() ){
			if( ref->FieldSize( *message, field_desc ) > 0 ){
				res++ ;
			}
		} else{
			if( ref->HasField( *message, field_desc ) ){
				res++ ;
			}
		}
	}
	return res ;
}


/**
 * Get the message descriptor of a Message
 * 
 * @param xp (GPB::Message*) external pointer
 * @return the descriptor, as a Descriptor R S4 object
 */
RCPP_FUNCTION_1(S4_Descriptor, METHOD(descriptor), Rcpp::XPtr<GPB::Message> message ){
	return( message->GetDescriptor() ) ;
}

RCPP_XP_METHOD_0( METHOD(as_character) , GPB::Message, DebugString) ;
RCPP_XP_METHOD_0( METHOD(bytesize), GPB::Message, ByteSize )

RCPP_FUNCTION_2( int, METHOD(field_size), Rcpp::XPtr<GPB::Message> message, SEXP field  ){
	
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	
	int res = 0 ;
	if( field_desc->is_repeated() ){
		res = message->GetReflection()->FieldSize(*message, field_desc ) ;
	} else{
		res = message->GetReflection()->HasField(*message, field_desc) ? 1: 0 ;
	}
	return res ;
}


RCPP_FUNCTION_VOID_3( METHOD(set_field_size), Rcpp::XPtr<GPB::Message> message, SEXP field, int target){
	
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	const GPB::Reflection* ref = message->GetReflection() ;
	
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



}

