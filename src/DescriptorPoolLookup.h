#ifndef RPROTOBUF_DescriptorPoolLookup_H
#define RPROTOBUF_DescriptorPoolLookup_H

#include "RSourceTree.h"
#include "RWarningErrorCollector.h"

namespace rprotobuf {

class DescriptorPoolLookup {
   public:
    static void add(const std::string& element);

    static bool contains(const std::string& element);

    static SEXP getElements();

    static void importProtoFiles(SEXP files, SEXP cwd);

    static const GPB::DescriptorPool* pool();

    static const GPB::DynamicMessageFactory* factory();

   private:
    static std::set<std::string> elements;
    static RWarningErrorCollector error_collector;
    static RSourceTree source_tree;
    static GPB::compiler::Importer importer;
    static GPB::DynamicMessageFactory message_factory;
};

}  // namespace rprotobuf

#endif
