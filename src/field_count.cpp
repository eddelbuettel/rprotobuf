#include "rprotobuf.h"

namespace rprotobuf {

	SEXP field_count__Descriptor( SEXP xp ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->field_count() ) ; 
	}

} // namespace rprotobuf

