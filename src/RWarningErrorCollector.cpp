// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "RWarningErrorCollector.h"

namespace rprotobuf {

#if GOOGLE_PROTOBUF_VERSION < 5026000
    void RWarningErrorCollector::AddError(const std::string& filename, int line, int column,
                                          const std::string& message) {

        Rprintf("%s:%d:%d:%s\n", filename.c_str(), line + 1, column + 1, message.c_str());
    }
#else
    void RWarningErrorCollector::RecordError(absl::string_view filename, int line, int column,
                                             absl::string_view message) {

        Rprintf("%s:%d:%d:%s\n", std::string(filename).c_str(), line + 1, column + 1, std::string(message).c_str());
    }
#endif

}  // namespace rprotobuf
