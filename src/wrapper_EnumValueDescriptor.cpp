// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
// wrapper_EnumValueDescriptor.h: R/C++ interface class library
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
#include "RcppMacros.h"

namespace rprotobuf {

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(EnumValueDescriptor__, __NAME__)

RPB_XP_METHOD_0(METHOD(as_character), GPB::EnumValueDescriptor, DebugString)

RPB_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::EnumValueDescriptor> d) {
    GPB::EnumValueDescriptorProto* message = new GPB::EnumValueDescriptorProto();
    d->CopyTo(message);
    return S4_Message(message);
}

RPB_FUNCTION_2(std::string, METHOD(name), Rcpp::XPtr<GPB::EnumValueDescriptor> d, bool full) {
    return full ? d->full_name() : d->name();
}

RPB_FUNCTION_1(int, METHOD(number), Rcpp::XPtr<GPB::EnumValueDescriptor> d) { return d->number(); }

RPB_FUNCTION_1(S4_EnumDescriptor, METHOD(enum_type), Rcpp::XPtr<GPB::EnumValueDescriptor> d) {
    return S4_EnumDescriptor(d->type());
}

#undef METHOD

}  // namespace rprotobuf
