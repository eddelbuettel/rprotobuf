#include "rprotobuf.h"

namespace rprotobuf {

#define CONTAINING_TYPE(CLAZZ) CLAZZ* d = (CLAZZ*)EXTPTR_PTR(xp) ; \
	const GPB::Descriptor* parent = d->containing_type() ; \
	if( !parent ) return R_NilValue ; \
	return new_RS4_Descriptor( parent ) ;
	
	SEXP containing_type__Descriptor( SEXP xp ){
		CONTAINING_TYPE(GPB::Descriptor); 
	}
	SEXP containing_type__EnumDescriptor( SEXP xp ){
		CONTAINING_TYPE(GPB::EnumDescriptor); 
	}
	SEXP containing_type__FieldDescriptor( SEXP xp ){
		CONTAINING_TYPE(GPB::FieldDescriptor); 
	}

} // namespace rprotobuf
