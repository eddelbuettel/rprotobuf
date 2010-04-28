#include "rprotobuf.h"
#include "ConnectionCopyingInputStream.h"

namespace rprotobuf{
	
	ConnectionCopyingInputStream::ConnectionCopyingInputStream(SEXP con) : 
		con(con), readBin("readBin") {}
	
	/** 
	 * call readBin to read size bytes from R
	 * 
	 * @param buffer buffer to fill with at most size bytes
	 * @param size maximum number of bytes
	 *
	 * @return the number of bytes actually read
	 */
	int	ConnectionCopyingInputStream::Read(void * buffer, int size){
		
		/* TODO: error handling */
		Rcpp::RawVector res = readBin( con, Rcpp::RawVector( (size_t)0 ), size ) ;
		memcpy( buffer, res.begin() , res.size() ) ;
		return res.size() ;
	}
	
	
}

