#include "rprotobuf.h"

namespace rprotobuf{

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
SEXP getMessagePayload( SEXP xp ){
	           
	SEXP payload = PROTECT( Rf_allocVector( RAWSXP, 0) ); 
	/* TODO: implement */
	Rf_warning( "serialization not implemented yet" ) ;
	
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
	
	int file = open( CHAR(STRING_ELT(filename, 0 )), 
		O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666); 
	
	message->SerializeToFileDescriptor( file ) ;
	
	close( file ) ; 
	
	return( R_NilValue ); 
}


} // namespace rprotobuf

