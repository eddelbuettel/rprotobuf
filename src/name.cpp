#include "rprotobuf.h"

namespace rprotobuf{

SEXP name_descriptor( SEXP xp, SEXP full ){
	Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_field_descriptor( SEXP xp, SEXP full ){
	FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_enum_descriptor( SEXP xp, SEXP full ){
	EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_service_descriptor( SEXP xp, SEXP full ){
	ServiceDescriptor* d = (ServiceDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_method_descriptor( SEXP xp, SEXP full ){
	MethodDescriptor* d = (MethodDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_file_descriptor( SEXP xp ){
	FileDescriptor* d = (FileDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

} // namespace rprotobuf

