#include "rprotobuf.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{


SEXP new_RS4_Descriptor( const Descriptor * d ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufDescriptor")) );
  	if (!Rf_inherits(oo, "protobufDescriptor"))
  	  Rf_error("unable to create 'protobufDescriptor' S4 object");
  	
  	SEXP name  = PROTECT( Rf_mkString( d->full_name().c_str() ) ) ; 
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)d , 
		R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("type"), name ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(3) ; /* oo, name, ptr */
	
	return oo; 
}


SEXP new_RS4_FieldDescriptor( const FieldDescriptor * fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufFieldDescriptor")) );
  	if (!Rf_inherits(oo, "protobufFieldDescriptor"))
  	  Rf_error("unable to create 'protobufFieldDescriptor' S4 object");
 
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	SEXP type  = PROTECT( Rf_mkString( fd->containing_type()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("full_name"), fname ) ;
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr */
	
	return oo; 
}


SEXP new_RS4_EnumDescriptor( const EnumDescriptor * fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufEnumDescriptor")) );
  	if (!Rf_inherits(oo, "protobufEnumDescriptor"))
  	  Rf_error("unable to create 'protobufEnumDescriptor' S4 object");
 
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	SEXP type  = PROTECT( Rf_mkString( fd->containing_type()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("full_name"), fname ) ;
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr */
	
	return oo; 
}



} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

