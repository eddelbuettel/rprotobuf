#include "rprotobuf.h"

namespace rprotobuf{

/**
 * read a message from a file
 * 
 * @param xp external pointer to a Descriptor*
 * @param filename full path of the file to read
 * 
 * @return a new "protobufMessage" S4 instance
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

} // namespace rprotobuf
