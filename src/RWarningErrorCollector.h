#include <string>               /* For string */

#include "rprotobuf.h"

namespace rprotobuf {

class RWarningErrorCollector : public GPB::compiler::MultiFileErrorCollector {
   public:
    // implements ErrorCollector ---------------------------------------
    void AddError(const std::string& filename, int line, int column, const std::string& message);
};

}  // namespace rprotobuf
