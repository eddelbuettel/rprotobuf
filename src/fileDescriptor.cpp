#include "rprotobuf.h"

namespace rprotobuf{

	/**
	 * get the fileDescriptor associated with a message
	 */
	SEXP get_message_file_descriptor(SEXP xp){
		GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP( xp ) ;
		return new_RS4_FileDescriptor( message->GetDescriptor()->file() ); 
	}
	
	/**
	 * get the fileDescriptor associated with a message descriptor
	 */
	SEXP get_descriptor_file_descriptor(SEXP xp){
		GPB::Descriptor* desc = (GPB::Descriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->file() ); 
	}
	
	/**
	 * get the fileDescriptor associated with an enum descriptor
	 */
	SEXP get_enum_file_descriptor(SEXP xp){
		GPB::EnumDescriptor* desc = (GPB::EnumDescriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->file() ); 
	}
	
	/**
	 * get the fileDescriptor associated with a field descriptor
	 */
	SEXP get_field_file_descriptor(SEXP xp){
		GPB::FieldDescriptor* desc = (GPB::FieldDescriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->file() ); 
	}
	
	/**
	 * get the fileDescriptor associated with a service descriptor
	 */
	SEXP get_service_file_descriptor(SEXP xp){
		GPB::ServiceDescriptor* desc = (GPB::ServiceDescriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->file() ); 
	}
	
	/**
	 * get the fileDescriptor associated with a service descriptor
	 */
	SEXP get_method_file_descriptor(SEXP xp){
		GPB::MethodDescriptor* desc = (GPB::MethodDescriptor*) EXTPTR_PTR( xp ) ;
		return new_RS4_FileDescriptor( desc->service()->file() ); 
	}
	
	
} // namespace rprotobuf
