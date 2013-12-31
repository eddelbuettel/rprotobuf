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
#include "fieldtypes.h"
#include "RcppMacros.h"

namespace rprotobuf {

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(FieldDescriptor__, __NAME__)

RPB_XP_METHOD_0(METHOD(as_character), GPB::FieldDescriptor, DebugString)
RPB_XP_METHOD_0(METHOD(is_extension), GPB::FieldDescriptor, is_extension)
RPB_XP_METHOD_0(METHOD(number), GPB::FieldDescriptor, number)
RPB_XP_METHOD_0(METHOD(type), GPB::FieldDescriptor, type)
RPB_XP_METHOD_0(METHOD(cpp_type), GPB::FieldDescriptor, cpp_type)
RPB_XP_METHOD_0(METHOD(label), GPB::FieldDescriptor, label)
RPB_XP_METHOD_0(METHOD(is_repeated), GPB::FieldDescriptor, is_repeated)
RPB_XP_METHOD_0(METHOD(is_optional), GPB::FieldDescriptor, is_optional)
RPB_XP_METHOD_0(METHOD(is_required), GPB::FieldDescriptor, is_required)
RPB_XP_METHOD_0(METHOD(has_default_value), GPB::FieldDescriptor, has_default_value)

RPB_FUNCTION_1(S4_Descriptor, METHOD(containing_type), Rcpp::XPtr<GPB::FieldDescriptor> d) {
    return S4_Descriptor(d->containing_type());
}

#define RPB_HANDLE_CASE(__CPP__, __LC__)                \
    case CPPTYPE_##__CPP__: {                           \
        return Rcpp::wrap(d->default_value_##__LC__()); \
    }

RPB_FUNCTION_1(SEXP, METHOD(default_value), Rcpp::XPtr<GPB::FieldDescriptor> d) {
    switch (d->cpp_type()) {

        RPB_HANDLE_CASE(INT32, int32)
        RPB_HANDLE_CASE(UINT32, uint32)
#ifdef RCPP_HAS_LONG_LONG_TYPES
        RPB_HANDLE_CASE(INT64, int64)
        RPB_HANDLE_CASE(UINT64, uint64)
#endif
        RPB_HANDLE_CASE(DOUBLE, double)
        RPB_HANDLE_CASE(FLOAT, float)
        RPB_HANDLE_CASE(BOOL, bool)
        RPB_HANDLE_CASE(STRING, string)

        case CPPTYPE_ENUM: {
            return Rf_ScalarInteger(d->default_value_enum()->number());
        }
        default:
            break;
    }
    return R_NilValue;
}

RPB_FUNCTION_1(S4_Descriptor, METHOD(message_type), Rcpp::XPtr<GPB::FieldDescriptor> d) {
    if (d->cpp_type() != CPPTYPE_MESSAGE) {
        throw Rcpp::not_compatible("not a message type field");
    }
    return S4_Descriptor(d->message_type());
}

RPB_FUNCTION_1(S4_EnumDescriptor, METHOD(enum_type), Rcpp::XPtr<GPB::FieldDescriptor> d) {
    if (d->cpp_type() != CPPTYPE_ENUM) {
        Rcpp::stop("not an enum type field");
    }
    return S4_EnumDescriptor(d->enum_type());
}

RPB_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::FieldDescriptor> d) {
    GPB::FieldDescriptorProto* message = new GPB::FieldDescriptorProto();
    d->CopyTo(message);
    return S4_Message(message);
}

RPB_FUNCTION_1(S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::FieldDescriptor> desc) {
    return S4_FileDescriptor(desc->file());
}

RPB_FUNCTION_2(std::string, METHOD(name), Rcpp::XPtr<GPB::FieldDescriptor> d, bool full) {
    return full ? d->full_name() : d->name();
}

#undef RPB_HANDLE_CASE
#undef METHOD

}  // namespace rprotobuf
