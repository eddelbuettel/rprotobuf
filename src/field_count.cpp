#include "rprotobuf.h"

namespace rprotobuf {

	SEXP field_count__Descriptor( SEXP xp ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->field_count() ) ; 
	}

	SEXP nested_type_count__Descriptor( SEXP xp ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->field_count() ) ; 
	}

	SEXP enum_type_count__Descriptor( SEXP xp ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->enum_type_count() ) ; 
	}

	SEXP Descriptor_getFieldByIndex( SEXP xp, SEXP index ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const GPB::FieldDescriptor* field_desc = d->field( i ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	SEXP Descriptor_getFieldByNumber( SEXP xp, SEXP number ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		int num = INTEGER(number)[0] ;
		const GPB::FieldDescriptor* field_desc = d->FindFieldByNumber( num ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	SEXP Descriptor_getFieldByName( SEXP xp, SEXP name ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const GPB::FieldDescriptor* field_desc = d->FindFieldByName( nam ) ;
		if( !field_desc ) return R_NilValue ;
		return new_RS4_FieldDescriptor( field_desc ) ;
	}
	
	
	SEXP Descriptor_getNestedTypeByIndex( SEXP xp, SEXP index ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const GPB::Descriptor* nested_desc = d->nested_type( i ) ;
		if( !nested_desc ) return R_NilValue ;
		return new_RS4_Descriptor( nested_desc ) ;
	}
	
	SEXP Descriptor_getNestedTypeByName( SEXP xp, SEXP name ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const GPB::Descriptor* nested_desc = d->FindNestedTypeByName( nam ) ;
		if( !nested_desc ) return R_NilValue ;
		return new_RS4_Descriptor( nested_desc ) ;
	}
	
	
	SEXP Descriptor_getEnumTypeByIndex( SEXP xp, SEXP index ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		int i = INTEGER(index)[0] ;
		const GPB::EnumDescriptor* enum_desc = d->enum_type( i ) ;
		if( !enum_desc ) return R_NilValue ;
		return new_RS4_EnumDescriptor( enum_desc ) ;
	}
	
	SEXP Descriptor_getEnumTypeByName( SEXP xp, SEXP name ){
		GPB::Descriptor* d = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
		std::string nam = CHAR( STRING_ELT(name, 0) ) ;
		const GPB::EnumDescriptor* enum_desc = d->FindEnumTypeByName( nam ) ;
		if( !enum_desc ) return R_NilValue ;
		return new_RS4_EnumDescriptor( enum_desc ) ;
	}
	
	
} // namespace rprotobuf

