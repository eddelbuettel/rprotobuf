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
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("Descriptor")) );
  	if (!Rf_inherits(oo, "Descriptor"))
  	  throwException("unable to create 'Descriptor' S4 object", "CannotCreateObjectException" );
  	
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
 * Creates an new R object of S4 class "FieldDescriptor"
 *
 * @param fd pointer to a google::protobuf::FieldDescriptor
 *
 * @return a new "FieldDescriptor" R object
 */
SEXP new_RS4_FieldDescriptor( const GPB::FieldDescriptor*  fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("FieldDescriptor")) );
  	if (!Rf_inherits(oo, "FieldDescriptor"))
  		throwException("unable to create 'FieldDescriptor' S4 object", "CannotCreateObjectException" );
  	
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
 * Creates a new "EnumDescriptor" R S4 object
 *
 * @param fd pointer to a google::protobuf::EnumDescriptor
 *
 * @return a new "EnumDescriptor" holding the 
 * EnumDescriptor as an external pointer
 */
SEXP new_RS4_EnumDescriptor( const GPB::EnumDescriptor* fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("EnumDescriptor")) );
  	if (!Rf_inherits(oo, "EnumDescriptor"))
  		throwException( "unable to create 'EnumDescriptor' S4 object", "CannotCreateObjectException" );
 
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
 * @return a new R S4 object of class "Message"
 * holding the Message pointer as an external pointer
 */
SEXP new_RS4_Message( const GPB::Message* message, SEXP type ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("Message")) );
  	if (!Rf_inherits(oo, "Message"))
  		throwException( "unable to create 'Message' S4 object", "CannotCreateObjectException" );
  	
  	/* external pointer to the Message */
	/* TODO: finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)message , 
		R_NilValue, R_NilValue));
	
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT( 2) ; /* ptr, oo */
	return( oo ); 
	
}

/* same as above, but get the type from the message */
SEXP new_RS4_Message_( const GPB::Message* message ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("Message")) );
  	if (!Rf_inherits(oo, "Message"))
  	  throwException("unable to create 'Message' S4 object", "CannotCreateObjectException" );
  	
  	/* external pointer to the Message */
	/* TODO: finalizer */
	SEXP ptr   = PROTECT( R_MakeExternalPtr( (void*)message , 
		R_NilValue, R_NilValue));
	
	/* the message type */
	SEXP type = PROTECT( Rf_mkString( message->GetDescriptor()->full_name().c_str() )) ;
	
	SET_SLOT( oo, Rf_install("type"), type ) ;
	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
	UNPROTECT( 3) ; /* ptr, oo, type */
	return( oo ); 
	
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
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("ServiceDescriptor")) );
  	if (!Rf_inherits(oo, "ServiceDescriptor"))
  		throwException( "unable to create 'ServiceDescriptor' S4 object", "CannotCreateObjectException" );
 
  	/* the simple name of the enum */
	SEXP name  = PROTECT( Rf_mkString( sd->full_name().c_str() ) ) ; 
	
	/* external pointer to the ServiceDescriptor */
	/* TODO: finalizer */
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
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("MethodDescriptor")) );
  	if (!Rf_inherits(oo, "MethodDescriptor" ))
  		throwException( "unable to create 'MethodDescriptor' S4 object", "CannotCreateObjectException" );
 
  	/* the full name */
	SEXP fname = PROTECT( Rf_mkString( md->full_name().c_str() ) ) ;
	
	/* external pointer to the EnumDescriptor */
	/* TODO: finalizer */
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
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("FileDescriptor")) );
	if (!Rf_inherits(oo, "FileDescriptor"))
  		throwException( "unable to create 'FileDescriptor' S4 object", "CannotCreateObjectException" );
  	
  	SEXP ptr = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
  	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
  	UNPROTECT(2) ; /* oo, ptr */
	
	return oo; 
}

SEXP new_RS4_EnumValueDescriptor( const GPB::EnumValueDescriptor*  fd ){
	
	SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("EnumValueDescriptor")) );
  	if (!Rf_inherits(oo, "EnumValueDescriptor"))
  		throwException( "unable to create 'EnumValueDescriptor' S4 object", "CannotCreateObjectException" );
  	
  	SEXP ptr = PROTECT( R_MakeExternalPtr( (void*)fd , 
		R_NilValue, R_NilValue));
  	SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
	
  	UNPROTECT(2) ; /* oo, ptr */
	
	return oo; 
}

} // namespace rprotobuf

