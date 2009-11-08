#include "rprotobuf.h"
#include "RconnectionCopyingInputStream.h"

namespace rprotobuf{
	
	RconnectionCopyingInputStream::RconnectionCopyingInputStream(int id){
		connection_id = id ;
	}
	
	int	RconnectionCopyingInputStream::Read(void * buffer, int size){
		
		/* call readBin to read size bytes from R */
		
		SEXP con = PROTECT( Rf_ScalarInteger(connection_id) );
		SEXP what = PROTECT( Rf_allocVector(RAWSXP, 0) ) ;
		SEXP n = PROTECT( Rf_ScalarInteger( size ) );
		SEXP call = PROTECT( Rf_lang4( Rf_install( "readBin" ), con, what, n) ) ; 
		SEXP res = PROTECT( Rf_eval( call, R_GlobalEnv ) ); 
		
		int len = LENGTH( res ) ;
		memcpy( buffer, RAW(res), len ) ;
		
		UNPROTECT( 5 ) ; /* res, call, n, what, con */ 
		
		return len ;
	}
}

