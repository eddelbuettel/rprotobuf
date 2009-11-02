#include "rprotobuf.h"

//namespace org{
//namespace rproject{
namespace rprotobuf{
//namespace{


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
	
	/* FIXME: not sure R_GlobalEnv is right. This is similar to what rJava does */
	Rf_eval( call, R_GlobalEnv ) ; 
	
	/* but this is never actually called since the call eventually calls stop */
	UNPROTECT(1); 
	return( R_NilValue ); 
}

//} // namespace
} // namespace rprotobuf
//} // namespace rproject
//} // namespace org

