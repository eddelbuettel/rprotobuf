#include "rprotobuf.h"

namespace rprotobuf{
	
/**
 * clone a message
 *
 * @param xp external pointer to a message
 * @return a new message, clone of the input message
 */
RCPP_FUNCTION_1( S4_Message, Message__clone, Rcpp::XPtr<GPB::Message> message ){
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
RCPP_FUNCTION_2(bool, Message__has_field, Rcpp::XPtr<GPB::Message> message, std::string name ){

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
RCPP_FUNCTION_1( bool, Message__is_initialized, Rcpp::XPtr<GPB::Message> message){
	return message->IsInitialized() ;
}


/** 
 * serialize a message to a file
 *
 * @param xp external pointer to a GPB::Message*
 * @param filename file name where to serialize
 */
RCPP_FUNCTION_VOID_2( Message__serialize_to_file, Rcpp::XPtr<GPB::Message> message, const char* filename){
	
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
RCPP_FUNCTION_1( Rcpp::RawVector, Message__get_payload, Rcpp::XPtr<GPB::Message> message ){

	/* create a raw vector of the appropriate size */
	int size = message->ByteSize() ;
	Rcpp::RawVector payload( size ) ;
	
	/* fill the array */
	message->SerializePartialToArray( payload.begin(), size ); 
	
	return( payload ) ;
}

RCPP_XP_METHOD_VOID_0(Message__clear, GPB::Message, Clear )

/**
 * Clear a field of a message
 *
 * @param xp (GPB::Message*) external pointer
 * @param field name or tag of the field
 */
RCPP_FUNCTION_VOID_1(Message__clear_field, Rcpp::XPtr<GPB::Message> m, SEXP field ){
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( m, field ) ;
	const GPB::Reflection* ref = m->GetReflection(); 
	ref->ClearField( m, field_desc ) ;
}


/**
 * @param xp external pointer to a Message
 * @return the message as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, Message__as_list, Rcpp::XPtr<GPB::Message> message ){
    
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
RCPP_FUNCTION_1(int, Message__length, Rcpp::XPtr<GPB::Message> message){
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
RCPP_FUNCTION_1(S4_Descriptor, Message__descriptor, Rcpp::XPtr<GPB::Message> message ){
	return( message->GetDescriptor() ) ;
}



}

