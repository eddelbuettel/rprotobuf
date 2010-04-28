#include "rprotobuf.h"

namespace rprotobuf{

	
	RCPP_FUNCTION_1( S4_Descriptor, get_method_input_type , Rcpp::XPtr<GPB::MethodDescriptor> method){
		return method->input_type() ;
	}
	RCPP_FUNCTION_1( S4_Descriptor, get_method_output_type, Rcpp::XPtr<GPB::MethodDescriptor> method){
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
	
} // namespace rprotobuf




