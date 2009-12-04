#include "rprotobuf.h"
#include "fieldtypes.h"

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
	
	SEXP FieldDescriptor_label(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->label() ) ;
	}
	
	SEXP FieldDescriptor_is_repeated(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarLogical( d->is_repeated() ) ;
	}
	
	SEXP FieldDescriptor_is_optional(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->is_optional() ) ;
	}
	
	SEXP FieldDescriptor_is_required(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarInteger( d->is_required() ) ;
	}
	
	SEXP FieldDescriptor_has_default_value(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		return Rf_ScalarLogical( d->has_default_value() ) ;
	}
	
	SEXP FieldDescriptor_default_value(SEXP xp){
		FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
		switch( d->cpp_type() ){
			case CPPTYPE_INT32:
				{
					return Rf_ScalarInteger( (int)d->default_value_int32() ) ;
					break ;
				}
			case CPPTYPE_INT64:
				{
					return Rf_ScalarInteger( (int)d->default_value_int64() ) ;
					break ;
				}
			case CPPTYPE_UINT32:
				{
					return Rf_ScalarInteger( (int)d->default_value_uint32() ) ;
					break ;
				}
			case CPPTYPE_UINT64:
				{
					return Rf_ScalarInteger( (int)d->default_value_uint64() ) ;
					break ;
				}
			case CPPTYPE_DOUBLE:
				{
					return Rf_ScalarReal( (double)d->default_value_double() ) ;
					break ;
				}
			case CPPTYPE_FLOAT:
				{
					return Rf_ScalarReal( (double)d->default_value_float() ) ;
					break ;
				}
			case CPPTYPE_BOOL:
				{
					return Rf_ScalarLogical(d->default_value_bool() ) ;
					break ;
				}
			case CPPTYPE_ENUM:
				{
					return Rf_ScalarInteger( d->default_value_enum()->number() ) ;
					break ;
				}
			case CPPTYPE_STRING:
				{
					return Rf_mkString( d->default_value_string().c_str() ) ;
					break ;
				}
			default: 
				break ;
		}
		return R_NilValue ;
	}
	
} // namespace rprotobuf

