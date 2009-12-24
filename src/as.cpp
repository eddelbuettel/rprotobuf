#include "rprotobuf.h"

//namespace rcpp{
//	template class external_pointer<GPB::Descriptor>;
//}

namespace rprotobuf{
	
	// later
	// SEXP asMessage_Descriptor( rcpp::external_pointer<GPB::Descriptor> xp ){
	// 	Rprintf( "xp.pointer = %p\n", xp.getPointer() ) ;
	// 	// GPB::Descriptor* d = xp.getPointer() ;
	// 	// Rprintf( "pointer = %d\n" , d ) ;
	// 	return R_NilValue ;
	// 	// GPB::Descriptor* d = xp.getPointer() ;
	// 	// GPB::DescriptorProto* message = new GPB::DescriptorProto() ; 
	// 	// d->CopyTo( message ); 
	// 	// return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	// }
	
	SEXP asMessage_Descriptor( SEXP xp){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		GPB::DescriptorProto* message = new GPB::DescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_FieldDescriptor( SEXP xp){
		GPB::FieldDescriptor* d = (GPB::FieldDescriptor*)EXTPTR_PTR(xp) ;
		GPB::FieldDescriptorProto* message = new GPB::FieldDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_EnumDescriptor( SEXP xp){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		GPB::EnumDescriptorProto* message = new GPB::EnumDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_ServiceDescriptor( SEXP xp){
		GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
		GPB::ServiceDescriptorProto* message = new GPB::ServiceDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_MethodDescriptor( SEXP xp){
		GPB::MethodDescriptor* d = (GPB::MethodDescriptor*)EXTPTR_PTR(xp) ;
		GPB::MethodDescriptorProto* message = new GPB::MethodDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_FileDescriptor( SEXP xp){
		GPB::FileDescriptor* d = (GPB::FileDescriptor*)EXTPTR_PTR(xp) ;
		GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	SEXP asMessage_EnumValueDescriptor( SEXP xp){
		GPB::EnumValueDescriptor* d = (GPB::EnumValueDescriptor*)EXTPTR_PTR(xp) ;
		GPB::EnumValueDescriptorProto* message = new GPB::EnumValueDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
} // namespace rprotobuf
