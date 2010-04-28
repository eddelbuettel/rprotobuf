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


}

