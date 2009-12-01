#include "rprotobuf.h"

namespace rprotobuf{

	/**
	 * get the fileDescriptor associated with a message
	 */
	SEXP get_message_file_descriptor(SEXP xp){
		Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
		return new_RS4_FileDescriptor( message->GetDescriptor()->file() ); 
	}
	
	SEXP get_descriptor_file_descriptor(SEXP xp){
		Descriptor* desc = (Descriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->file() ); 
	}
	
	
} // namespace rprotobuf
