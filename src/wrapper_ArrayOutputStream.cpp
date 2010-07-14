
#include "rprotobuf.h"

namespace rprotobuf{

	RCPP_FUNCTION_2( S4_ArrayOutputStream, ArrayOutputStream__new, int size, int block_size){
		return S4_ArrayOutputStream( size, block_size ) ;
	}

}

