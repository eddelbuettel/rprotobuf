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
#include "Rcppsupport.h"

namespace rprotobuf {

const char* kIntStringOptionName = "RProtoBuf.int64AsString";
bool UseStringsForInt64() {
    static const SEXP option_name = Rf_install(kIntStringOptionName);
    return (Rf_asLogical(Rf_GetOption1(option_name)));
}

// Rcpp::wrap silently coerces 64-bit integers to numerics
// which drop precision for values between 2^53 - 2^64.
// So, if an option is set, we return as a character string.
template <typename ValueType>
SEXP Int64AsSEXP(ValueType value) {
    BEGIN_RCPP
    if (UseStringsForInt64()) {
        std::stringstream ss;
        if ((ss << value).fail()) {
            // This should not happen, its a bug in the code.
            string message = string("Error converting int64 to string, unset ") +
                             kIntStringOptionName + " option.";
            Rcpp::stop(message.c_str());
        }
        return Rcpp::CharacterVector(ss.str());
    } else {
        return Rcpp::wrap(value);
    }
    END_RCPP
}

/**
 * extract a field from a message
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 *
 * @return the field called "name" of the message if the
 *         message has the field, otherwise an error is generated
 */
SEXP getMessageField(SEXP pointer, SEXP name) {

#ifdef RPB_DEBUG
    Rprintf("<getMessageField>\n");

    PRINT_DEBUG_INFO("pointer", pointer);
    PRINT_DEBUG_INFO("name", name);
#endif

    /* grab the Message pointer */
    Rcpp::XPtr<GPB::Message> message(pointer);

    GPB::FieldDescriptor* field_desc = getFieldDescriptor(message, name);

#ifdef RPB_DEBUG
    Rprintf("</getMessageField>\n");
#endif

    return (extractFieldAsSEXP(message, field_desc));
}

SEXP extractFieldAsSEXP(const Rcpp::XPtr<GPB::Message>& message,
                        const GPB::FieldDescriptor* fieldDesc) {
    BEGIN_RCPP
    const Reflection* ref = message->GetReflection();

    if (fieldDesc->is_repeated()) {

        switch (GPB::FieldDescriptor::TypeToCppType(fieldDesc->type())) {

#undef HANDLE_REPEATED_FIELD
#define HANDLE_REPEATED_FIELD(TYPE, DATATYPE) \
    case TYPE:                                \
        return Rcpp::wrap(RepeatedFieldImporter<DATATYPE>(ref, *message, fieldDesc));

            HANDLE_REPEATED_FIELD(CPPTYPE_INT32, GPB::int32)
            HANDLE_REPEATED_FIELD(CPPTYPE_DOUBLE, double)
            HANDLE_REPEATED_FIELD(CPPTYPE_FLOAT, float)
            HANDLE_REPEATED_FIELD(CPPTYPE_BOOL, bool)
            HANDLE_REPEATED_FIELD(CPPTYPE_ENUM, enum_field)
            HANDLE_REPEATED_FIELD(CPPTYPE_MESSAGE, message_field)
            // TODO(mstokely): Rcpp doesn't handle uint32 properly as of 2013/12
            // See
            // https://r-forge.r-project.org/tracker/index.php?func=detail&aid=1360&group_id=155&atid=637
            case CPPTYPE_UINT32:
                return Rcpp::wrap(UInt32RepeatedFieldImporter(ref, *message, fieldDesc));
#ifdef RCPP_HAS_LONG_LONG_TYPES
            // We can't handle these the same way, because Rcpp::wrap silently
            // casts int64s to doubles which may cause us to lose precision.
            case CPPTYPE_INT64:
                if (UseStringsForInt64()) {
                    return Rcpp::wrap(Int64AsStringRepeatedFieldImporter(ref, *message, fieldDesc));
                } else {
                    return Rcpp::wrap(RepeatedFieldImporter<int64>(ref, *message, fieldDesc));
                }
            case CPPTYPE_UINT64:
                if (UseStringsForInt64()) {
                    return Rcpp::wrap(
                        UInt64AsStringRepeatedFieldImporter(ref, *message, fieldDesc));
                } else {
                    return Rcpp::wrap(RepeatedFieldImporter<uint64>(ref, *message, fieldDesc));
                }
#endif
#undef HANDLE_REPEATED_FIELD

            case CPPTYPE_STRING:
                if (fieldDesc->type() == TYPE_STRING) {
                    return Rcpp::wrap(RepeatedFieldImporter<std::string>(ref, *message, fieldDesc));
                } else if (fieldDesc->type() == TYPE_BYTES) {
                    int field_size = ref->FieldSize(*message, fieldDesc);
                    Rcpp::List res(field_size);
                    for (int i = 0; i < field_size; i++) {
                        std::string s = ref->GetRepeatedString(*message, fieldDesc, i);
                        res[i] = Rcpp::wrap(std::vector<Rbyte>(s.begin(), s.end()));
                    }
                    return res;
                } else {
                    Rcpp::stop("unknown field type with CPP_TYPE STRING");
                }

            default:
                Rcpp::stop("Unsupported type");
        }

    } else {
        switch (GPB::FieldDescriptor::TypeToCppType(fieldDesc->type())) {

#undef HANDLE_SINGLE_FIELD
#define HANDLE_SINGLE_FIELD(CPPTYPE, SUFFIX) \
    case CPPTYPE:                            \
        return Rcpp::wrap(ref->Get##SUFFIX(*message, fieldDesc));

            HANDLE_SINGLE_FIELD(CPPTYPE_INT32, Int32)
            HANDLE_SINGLE_FIELD(CPPTYPE_DOUBLE, Double)
            HANDLE_SINGLE_FIELD(CPPTYPE_FLOAT, Float)
            HANDLE_SINGLE_FIELD(CPPTYPE_BOOL, Bool)
            // TODO(mstokely): Rcpp doesn't handle uint32 properly as of 2013/12
            // See
            // https://r-forge.r-project.org/tracker/index.php?func=detail&aid=1360&group_id=155&atid=637
            case CPPTYPE_UINT32:
                return Rcpp::wrap(double(ref->GetUInt32(*message, fieldDesc)));
#ifdef RCPP_HAS_LONG_LONG_TYPES
            // Handle these types separately since Rcpp::wrap doesn't
            // do the right thing.
            case CPPTYPE_INT64:
                return Int64AsSEXP<int64>(ref->GetInt64(*message, fieldDesc));
            case CPPTYPE_UINT64:
                return Int64AsSEXP<uint64>(ref->GetUInt64(*message, fieldDesc));
#endif
#undef HANDLE_SINGLE_FIELD

            case CPPTYPE_STRING:
                if (fieldDesc->type() == TYPE_STRING) {
                    return Rcpp::wrap(ref->GetString(*message, fieldDesc));
                } else if (fieldDesc->type() == TYPE_BYTES) {
                    std::string s = ref->GetString(*message, fieldDesc);
                    return Rcpp::wrap(std::vector<Rbyte>(s.begin(), s.end()));
                } else {
                    Rcpp::stop("unknown field type with CPP_TYPE STRING");
                }
            case CPPTYPE_ENUM:
                return Rcpp::wrap(ref->GetEnum(*message, fieldDesc)->number());

            case CPPTYPE_MESSAGE:
                return S4_Message(CLONE(&ref->GetMessage(*message, fieldDesc)));

            default:
                Rcpp::stop("Unsupported type");
        }
    }
    END_RCPP
}

}  // namespace rprotobuf
