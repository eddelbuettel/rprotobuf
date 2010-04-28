#include "rprotobuf.h"
#include "ConnectionCopyingOutputStream.h"

namespace rprotobuf{
	
	ConnectionCopyingOutputStream::ConnectionCopyingOutputStream(SEXP con) : con(con), writeBin("writeBin") {}
	
	bool ConnectionCopyingOutputStream::Write(const void * buffer, int size){
		
		/* we need to take care of error handling */
		Rcpp::RawVector payload(size) ;
		memcpy( payload.begin() , buffer, size ) ;
		
		writeBin( payload, con) ; 
		return true ;
	}
	
}

