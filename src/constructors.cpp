#include "rprotobuf.h"

namespace rprotobuf{

/**
 * Creates an R object of S4 class Descriptor
 * from a google::protobuf::Descriptor pointer
 * 
 * @param d Descriptor
 * 
 * @return a new "Descriptor" R object holding the 
 * descriptor as an external pointer
 */
SEXP new_RS4_Descriptor( const GPB::Descriptor*  d ){
	
	NEW_S4_OBJECT( "Descriptor") ;
  	
	/* grab the fully qualified name of the message type */
  	SEXP name  = PROTECT( Rf_mkString( d->full_name().c_str() ) ) ; 
	
  	/* 
  		we don't protect anything with this xp, and we do not need 
  		a finalizer since the object belongs to the DescriptorPool
  		it comes from
  	*/
  	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)d , R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("type"), name ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(3) ; /* oo, name, ptr */
	
	return oo; 
}

/**
 * Creates an new R object of S4 class "FieldDescriptor"
 *
 * @param fd pointer to a google::protobuf::FieldDescriptor
 *
 * @return a new "FieldDescriptor" R object
 */
SEXP new_RS4_FieldDescriptor( const GPB::FieldDescriptor*  fd ){
	
	NEW_S4_OBJECT( "FieldDescriptor") ;
  	
  	/* grab the short name of the field */
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	
	/* grab the full name */
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	
	/* hold the FieldDescriptor as an external pointer */
	/* no need for a finalizer, the object belongs to the DescriptorPool */
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
 * Creates a new "EnumDescriptor" R S4 object
 *
 * @param fd pointer to a google::protobuf::EnumDescriptor
 *
 * @return a new "EnumDescriptor" holding the 
 * EnumDescriptor as an external pointer
 */
SEXP new_RS4_EnumDescriptor( const GPB::EnumDescriptor* fd ){
	
	NEW_S4_OBJECT( "EnumDescriptor") ;
  	
	/* the simple name of the enum */
	SEXP name  = PROTECT( Rf_mkString( fd->name().c_str() ) ) ; 
	
	/* the full name */
	SEXP fname = PROTECT( Rf_mkString( fd->full_name().c_str() ) ) ;
	
	/* external pointer to the EnumDescriptor */
	/* no need for a finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
	
	/* message type where the enum is defined */
	const GPB::Descriptor *type_desc = fd->containing_type() ;
	SEXP type = R_NilValue ; 
	if( type_desc ){
		type = PROTECT( Rf_mkString( type_desc->full_name().c_str() ) ) ;
	} else{
		type = PROTECT( Rf_allocVector( STRSXP, 0 ) ) ;
	}
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("full_name"), fname ) ;
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(5) ; /* oo, name, fname, ptr, type */
	
	return oo; 
}

/**
 * Creates a new "ServiceDescriptor" R S4 object
 *
 * @param fd pointer to a google::protobuf::ServiceDescriptor
 *
 * @return a new "ServiceDescriptor" holding the 
 * ServiceDescriptor as an external pointer
 */
SEXP new_RS4_ServiceDescriptor( const GPB::ServiceDescriptor*  sd ){
	
	NEW_S4_OBJECT( "ServiceDescriptor" ) ;
  	
	/* the simple name of the enum */
	SEXP name  = PROTECT( Rf_mkString( sd->full_name().c_str() ) ) ; 
	
	/* external pointer to the ServiceDescriptor */
	/* no need for a finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)sd , 
		R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("name"), name ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(3) ; /* oo, name,ptr */
	
	return oo; 
}

/**
 * Creates a new MethodDescriptor R S4 object
 *
 * @param fd pointer to a google::protobuf::MethodDescriptor
 *
 * @return a new  holding the 
 * MethodDescriptor as an external pointer
 */
SEXP new_RS4_MethodDescriptor( const GPB::MethodDescriptor*  md ){
	
	NEW_S4_OBJECT( "MethodDescriptor" ) ;
  	
	/* the full name */
	SEXP fname = PROTECT( Rf_mkString( md->full_name().c_str() ) ) ;
	
	/* external pointer to the EnumDescriptor */
	/* no need for a finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)md , 
		R_NilValue, R_NilValue));
	
	/* message type where the enum is defined */
	SEXP service  = PROTECT( Rf_mkString( md->service()->full_name().c_str() ) ) ;
	
	SET_SLOT( oo, Rf_install("name"), fname ) ;
	SET_SLOT( oo, Rf_install("service"), service ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT(4) ; /* oo, fname, ptr, service */
	
	return oo; 
}

SEXP new_RS4_FileDescriptor( const GPB::FileDescriptor*  fd ){
	
	NEW_S4_OBJECT( "FileDescriptor" ) ;
  	
	/* no need for a finalizer */
  	SEXP ptr = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
  	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
  	UNPROTECT(2) ; /* oo, ptr */
	
	return oo; 
}

SEXP new_RS4_EnumValueDescriptor( const GPB::EnumValueDescriptor*  fd ){
	
	NEW_S4_OBJECT( "EnumValueDescriptor" ) ;
  	
	/* no need for a finalizer */
  	SEXP ptr = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
  	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
  	UNPROTECT(2) ; /* oo, ptr */
	
	return oo; 
}

} // namespace rprotobuf

