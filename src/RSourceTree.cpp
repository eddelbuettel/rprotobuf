#include "rprotobuf.h"
#include "RSourceTree.h"

namespace rprotobuf {

	io::ZeroCopyInputStream * RSourceTree::Open(const string & filename){
		int file_descriptor = open(filename.c_str(), O_RDONLY);
	  	if (file_descriptor >= 0) {
	  	  io::FileInputStream* result = new io::FileInputStream(file_descriptor);
	  	  result->SetCloseOnDelete(true);
	  	  return result;
	  	} else {
	  	  return NULL;
	  	}		
	}
	
} // namespace rprotobuf


