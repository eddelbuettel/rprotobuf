#include "rprotobuf.h"
#include "ConnectionCopyingInputStream.h"

namespace rprotobuf{
	
	ConnectionCopyingInputStream::ConnectionCopyingInputStream(SEXP con) : con(con){}
	
	/** 
	 * call readBin to read size bytes from R
	 * 
	 * @param buffer buffer to fill with at most size bytes
	 * @param size maximum number of bytes
	 *
	 * @return the number of bytes actually read
	 */
	int	ConnectionCopyingInputStream::Read(void * buffer, int size){
		
		/* we need to take care of error handling */
		SEXP what = PROTECT( Rf_allocVector(RAWSXP, 0) ) ;
		SEXP n    = PROTECT( Rf_ScalarInteger( size ) );
		SEXP call = PROTECT( Rf_lang4( Rf_install( "readBin" ), con, what, n) ) ; 
		SEXP res  = PROTECT( Rf_eval( call, R_GlobalEnv ) ); 
		int len = LENGTH( res ) ;
		memcpy( buffer, RAW(res), len ) ;
		UNPROTECT( 4 ) ; /* res, call, n, what */ 
		return len ;
	}
	
	
}

