#include "rprotobuf.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

/**
 * Creates an R object of S4 class protobufDescriptor
 * from a google::protobuf::Descriptor pointer
 * 
 * @param d Descriptor
 * 
 * @return a new "protobufDescriptor" R object holding the 
 * descriptor as an external pointer
 */
SEXP new_RS4_Descriptor( const Descriptor * d ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufDescriptor")) );
  	if (!Rf_inherits(oo, "protobufDescriptor"))
  	  Rf_error("unable to create 'protobufDescriptor' S4 object");
  	
	/* grab the fully qualified name of the message type */
  	SEXP name  = PROTECT( Rf_mkString( d->full_name().c_str() ) ) ; 
	SEXP ptr   = PROTECT( /* TODO: finalizer */
		R_MakeExternalPtr( (void*)d , R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("type"), name ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(3) ; /* oo, name, ptr */
	
	return oo; 
}

/**
 * Creates an new R object of S4 class "protobufFieldDescriptor"
 *
 * @param fd pointer to a google::protobuf::FieldDescriptor
 *
 * @return a new "protobufFieldDescriptor" R object
 */
SEXP new_RS4_FieldDescriptor( const FieldDescriptor * fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufFieldDescriptor")) );
  	if (!Rf_inherits(oo, "protobufFieldDescriptor"))
  	  Rf_error("unable to create 'protobufFieldDescriptor' S4 object");
  	
  	/* grab the short name of the field */
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	
	/* grab the full name */
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	
	/* hold the FieldDescriptor as an external pointer */
	/* TODO: finalizer strategy */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	
	/* the fully qualified TYPE associated with this field descriptor */
	SEXP type  = PROTECT( Rf_mkString( fd->containing_type()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("full_name"), fname ) ;
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr, type */
	
	return oo; 
}

/**
 * Creates a new "protobufEnumDescriptor" R S4 object
 *
 * @param fd pointer to a google::protobuf::EnumDescriptor
 *
 * @return a new "protobufEnumDescriptor" holding the 
 * EnumDescriptor as an external pointer
 */
SEXP new_RS4_EnumDescriptor( const EnumDescriptor * fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufEnumDescriptor")) );
  	if (!Rf_inherits(oo, "protobufEnumDescriptor"))
  	  Rf_error("unable to create 'protobufEnumDescriptor' S4 object");
 
  	/* the simple name of the enum */
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	
	/* the full name */
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	
	/* external pointer to the EnumDescriptor */
	/* TODO: finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	
	/* message type where the enum is defined */
	SEXP type  = PROTECT( Rf_mkString( fd->containing_type()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("full_name"), fname ) ;
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr, type */
	
	return oo; 
}

/**
 * @param pointer to a google::protobuf::Message
 * @param type type of the message, as a STRSXP
 *
 * @return a new R S4 object of class "protobufMessage"
 * holding the Message pointer as an external pointer
 */
SEXP new_RS4_Message( const Message* message, SEXP type ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("protobufMessage")) );
  	if (!Rf_inherits(oo, "protobufMessage"))
  	  Rf_error("unable to create 'protobufMessage' S4 object");
  	
  	/* external pointer to the Message */
	/* TODO: finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)message , 
		R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT( 2) ; /* ptr, oo */
	return( oo ); 
	
}

} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

