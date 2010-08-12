#include "rprotobuf.h"
#include "RconnectionCopyingInputStream.h"

namespace rprotobuf{
	
	RconnectionCopyingInputStream::RconnectionCopyingInputStream(int id) : 
		connection_id(id){}
	
	/** 
	 * call readBin to read size bytes from R
	 * 
	 * @param buffer buffer to fill with at most size bytes
	 * @param size maximum number of bytes
	 *
	 * @return the number of bytes actually read
	 */
	int	RconnectionCopyingInputStream::Read(void * buffer, int size){
		
		Rcpp::Language call( "readBin", connection_id, Rcpp::RawVector(0), size ) ;
		Rcpp::RawVector res ;
		try{
			res = call.eval(); 
		}  catch( ... ){
			return 0 ;
		}
		int len = res.size() ;
		memcpy( buffer, reinterpret_cast<const void*>(res.begin()), len) ;
		return len ;
	}
	
}

