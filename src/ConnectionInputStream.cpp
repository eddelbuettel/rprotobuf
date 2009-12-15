#include "rprotobuf.h"
#include "ConnectionInputStream.h"

namespace rprotobuf{
	
	ConnectionInputStream::ConnectionInputStream(SEXP con_, bool was_open_){
		con = con_ ;
		was_open = was_open ;
	}
	
	ConnectionInputStream::~ConnectionInputStream(){
		/* con will be disposed by the R GC, it is
		   protected as part of the protection of the 
		   external pointer that wraps this */
	}
	
	bool ConnectionInputStream::Next(const void** data, int* size){
		return false; 
	}
	void ConnectionInputStream::BackUp(int count){
		
	}
	bool ConnectionInputStream::Skip(int count){
		return false; 
	}
	int64 ConnectionInputStream::ByteCount() const {
		return (int64)0 ;
	}
	
} // namespace rprotobuf
