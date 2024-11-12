// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
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

void DescriptorPoolLookup::add(std::string_view element) { elements.emplace(element); }

bool DescriptorPoolLookup::contains(std::string_view element) {
    return elements.find(element) != elements.end();
}

SEXP DescriptorPoolLookup::getElements() { return Rcpp::wrap(elements); }

std::set<std::string, std::less<>> DescriptorPoolLookup::elements;
RWarningErrorCollector DescriptorPoolLookup::error_collector;
RSourceTree DescriptorPoolLookup::source_tree;
GPB::compiler::Importer* DescriptorPoolLookup::importer =
    new GPB::compiler::Importer(&source_tree, &error_collector);
GPB::DynamicMessageFactory DescriptorPoolLookup::message_factory(importer->pool());

/**
 * Add descriptors from a proto file to the descriptor pool.
 *
 * Specifically, message types, extensions, and enums are added.
 * Services are not added because they are not really used in RProtoBuf.
 *
 * @param files A character vector of .proto files to import.
 * @param dirs A character vector of directories to import from.
 * @throws Rcpp::exception if a file can't be loaded (uncaught).
 */
void DescriptorPoolLookup::importProtoFiles(SEXP files, SEXP dirs) {
    source_tree.addDirectories(dirs);
    int n = LENGTH(files);
    for (int j = 0; j < n; j++) {
        const GPB::FileDescriptor* file_desc = importer->Import(CHAR(STRING_ELT(files, j)));
        if (!file_desc) {
            std::string message = std::string("Could not load proto file '") + CHAR(STRING_ELT(files, j)) +
                "'\n";
            Rcpp_error(message.c_str());
        }
        // add top level messages from the file.
        int ntypes = file_desc->message_type_count();
        for (int i = 0; i < ntypes; i++) {
            const GPB::Descriptor* desc = file_desc->message_type(i);
            add(desc->full_name());
            /* should we bother recursing ? */
        }
        // add top level extensions
        int nexts = file_desc->extension_count();
        for (int i = 0; i < nexts; i++) {
            const GPB::FieldDescriptor* field_desc = file_desc->extension(i);
            add(field_desc->full_name());
        }
        // add top level enums.
        int nenums = file_desc->enum_type_count();
        for (int i = 0; i < nenums; i++) {
            const GPB::EnumDescriptor* enum_desc = file_desc->enum_type(i);
            add(enum_desc->full_name());
        }
    }
    // source_tree.removeDirectories( dirs ) ;
}

/**
 * Clears any persisted state for the descriptor pool.
 */
void DescriptorPoolLookup::reset() {
    source_tree.removeAllDirectories();
    elements.clear();
    // TODO: Find out why deleting the old importer crashes the unit test run sometimes.
    // delete importer;
    importer = new GPB::compiler::Importer(&source_tree, &error_collector);
}

const GPB::DescriptorPool* DescriptorPoolLookup::pool() { return importer->pool(); }

const GPB::DynamicMessageFactory* DescriptorPoolLookup::factory() { return &message_factory; }

}  // namespace rprotobuf
