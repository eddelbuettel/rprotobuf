#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(FileDescriptor__,__NAME__)

RCPP_XP_METHOD_0( METHOD(as_character)       , GPB::FileDescriptor      , DebugString) ;

RCPP_FUNCTION_1(S4_FileDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::FileDescriptor> d ){
	GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}
	
#undef METHOD

} // namespace rprotobuf
