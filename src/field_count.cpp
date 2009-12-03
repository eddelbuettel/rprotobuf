#include "rprotobuf.h"

namespace rprotobuf {

	SEXP field_count__Descriptor( SEXP xp ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->field_count() ) ; 
	}

	SEXP nested_type_count__Descriptor( SEXP xp ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->field_count() ) ; 
	}

	SEXP enum_type_count__Descriptor( SEXP xp ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->enum_type_count() ) ; 
	}

	SEXP Descriptor_getFieldByIndex( SEXP xp, SEXP index ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const FieldDescriptor* field_desc = d->field( i ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	SEXP Descriptor_getFieldByNumber( SEXP xp, SEXP number ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		int num = INTEGER(number)[0] ;
		const FieldDescriptor* field_desc = d->FindFieldByNumber( num ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	SEXP Descriptor_getFieldByName( SEXP xp, SEXP name ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const FieldDescriptor* field_desc = d->FindFieldByName( nam ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	SEXP Descriptor_getNestedTypeByIndex( SEXP xp, SEXP index ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const Descriptor* nested_desc = d->nested_type( i ) ;
		if( !nested_desc ) return R_NilValue ;
		return new_RS4_Descriptor( nested_desc ) ;
	}
	
	SEXP Descriptor_getNestedTypeByName( SEXP xp, SEXP name ){
		Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const Descriptor* nested_desc = d->FindNestedTypeByName( nam ) ;
		if( !nested_desc ) return R_NilValue ;
		return new_RS4_Descriptor( nested_desc ) ;
	}
	
	
	
} // namespace rprotobuf

