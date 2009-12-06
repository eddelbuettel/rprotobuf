#include "rprotobuf.h"
#include "RSourceTree.h"

namespace rprotobuf {

	GPB::io::ZeroCopyInputStream * RSourceTree::Open(const std::string & filename){
		int file_descriptor = open(filename.c_str(), O_RDONLY);
	  	if (file_descriptor >= 0) {
	  		GPB::io::FileInputStream* result = new GPB::io::FileInputStream(file_descriptor);
			result->SetCloseOnDelete(true);
			return result;
	  	} else {
	  	  return NULL;
	  	}		
	}
	
} // namespace rprotobuf


