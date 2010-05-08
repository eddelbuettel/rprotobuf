#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(EnumValueDescriptor__,__NAME__)

RCPP_XP_METHOD_0( METHOD(as_character) , GPB::EnumValueDescriptor , DebugString) ;

RCPP_FUNCTION_1(S4_EnumValueDescriptor, METHOD(as_Message) , Rcpp::XPtr<GPB::EnumValueDescriptor> d ){
	GPB::EnumValueDescriptorProto* message = new GPB::EnumValueDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}
		
#undef METHOD

} // namespace rprotobuf
