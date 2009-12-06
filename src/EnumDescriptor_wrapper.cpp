#include "rprotobuf.h"

namespace rprotobuf{

	SEXP EnumDescriptor_length(SEXP xp){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->value_count() ) ;
	}
	
	SEXP EnumDescriptor__value_count(SEXP xp){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->value_count() ) ;
	}
	
	SEXP EnumDescriptor_getValueByIndex(SEXP xp, SEXP index){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const GPB::EnumValueDescriptor* evd = d->value(i); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd ); 
	}
	
	SEXP EnumDescriptor_getValueByNumber(SEXP xp, SEXP number){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		int num = INTEGER(number)[0] ;
		const GPB::EnumValueDescriptor* evd = d->FindValueByNumber(num); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd );
	}
	
	SEXP EnumDescriptor_getValueByName(SEXP xp, SEXP name){
		GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const GPB::EnumValueDescriptor* evd = d->FindValueByName(nam); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd );
	}
	
} // namespace rprotobuf
