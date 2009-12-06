#include "rprotobuf.h"
#include "RconnectionCopyingInputStream.h"

namespace rprotobuf{

/**
 * read a message from a file
 * 
 * @param xp external pointer to a Descriptor*
 * @param filename full path of the file to read
 * 
 * @return a new "Message" S4 instance
 */
SEXP readMessageFromFile( SEXP xp, SEXP filename ){
	
	Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_XP( xp ); 
	
	/* open the file to read in binary mode */
	int file = open( CHAR(STRING_ELT(filename, 0 )), O_RDONLY | O_BINARY);
	
	/* create a prototype of the message we are going to read */
	Message * message = (Message*)MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
	
	/* read the message from the file */
	message->ParsePartialFromFileDescriptor( file ); 
	close( file ) ;
	return( new_RS4_Message_( message ) ) ;
	
}

/**
 * read a message from a binary connection
 * 
 * @param xp external pointer to a Descriptor*
 * @param con connection id
 *
 */ 
SEXP readMessageFromConnection( SEXP xp, SEXP con ){
	
	Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_XP( xp ); 
	
	int conn_id = INTEGER(con)[0] ;
	
	RconnectionCopyingInputStream wrapper( conn_id ) ;
	io::CopyingInputStreamAdaptor stream( &wrapper, 1024 ) ;
	io::CodedInputStream coded_stream(&stream ) ;
	
	/* create a prototype of the message we are going to read */
	Message * message = PROTOTYPE( desc ) ; 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
	
	message->MergePartialFromCodedStream( &coded_stream ) ;
	return( new_RS4_Message_( message ) ) ;
}

/**
 * read a message from its payload
 *
 * @param xp (Descriptor*) external pointer
 * @param raw the payload of the message
 */
SEXP readMessageFromRawVector( SEXP xp, SEXP raw){
	
	Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_XP( xp ); 
	
	io::ArrayInputStream ais( (void*)RAW(raw), LENGTH(raw) ); 
	io::CodedInputStream stream( &ais ) ; 
	
	Message * message = PROTOTYPE( desc ) ; 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
	
	message->MergePartialFromCodedStream( &stream ) ;
	return( new_RS4_Message_( message ) ) ;
}



} // namespace rprotobuf
