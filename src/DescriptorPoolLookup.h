#ifndef RPROTOBUF_DescriptorPoolLookup_H
#define RPROTOBUF_DescriptorPoolLookup_H

#include <functional>           /* For less */
#include <set>                  /* For set */
#include <string>               /* For string */
#include <string_view>          /* For string_view */

#include "RSourceTree.h"
#include "RWarningErrorCollector.h"

namespace rprotobuf {

class DescriptorPoolLookup {
   public:
    static void add(std::string_view element);

    static bool contains(std::string_view element);

    static SEXP getElements();

    static void importProtoFiles(SEXP files, SEXP cwd);

    static void reset();

    static const GPB::DescriptorPool* pool();

    static const GPB::DynamicMessageFactory* factory();

   private:
    static std::set<std::string, std::less<>> elements;
    static RWarningErrorCollector error_collector;
    static RSourceTree source_tree;
    static GPB::compiler::Importer* importer;
    static GPB::DynamicMessageFactory message_factory;
};

}  // namespace rprotobuf

#endif
