#include "rprotobuf.h"

namespace rprotobuf{
	
	SEXP asMessage_Descriptor( SEXP xp){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		DescriptorProto* message = new DescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
	SEXP asMessage_FieldDescriptor( SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		FieldDescriptorProto* message = new FieldDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
	SEXP asMessage_EnumDescriptor( SEXP xp){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		EnumDescriptorProto* message = new EnumDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
	SEXP asMessage_ServiceDescriptor( SEXP xp){
		ServiceDescriptor* d = (ServiceDescriptor*)EXTPTR_PTR(xp) ;
		ServiceDescriptorProto* message = new ServiceDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
	SEXP asMessage_MethodDescriptor( SEXP xp){
		MethodDescriptor* d = (MethodDescriptor*)EXTPTR_PTR(xp) ;
		MethodDescriptorProto* message = new MethodDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
	SEXP asMessage_FileDescriptor( SEXP xp){
		FileDescriptor* d = (FileDescriptor*)EXTPTR_PTR(xp) ;
		FileDescriptorProto* message = new FileDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (Message*)message ) ) ;
	}
	
} // namespace rprotobuf
