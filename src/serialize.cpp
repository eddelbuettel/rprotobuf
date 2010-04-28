#include "rprotobuf.h"
#include "connections.h"

namespace rprotobuf{

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
RCPP_FUNCTION_1( Rcpp::RawVector, getMessagePayload, Rcpp::XPtr<GPB::Message> message ){

	/* create a raw vector of the appropriate size */
	int size = message->ByteSize() ;
	Rcpp::RawVector payload( size ) ;
	
	/* fill the array */
	message->SerializePartialToArray( payload.begin(), size ); 
	
	return( payload ) ;
}

/** 
 * serialize a message to a file
 *
 * @param xp external pointer to a GPB::Message*
 * @param filename file name where to serialize
 */
RCPP_FUNCTION_VOID_2( serializeMessageToFile, Rcpp::XPtr<GPB::Message> message, const char* filename){
	
	/* open the file in binary mode to write */
	/* we make sure in the R side that filename is the full path of the file */
	int file = open( filename, 
		O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666); 
	
	/* using partial to allow partially filled messages */
	message->SerializePartialToFileDescriptor( file ) ;
	
	close( file ) ; 
}

} // namespace rprotobuf

