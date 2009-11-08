#include "rprotobuf.h"
#include "RconnectionCopyingInputStream.h"

namespace rprotobuf{
	
	RconnectionCopyingInputStream::RconnectionCopyingInputStream(int id){
		connection_id = id ;
	}
	
	/** 
	 * call readBin to read size bytes from R
	 * 
	 * @param buffer buffer to fill with at most size bytes
	 * @param size maximum number of bytes
	 *
	 * @return the number of bytes actually read
	 */
	int	RconnectionCopyingInputStream::Read(void * buffer, int size){
		
		/* FIXME: maybe we should cache these 4 objects instead of recalculating them all the time */
		SEXP call = PROTECT( getReadBinCall( size ) ) ;
		SEXP res = PROTECT( Rf_eval( call, R_GlobalEnv ) ); 
		
		int len = LENGTH( res ) ;
		memcpy( buffer, RAW(res), len ) ;
		
		UNPROTECT( 2 ) ; /* res, call */ 
		return len ;
	}
	
	SEXP RconnectionCopyingInputStream::getReadBinCall( int size ){
		SEXP con = PROTECT( Rf_ScalarInteger(connection_id) );
		SEXP what = PROTECT( Rf_allocVector(RAWSXP, 0) ) ;
		SEXP n = PROTECT( Rf_ScalarInteger( size ) );
		SEXP call = PROTECT( Rf_lang4( Rf_install( "readBin" ), con, what, n) ) ; 
		UNPROTECT(4) ; /* call, n, what, con */
		return call ;
	}
	
	
}

