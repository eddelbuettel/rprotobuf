// DescriptorPoolLookup.cpp: R/C++ interface class library
//
// Copyright (C) 2010 - 2011  Dirk Eddelbuettel and Romain Francois
//
// This file is part of RProtoBuf.
//
// RProtoBuf is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RProtoBuf is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.

#include "rprotobuf.h"
#include "DescriptorPoolLookup.h"

namespace rprotobuf {

void DescriptorPoolLookup::add(const std::string& element) {
    elements.insert(element);
}

bool DescriptorPoolLookup::contains(const std::string& element) {
    return elements.find(element) != elements.end();
}

SEXP DescriptorPoolLookup::getElements() { return Rcpp::wrap(elements); }

std::set<std::string> DescriptorPoolLookup::elements;
RWarningErrorCollector DescriptorPoolLookup::error_collector;
RSourceTree DescriptorPoolLookup::source_tree;
GPB::compiler::Importer DescriptorPoolLookup::importer(&source_tree,
                                                       &error_collector);
GPB::DynamicMessageFactory DescriptorPoolLookup::message_factory(
    importer.pool());

void DescriptorPoolLookup::importProtoFiles(SEXP files, SEXP dirs) {
    source_tree.addDirectories(dirs);
    int n = LENGTH(files);
    for (int j = 0; j < n; j++) {
        const GPB::FileDescriptor* file_desc =
            importer.Import(CHAR(STRING_ELT(files, j)));
        if (!file_desc) {
            Rf_error("Could not load proto file '%s'\n",
                     CHAR(STRING_ELT(files, j)));
            continue;
        }
        int ntypes = file_desc->message_type_count();
        for (int i = 0; i < ntypes; i++) {
            const GPB::Descriptor* desc = file_desc->message_type(i);
            add(desc->full_name());
            /* should we bother recursing ? */
            /* TODO(mstokely): add top level enums and services? */
        }
        // add top level extensions!
        int nexts = file_desc->extension_count();
        for (int i = 0; i < nexts; i++) {
            const GPB::FieldDescriptor* field_desc = file_desc->extension(i);
            add(field_desc->full_name());
        }
    }
    // source_tree.removeDirectories( dirs ) ;
}

const GPB::DescriptorPool* DescriptorPoolLookup::pool() {
    return importer.pool();
}

const GPB::DynamicMessageFactory* DescriptorPoolLookup::factory() {
    return &message_factory;
}

}  // namespace rprotobuf
