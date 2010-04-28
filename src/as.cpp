#include "rprotobuf.h"

namespace rprotobuf{

	RCPP_FUNCTION_1(SEXP, asMessage_Descriptor, Rcpp::XPtr<GPB::Descriptor> d ){
		GPB::DescriptorProto* message = new GPB::DescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_FieldDescriptor, Rcpp::XPtr<GPB::FieldDescriptor> d ){
		GPB::FieldDescriptorProto* message = new GPB::FieldDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_EnumDescriptor, Rcpp::XPtr<GPB::EnumDescriptor> d ){
		GPB::EnumDescriptorProto* message = new GPB::EnumDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_ServiceDescriptor, Rcpp::XPtr<GPB::ServiceDescriptor> d ){
		GPB::ServiceDescriptorProto* message = new GPB::ServiceDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_MethodDescriptor, Rcpp::XPtr<GPB::MethodDescriptor> d ){
		GPB::MethodDescriptorProto* message = new GPB::MethodDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_FileDescriptor, Rcpp::XPtr<GPB::FileDescriptor> d ){
		GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
	RCPP_FUNCTION_1(SEXP, asMessage_EnumValueDescriptor, Rcpp::XPtr<GPB::EnumValueDescriptor> d ){
		GPB::EnumValueDescriptorProto* message = new GPB::EnumValueDescriptorProto() ; 
		d->CopyTo( message ); 
		return( new_RS4_Message_( (GPB::Message*)message ) ) ;
	}
	
} // namespace rprotobuf
