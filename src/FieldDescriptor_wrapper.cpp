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
	
	SEXP FieldDescriptor_type(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->type() ) ;
	}
	
	SEXP FieldDescriptor_cpp_type(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->cpp_type() ) ;
	}
	
	
} // namespace rprotobuf

