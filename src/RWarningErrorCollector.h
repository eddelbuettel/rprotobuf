#include "rprotobuf.h"

namespace rprotobuf {

class RWarningErrorCollector : public MultiFileErrorCollector {
 public:
  
  // implements ErrorCollector ---------------------------------------
  void AddError(const string& filename, int line, int column,
                const string& message) ;

} ;

} // namespace rprotobuf
