#include "rprotobuf.h"

namespace rprotobuf{

/* FIXME: this has got to disappear */	
	
/**
 * create a call to throw an evaluate it
 *
 * @param message the message
 * @param subclass the subclass to use (to allow direct handlers in tryCatch)
 */
SEXP throwException( const char* message, const char* subclass ){
	
	SEXP m = PROTECT( Rf_mkString( message ) ) ;
	SEXP s = PROTECT( Rf_mkString( subclass ) ) ;
	
	SEXP call = PROTECT( Rf_lang3( Rf_install("throw"), m, s) ) ;
	UNPROTECT( 2) ; /* m, s */
	
	Rf_eval( call, R_FindNamespace(Rf_mkString("RProtoBuf")) ) ; 
	
	/* but this is never actually called since the call eventually calls stop */
	UNPROTECT(1); 
	return( R_NilValue ); /* Wall */
}

} // namespace rprotobuf

