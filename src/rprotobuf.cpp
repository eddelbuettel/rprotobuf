
#include "rprotobuf.h"

class RProtoBuf {
	
} ;



/**
 * read a proto file and cache the message definitions it contains
 *
 * @param file proto file name
 */
RcppExport SEXP readProtoFile( SEXP file ){
	
#ifdef RPB_DEBUG
Rprintf( "<readProtoFile>\n" ) ;
PrintValue( file ) ;
#endif
	
	if( TYPEOF( file) != STRSXP ){
		error( "'file must be a character vector"  );
	}

	
	
	
#ifdef RPB_DEBUG
Rprintf( "</readProtoFile>\n" ) ;
#endif

return R_NilValue ;

}



/**
 * get the descriptor associated with a message type
 *
 * @param type message type
 */
RcppExport SEXP getProtobufDescriptor( SEXP type ){

#ifdef RPB_DEBUG
Rprintf( "<getProtobufDescriptor>\n      type = " ) ;
PrintValue( type ) ;
#endif
	
	if( TYPEOF( type ) != STRSXP ){
		error( "'type' must be a character vector"  );
	}

#ifdef RPB_DEBUG
Rprintf( "</getProtobufDescriptor>\n" ) ;
#endif

	SEXP ptr ; 
	// TODO: replace 0 with some C++ pointer
	// TODO: implement the finalizer for this external pointer
	PROTECT(ptr = R_MakeExternalPtr(0, R_NilValue, R_NilValue));
	UNPROTECT(1); 
	
	return ptr ;
}


/**
 * make a new protobuf message
 *
 * @param descriptor a "protobufDescriptor" R object
 */
RcppExport SEXP newProtoMessage( SEXP descriptor ){

#ifdef RPB_DEBUG
Rprintf( "<newProtoMessage>\n" ) ;
#endif

	/* the message type */
	SEXP type = GET_SLOT( descriptor, install("type") ) ;
	
	/* the pointer to the c++ descriptor object */
	SEXP desc_ptr  = GET_SLOT( descriptor, install("pointer") ) ;

#ifdef RPB_DEBUG
PRINT_DEBUG_INFO( "type", type ) ;
PRINT_DEBUG_INFO( "desc_ptr", desc_ptr ) ;
#endif
	
	/* create the a prototype for this message and create an external pointer to it */
	SEXP p ; 
	// TODO: replace 0 with some C++ pointer
	// TODO: implement the finalizer for this external pointer
	PROTECT(p = R_MakeExternalPtr(0, R_NilValue, R_NilValue));
	UNPROTECT(1); 
	
#ifdef RPB_DEBUG
Rprintf( "</newProtoMessage>\n" ) ;
#endif

	return p ;
}


/**
 * extract a field from a message
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 *
 * @return the field called "name" of the message if the 
 *         message has the field, otherwise an error is generated
 */
RcppExport SEXP getMessageField( SEXP pointer, SEXP name ){
	
#ifdef RPB_DEBUG
Rprintf( "<getMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
#endif

	/* TODO: do something */
	

#ifdef RPB_DEBUG
Rprintf( "</getMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
}

/**
 * set a message field to a new value
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 * @param value new value for the field
 *
 * @return allways NULL, the message is modified by reference
 */
RcppExport SEXP setMessageField( SEXP pointer, SEXP name, SEXP value ){
	
#ifdef RPB_DEBUG
Rprintf( "<setMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
PRINT_DEBUG_INFO( "value", value ) ;
#endif

	/* TODO: do something */
	

#ifdef RPB_DEBUG
Rprintf( "</setMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
}

