#include "rprotobuf.h"

namespace rprotobuf{

	SEXP EnumDescriptor_length(SEXP xp){
		EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->value_count() ) ;
	}
	
} // namespace rprotobuf
