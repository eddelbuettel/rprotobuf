#include "rprotobuf.h"

namespace rprotobuf {

	SEXP FieldDescriptor_is_extension(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarLogical( d->is_extension() ) ;
	}
	
} // namespace rprotobuf

