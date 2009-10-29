#include "rprotobuf.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{


SEXP new_RS4_Descriptor( const Descriptor * d ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufDescriptor")) );
  	if (!inherits(oo, "protobufDescriptor"))
  	  error("unable to create 'protobufDescriptor' S4 object");
  	
  	SEXP name  = PROTECT( mkString( d->full_name().c_str() ) ) ; 
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)d , 
		R_NilValue, R_NilValue));
	
	SET_SLOT( oo, install("type"), name ) ;
	SET_SLOT( oo, install("pointer"), ptr ) ;
	
	UNPROTECT(3) ; /* oo, name, ptr */
	
	return oo; 
}


SEXP new_RS4_FieldDescriptor( const FieldDescriptor * fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufFieldDescriptor")) );
  	if (!inherits(oo, "protobufFieldDescriptor"))
  	  error("unable to create 'protobufFieldDescriptor' S4 object");
 
	SEXP name  = PROTECT( mkString( fd->name().c_str() ) ) ; 
	SEXP fname = PROTECT( mkString( fd->full_name().c_str() ) ) ;
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	SEXP type  = PROTECT( mkString( fd->containing_type()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, install("name"), name ) ;
	SET_SLOT( oo, install("full_name"), fname ) ;
	SET_SLOT( oo, install("type"), type ) ;
	SET_SLOT( oo, install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr */
	
	return oo; 
}


} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

