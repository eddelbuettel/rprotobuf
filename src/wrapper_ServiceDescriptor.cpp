#include "rprotobuf.h"

namespace rprotobuf{

	RCPP_XP_METHOD_0(ServiceDescriptor_length,GPB::ServiceDescriptor, method_count )
	RCPP_XP_METHOD_0(ServiceDescriptor_method_count,GPB::ServiceDescriptor, method_count )
	
	RCPP_XP_METHOD_CAST_1(ServiceDescriptor_getMethodByIndex , GPB::ServiceDescriptor , method          , S4_MethodDescriptor ) 
	RCPP_XP_METHOD_CAST_1(ServiceDescriptor_getMethodByName  , GPB::ServiceDescriptor , FindMethodByName, S4_MethodDescriptor ) 
	
} // namespace rprotobuf
