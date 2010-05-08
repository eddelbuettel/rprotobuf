#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(MethodDescriptor__,__NAME__)

RCPP_FUNCTION_1(S4_MethodDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::MethodDescriptor> d ){
	GPB::MethodDescriptorProto* message = new GPB::MethodDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}
	
	
#undef METHOD

} // namespace rprotobuf
