#include "rprotobuf.h"
#include "connections.h"

namespace rprotobuf{

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
SEXP getMessagePayload( SEXP xp ){
	           
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
	
	int size = message->ByteSize() ;
	SEXP payload = PROTECT( Rf_allocVector( RAWSXP, size) );
	
	io::ArrayOutputStream raw_output( RAW(payload), size ); 
	io::CodedOutputStream stream(&raw_output);

	message->SerializeWithCachedSizes( &stream ); 
	
	UNPROTECT(1); /* payload */ 
	return( payload ) ;
}

/** 
 * serialize a message to a file
 *
 * @param xp external pointer to a Message*
 * @param filename file name where to serialize
 */
SEXP serializeMessageToFile( SEXP xp, SEXP filename ){
	
	Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ); 
	
	/* open the file in binary mode to write */
	/* we make sure in the R side that filename is the full path of the file */
	int file = open( CHAR(STRING_ELT(filename, 0 )), 
		O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666); 
	
	/* using partial to allow partially filled messages */
	message->SerializePartialToFileDescriptor( file ) ;
	
	close( file ) ; 
	
	return( R_NilValue ); 
}

} // namespace rprotobuf

