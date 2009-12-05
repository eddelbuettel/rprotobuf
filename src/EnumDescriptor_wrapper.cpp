#include "rprotobuf.h"

namespace rprotobuf{

	SEXP EnumDescriptor_length(SEXP xp){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->value_count() ) ;
	}
	
	SEXP EnumDescriptor__value_count(SEXP xp){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->value_count() ) ;
	}
	
	SEXP EnumDescriptor_getValueByIndex(SEXP xp, SEXP index){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const EnumValueDescriptor* evd = d->value(i); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd ); 
	}
	
	SEXP EnumDescriptor_getValueByNumber(SEXP xp, SEXP number){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		int num = INTEGER(number)[0] ;
		const EnumValueDescriptor* evd = d->FindValueByNumber(num); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd );
	}
	
	SEXP EnumDescriptor_getValueByName(SEXP xp, SEXP name){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const EnumValueDescriptor* evd = d->FindValueByName(nam); 
		if( !evd ) return R_NilValue ;
		return new_RS4_EnumValueDescriptor( evd );
	}
	
} // namespace rprotobuf
