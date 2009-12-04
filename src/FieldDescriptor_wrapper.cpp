#include "rprotobuf.h"

namespace rprotobuf {

	SEXP FieldDescriptor_is_extension(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarLogical( d->is_extension() ) ;
	}
	
	SEXP FieldDescriptor_number(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->number() ) ;
	}
	
} // namespace rprotobuf

