#include "rprotobuf.h"
#include "RWarningErrorCollector.h" 

namespace rprotobuf {

	void RWarningErrorCollector::AddError(const string& filename, int line, int column,
                const string& message) {
		
    	Rf_warning( "%s:%d:%d:%s", filename.c_str(), line+1, column+1, message.c_str() ) ;
	}

} // namespace rprotobuf

