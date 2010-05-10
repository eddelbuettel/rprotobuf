#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(MethodDescriptor__,__NAME__)

RCPP_XP_METHOD_0( METHOD(as_character)     , GPB::MethodDescriptor    , DebugString)

RCPP_FUNCTION_1(S4_MethodDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::MethodDescriptor> d ){
	GPB::MethodDescriptorProto* message = new GPB::MethodDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}
	
RCPP_FUNCTION_1( S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::MethodDescriptor> desc){
	return S4_FileDescriptor( desc->service()->file() ); 
}
	
RCPP_FUNCTION_1( S4_Descriptor, METHOD(input_type) , Rcpp::XPtr<GPB::MethodDescriptor> method){
	return method->input_type() ;
}
RCPP_FUNCTION_1( S4_Descriptor, METHOD(output_type), Rcpp::XPtr<GPB::MethodDescriptor> method){
	return method->output_type() ;
}

RCPP_FUNCTION_1( S4_Message, get_method_input_prototype, Rcpp::XPtr<GPB::MethodDescriptor> method ){
	const GPB::Descriptor* desc = method->input_type();
	return S4_Message( PROTOTYPE( desc ) ) ;
}

RCPP_FUNCTION_1( S4_Message, get_method_output_prototype, Rcpp::XPtr<GPB::MethodDescriptor> method ){
	const GPB::Descriptor* desc = method->output_type();
	return S4_Message( PROTOTYPE( desc ) ) ;
}

RCPP_FUNCTION_2(bool, valid_input_message, Rcpp::XPtr<GPB::MethodDescriptor> method, Rcpp::XPtr<GPB::Message> message){
	return message->GetDescriptor() == method->input_type() ;
}

RCPP_FUNCTION_2(bool, valid_output_message, Rcpp::XPtr<GPB::MethodDescriptor> method, Rcpp::XPtr<GPB::Message> message){
	return message->GetDescriptor() == method->output_type() ;
}

RCPP_FUNCTION_2( std::string, METHOD(name), Rcpp::XPtr<GPB::MethodDescriptor> d, bool full){
	return full ? d->full_name() : d->name() ;
}

#undef METHOD

} // namespace rprotobuf
