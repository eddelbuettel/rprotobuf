#include <string>               /* For string */

#include "rprotobuf.h"

namespace rprotobuf {

class RWarningErrorCollector : public GPB::compiler::MultiFileErrorCollector {
   public:
    // implements ErrorCollector ---------------------------------------
    #if GOOGLE_PROTOBUF_VERSION < 5026000
        void AddError(const std::string& filename, int line, int column, const std::string& message);
    #else
        void RecordError(absl::string_view filename, int line, int column, absl::string_view message);
    #endif
};

}  // namespace rprotobuf
