#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(ServiceDescriptor__,__NAME__)	
	
	RCPP_XP_METHOD_0( METHOD(length),GPB::ServiceDescriptor, method_count )
	RCPP_XP_METHOD_0( METHOD(method_count),GPB::ServiceDescriptor, method_count )
	RCPP_XP_METHOD_0( METHOD(as_character)    , GPB::ServiceDescriptor   , DebugString)
	
	RCPP_XP_METHOD_CAST_1( METHOD(getMethodByIndex) , GPB::ServiceDescriptor , method          , S4_MethodDescriptor ) 
	RCPP_XP_METHOD_CAST_1( METHOD(getMethodByName)  , GPB::ServiceDescriptor , FindMethodByName, S4_MethodDescriptor ) 

	RCPP_FUNCTION_1( Rcpp::CharacterVector, METHOD(getMethodNames), Rcpp::XPtr<GPB::ServiceDescriptor> desc){
		int nmeths  = desc->method_count() ;
		Rcpp::CharacterVector res( nmeths );
		
		for( int i=0; i<nmeths; i++){
			res[i] = desc->method(i)->name() ;
		}
		return res ;
	}
	
	/**
	 * @param xp (GPB::ServiceDescriptor*) external pointer
	 * @return the descriptor as an R list
	 */
	RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::ServiceDescriptor> desc ){
		int n = desc->method_count() ;
		
		Rcpp::CharacterVector names(n) ; 
		Rcpp::List res(n); 
		for( int i=0; i<n; i++){
			const GPB::MethodDescriptor* met = desc->method(i) ;
			res[i] = S4_MethodDescriptor( met );
			names[i] = met->name() ;
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
