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
	
	int file = open( CHAR(STRING_ELT(filename, 0 )), O_RDONLY | O_BINARY);
	
	Message * message = (Message*)MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
	
	message->ParseFromFileDescriptor( file ); 
	
	close( file ) ;
	
	return( new_RS4_Message_( message ) ) ;
	
}

} // namespace rprotobuf
