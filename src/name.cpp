#include "rprotobuf.h"

namespace rprotobuf{

SEXP name_descriptor( SEXP xp, SEXP full ){
	GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_field_descriptor( SEXP xp, SEXP full ){
	GPB::FieldDescriptor* d = (GPB::FieldDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_enum_descriptor( SEXP xp, SEXP full ){
	GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_service_descriptor( SEXP xp, SEXP full ){
	GPB::ServiceDescriptor* d = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_method_descriptor( SEXP xp, SEXP full ){
	GPB::MethodDescriptor* d = (GPB::MethodDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

SEXP name_file_descriptor( SEXP xp ){
	GPB::FileDescriptor* d = (GPB::FileDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( d->name().c_str() ) );
	UNPROTECT(1); /* res */
	return res ;
}

} // namespace rprotobuf

