#include "rprotobuf.h"
#include "ConnectionCopyingOutputStream.h"

namespace rprotobuf{
	
	ConnectionCopyingOutputStream::ConnectionCopyingOutputStream(SEXP con) : con(con) {}
	
	bool ConnectionCopyingOutputStream::Write(const void * buffer, int size){
		
		/* we need to take care of error handling */
		SEXP payload = PROTECT( Rf_allocVector( RAWSXP, size )) ;
		memcpy( RAW(payload), buffer, size ) ;
		SEXP call = PROTECT( Rf_lang3( Rf_install( "writeBin" ), payload, con) ) ; 
		SEXP res = PROTECT( Rf_eval( call, R_GlobalEnv ) ); 
		
		UNPROTECT(3) ; /* res, call, payload */
		return true ;
		res = R_NilValue; // not reached, but shuts g++ -Wall up
	}
	
}

