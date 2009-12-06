#include "rprotobuf.h"

namespace rprotobuf{

	SEXP ServiceDescriptor_length(SEXP xp){
		GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->method_count() ) ;
	}
	
	SEXP ServiceDescriptor_method_count(SEXP xp){
		GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->method_count() ) ;
	}
	
	SEXP ServiceDescriptor_getMethodByIndex(SEXP xp, SEXP index){
		GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const GPB::MethodDescriptor* md = d->method(i); 
		if( !md ) return R_NilValue ;
		return new_RS4_MethodDescriptor( md ); 
	}
	
	SEXP ServiceDescriptor_getMethodByName(SEXP xp, SEXP name){
		GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const GPB::MethodDescriptor* md = d->FindMethodByName(nam); 
		if( !md ) return R_NilValue ;
		return new_RS4_MethodDescriptor( md );
	}
	
} // namespace rprotobuf
