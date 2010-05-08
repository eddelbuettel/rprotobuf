#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(EnumValueDescriptor__,__NAME__)
	
RCPP_FUNCTION_1(S4_EnumValueDescriptor, asMessage_EnumValueDescriptor, Rcpp::XPtr<GPB::EnumValueDescriptor> d ){
	GPB::EnumValueDescriptorProto* message = new GPB::EnumValueDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}
		
#undef METHOD

} // namespace rprotobuf
