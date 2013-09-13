#include "rprotobuf.h"
#include "RcppMacros.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(ServiceDescriptor__,__NAME__)	
	
	RPB_XP_METHOD_0( METHOD(length),GPB::ServiceDescriptor, method_count )
	RPB_XP_METHOD_0( METHOD(method_count),GPB::ServiceDescriptor, method_count )
	RPB_XP_METHOD_0( METHOD(as_character)    , GPB::ServiceDescriptor   , DebugString)
	
	RPB_XP_METHOD_CAST_1( METHOD(getMethodByIndex) , GPB::ServiceDescriptor , method          , S4_MethodDescriptor ) 
	RPB_XP_METHOD_CAST_1( METHOD(getMethodByName)  , GPB::ServiceDescriptor , FindMethodByName, S4_MethodDescriptor ) 

	RPB_FUNCTION_1( Rcpp::CharacterVector, METHOD(getMethodNames), Rcpp::XPtr<GPB::ServiceDescriptor> desc){
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
	RPB_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::ServiceDescriptor> desc ){
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

	RPB_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::ServiceDescriptor> d ){
		GPB::ServiceDescriptorProto* message = new GPB::ServiceDescriptorProto() ; 
		d->CopyTo( message ); 
		return S4_Message( message ) ;
	}
	
	RPB_FUNCTION_1( S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::ServiceDescriptor> desc){
		return S4_FileDescriptor( desc->file() ); 
	}
	
	RPB_FUNCTION_2( std::string, METHOD(name), Rcpp::XPtr<GPB::ServiceDescriptor> d, bool full){
		return full ? d->full_name() : d->name() ;
	}
	

/**
 * extract a method descriptor from a service descriptor using its
 * name or position
 *
 * @param pointer (GPB::ServiceDescriptor*) external pointer
 * @param name name or position of the method
 */
SEXP get_service_method( SEXP pointer, SEXP name ){

	/* grab the Message pointer */
	Rcpp::XPtr<GPB::ServiceDescriptor> desc(pointer) ;

	GPB::MethodDescriptor* method_desc = static_cast<GPB::MethodDescriptor*>(0);
	
	switch( TYPEOF( name) ){
	case STRSXP:
		{
			/* what we are looking for */
			const char * what = CHAR( STRING_ELT(name, 0 ) ) ;
			
			/* the method descriptor */
			method_desc = (GPB::MethodDescriptor*)desc->FindMethodByName( what ) ;
			
			break ;
		}
	case REALSXP:
		{
			
			/* the method descriptor */
			method_desc = (GPB::MethodDescriptor*)desc->method( (int)REAL(name)[0] ) ;
			
			break ;
		}
	case INTSXP: 
		{
			/* the method descriptor */
			method_desc = (GPB::MethodDescriptor*)desc->method( INTEGER(name)[0] ) ;
			
			break ;
		}
	}
	
	if( !method_desc ){
		throwException( "could not get MethodDescriptor", "NoSuchMethodException" ) ;
	}
	
	return S4_MethodDescriptor( method_desc ); 
	
}

#undef METHOD

} // namespace rprotobuf
