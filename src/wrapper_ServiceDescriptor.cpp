#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(ServiceDescriptor__,__NAME__)	
	
	RCPP_XP_METHOD_0( METHOD(length),GPB::ServiceDescriptor, method_count )
	RCPP_XP_METHOD_0( METHOD(method_count),GPB::ServiceDescriptor, method_count )
	
	RCPP_XP_METHOD_CAST_1( METHOD(getMethodByIndex) , GPB::ServiceDescriptor , method          , S4_MethodDescriptor ) 
	RCPP_XP_METHOD_CAST_1( METHOD(getMethodByName)  , GPB::ServiceDescriptor , FindMethodByName, S4_MethodDescriptor ) 

	/**
	 * @param xp (GPB::ServiceDescriptor*) external pointer
	 * @return the descriptor as an R list
	 */
	RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::ServiceDescriptor> desc ){
		Rcpp::CharacterVector names = getServiceDescriptorMethodNames(desc) ; 
		int n = names.size() ;
		
		Rcpp::List res(n); 
		for( int i=0; i<n; i++){
			res[i] = S4_MethodDescriptor( desc->method(i) ); 
		}
		res.names() = names ;
		return res; 
	}

	RCPP_FUNCTION_1(S4_ServiceDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::ServiceDescriptor> d ){
		GPB::ServiceDescriptorProto* message = new GPB::ServiceDescriptorProto() ; 
		d->CopyTo( message ); 
		return message ;
	}
	
	

#undef METHOD

} // namespace rprotobuf
