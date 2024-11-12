
// Copyright (C) 2010 - 2022  Dirk Eddelbuettel and Romain Francois
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

// {{{ GETDOUBLE
/**
 * get the index'th value of x, as an double
 *
 * @param x some R data
 * @param index the index
 * @return x[index], as an double
 * @throws Rcpp::exception if x[index] cannot be converted to double
 */
/* FIXME: should we convert the NA's */
double GET_double(SEXP x, int index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((double)INTEGER(x)[index]);
        case REALSXP:
            return (REAL(x)[index]);
        case LGLSXP:
            return ((double)LOGICAL(x)[index]);
        case RAWSXP:
            return ((double)RAW(x)[index]);
        default:
            Rcpp::stop("cannot cast SEXP to double");
    }
    return 0.0;  // -Wall
}
// }}}

float GET_float(SEXP x, int index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((float)INTEGER(x)[index]);
        case REALSXP:
            return ((float)REAL(x)[index]);
        case LGLSXP:
            return ((float)LOGICAL(x)[index]);
        case RAWSXP:
            return ((float)RAW(x)[index]);
        default:
            Rcpp::stop("cannot cast SEXP to double");
    }
    return (float)0.0;  // -Wall
}

int GET_int(SEXP x, int index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return (INTEGER(x)[index]);
        case REALSXP:
            return ((int)REAL(x)[index]);
        case LGLSXP:
            return ((int)LOGICAL(x)[index]);
        case RAWSXP:
            return ((int)RAW(x)[index]);
        default:
            Rcpp::stop("cannot cast SEXP to int");
    }
    return 0;  // -Wall, should not happen since we only call this when we know it works
}

template <typename ValueType>
ValueType Int64FromString(const std::string& value) {
    std::stringstream ss(value);
    ValueType ret;
    if ((ss >> ret).fail() || !(ss >> std::ws).eof()) {
        std::string message =
            "Provided character value '" + value + "' cannot be cast to 64-bit integer.";
        Rcpp::stop(message.c_str());
    }
    return ret;
}

template <typename ValueType>
ValueType Int32FromString(const std::string& value) {
    std::stringstream ss(value);
    ValueType ret;
    if ((ss >> ret).fail() || !(ss >> std::ws).eof()) {
        std::string message =
            "Provided character value '" + value + "' cannot be cast to 32-bit integer.";
        Rcpp::stop(message.c_str());
    }
    return ret;
}

int32 GET_int32(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((int32)INTEGER(x)[vec_index]);
        case REALSXP:
            return ((int32)REAL(x)[vec_index]);
        case LGLSXP:
            return ((int32)LOGICAL(x)[vec_index]);
        case RAWSXP:
            return ((int32)RAW(x)[vec_index]);
        case STRSXP:
            return Int32FromString<int32>(CHAR(STRING_ELT(x, vec_index)));
        default:
            Rcpp::stop("cannot cast SEXP to int32");
    }
    return (int32)0;  // -Wall, should not happen since we only call this when we know it works
}

int64 GET_int64(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((int64)INTEGER(x)[vec_index]);
        case REALSXP:
            return ((int64)REAL(x)[vec_index]);
        case LGLSXP:
            return ((int64)LOGICAL(x)[vec_index]);
        case RAWSXP:
            return ((int64)RAW(x)[vec_index]);
        case STRSXP:
            return Int64FromString<int64>(CHAR(STRING_ELT(x, vec_index)));
        default:
            Rcpp::stop("cannot cast SEXP to int64");
    }
    return (int64)0;  // -Wall, should not happen since we only call this when we know it works
}

uint32 GET_uint32(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((uint32)INTEGER(x)[vec_index]);
        case REALSXP:
            return ((uint32)REAL(x)[vec_index]);
        case LGLSXP:
            return ((uint32)LOGICAL(x)[vec_index]);
        case RAWSXP:
            return ((uint32)RAW(x)[vec_index]);
        case STRSXP:
            return Int32FromString<uint32>(CHAR(STRING_ELT(x, vec_index)));
        default:
            Rcpp::stop("cannot cast SEXP to uint32");
    }
    return (uint32)0;  // -Wall, should not happen since we only call this when we know it works
}

uint64 GET_uint64(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            return ((uint64)INTEGER(x)[vec_index]);
        case REALSXP:
            return ((uint64)REAL(x)[vec_index]);
        case LGLSXP:
            return ((uint64)LOGICAL(x)[vec_index]);
        case RAWSXP:
            return ((uint64)RAW(x)[vec_index]);
        case STRSXP:
            return Int64FromString<uint64>(CHAR(STRING_ELT(x, vec_index)));
        default:
            Rcpp::stop("cannot cast SEXP to uint64");
    }
    return (uint64)0;  // -Wall, should not happen since we only call this when we know it works
}

bool GET_bool(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case INTSXP:
            if (INTEGER(x)[vec_index] == R_NaInt) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            }
            return ((bool)INTEGER(x)[vec_index]);
        case REALSXP:
            if (REAL(x)[vec_index] == R_NaReal) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            }
            return ((bool)REAL(x)[vec_index]);
        case LGLSXP:
            if (LOGICAL(x)[vec_index] == NA_LOGICAL) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            }
            return ((bool)LOGICAL(x)[vec_index]);
        case RAWSXP:
            return ((bool)RAW(x)[vec_index]);
        default:
            Rcpp::stop("cannot cast SEXP to bool");
    }
    return (bool)0;  // Unreachable.  -Wall
}

std::string GET_stdstring(SEXP x, R_xlen_t vec_index) {
    if (TYPEOF(x) == STRSXP) {
        return (CHAR(STRING_ELT(x, vec_index)));
    }
    return "";  // Unreachable.  -Wall
}

std::string GET_bytes(SEXP x, R_xlen_t vec_index) {
    switch (TYPEOF(x)) {
        case RAWSXP:
            if (vec_index == 0) {
                return (std::string((const char*)RAW(x), (size_t)LENGTH(x)));
            } else {
                Rcpp::stop("cannot cast SEXP to bytes");
            }
        case VECSXP:
            if (TYPEOF(VECTOR_ELT(x, vec_index)) == RAWSXP) {
                return (std::string((const char*)RAW(VECTOR_ELT(x, vec_index)),
                                    (size_t)LENGTH(VECTOR_ELT(x, vec_index))));
            } else {
                Rcpp::stop("cannot cast SEXP to bytes");
            }
        default:
            Rcpp::stop("cannot cast SEXP to bytes");
    }
    return "";  // Unreachable. -Wall
}

/**
 * indicates if this is a list of messages
 *
 * @param x a list (VECSXP), not a long vec
 * @return TRUE if all objects are instances of Message class
 */
Rboolean allAreMessages(SEXP x) {
    if (TYPEOF(x) != VECSXP) return _FALSE_;

    R_xlen_t n = LENGTH(x);     // Caller verifies its not a long vec
    SEXP current;
    for (R_xlen_t i = 0; i < n; i++) {
        current = VECTOR_ELT(x, i);
        /* not an S4 object */
        if (TYPEOF(current) != S4SXP) return _FALSE_;

        /* not a Message object */
        if (!Rf_inherits(current, "Message")) return _FALSE_;
    }
    return _TRUE_;
}

/**
 * indicates if this is a list of raws
 *
 * @param x a list (VECSXP)
 * @return TRUE if all objects are instances of RAWSXP
 */
Rboolean allAreRaws(SEXP x) {
    if (TYPEOF(x) != VECSXP) return _FALSE_;

    R_xlen_t n = LENGTH(x);
    SEXP current;
    for (R_xlen_t i = 0; i < n; i++) {
        current = VECTOR_ELT(x, i);
        /* not a RAWSXP */
        if (TYPEOF(current) != RAWSXP) return _FALSE_;
    }
    return _TRUE_;
}

/**
 * check that all the values contained in value are suitable for the
 * enum type
 *
 * @param field_desc field descriptor of an enum type
 * @param value value to potentially fill the enum
 *
 */
void CHECK_values_for_enum(const GPB::FieldDescriptor* field_desc, SEXP value) {
    BEGIN_RCPP
    const GPB::EnumDescriptor* enum_desc = field_desc->enum_type();
    // N.B. n undefined if TYPEOF(value) not a vector, but we catch that below.
    R_xlen_t n = XLENGTH(value);

    switch (TYPEOF(value)) {
        // {{{ numbers
        case INTSXP:
        case REALSXP:
        case LGLSXP:
        case RAWSXP: {
            int nenums = enum_desc->value_count();  // Guaranteed to be > 0.
            std::vector<int> possibles(nenums);
            for (int i = 0; i < nenums; i++) {
                possibles[i] = enum_desc->value(i)->number();
            }

            /* loop around the numbers to see if they are in the possibles */
            for (int i = 0; i < n; i++) {
                int val = GET_int(value, i);
                int ok = 0;
                for (int j = 0; j < nenums; j++) {
                    if (val == possibles[j]) {
                        ok = 1;
                        break;
                    }
                }
                if (!ok) {
                    Rcpp::stop("wrong value for enum");
                }
            }

            break;
        }
        // }}}

        // {{{ STRSXP
        case STRSXP: {
            int nenums = enum_desc->value_count();
            std::vector<std::string> possibles(nenums);
            for (int i = 0; i < nenums; i++) {
                possibles[i] = enum_desc->value(i)->name();
            }

            /* loop around the numbers to see if they are in the possibles */
            for (int i = 0; i < n; i++) {
                const char* val = CHAR(STRING_ELT(value, i));
                int ok = 0;
                /* FIXME: there is probably something more efficient */
                for (int j = 0; j < nenums; j++) {
                    if (!possibles[j].compare(val)) {
                        ok = 1;
                        break;
                    }
                }
                if (!ok) {
                    Rcpp::stop("wrong value for enum");
                }
            }
            break;
        }
        // }}}

        default:
            Rcpp::stop("impossible to convert to a enum");
    }
    VOID_END_RCPP
}

/**
 * check that the values are suitable for the field descriptor
 *
 * @throws Rcpp::exception on error (uncaught)
 */
void CHECK_messages(const GPB::FieldDescriptor* field_desc, SEXP values) {
    if (TYPEOF(values) != VECSXP) {
        Rcpp::stop("expecting a list of messages");
    }

    std::string_view target = field_desc->message_type()->full_name();
    int n = LENGTH(values);
    for (int i = 0; i < n; i++) {
        if (!isMessage(VECTOR_ELT(values, i), target)) {
            // TODO(mstokely): When we have C++11 CXX11, use
            // std::to_string(i)
            // {{{
            std::string s;
            std::stringstream out;
            out << i;
            s = out.str();
            // }}}
            std::string message = "List element " + s + " is not a message " +
                                  "of the appropriate type ('" +
                                  std::string(target) + "')";
            Rcpp::stop(message.c_str());
        }
    }
}

/**
 * check that all repeated values are ok before doing anything,
 * otherwise this could lead to modifying a few values then failing in
 * an inconsistent state.
 */
void CHECK_repeated_vals(const GPB::FieldDescriptor* field_desc, SEXP value, int value_size) {
    switch (field_desc->type()) {
        case TYPE_MESSAGE:
        case TYPE_GROUP: {
            switch (TYPEOF(value)) {
                case VECSXP: {

                    /* check that it is a list of Messages of the
                       appropriate type */
                    CHECK_messages(field_desc, value);
                    break;
                }
                case S4SXP: {
                    /* check that this is a message of the appropriate type */
                    if (!isMessage(value,
                                   field_desc->message_type()->full_name())) {
                      std::string message =
                          "Not a message of type '" +
                          std::string(field_desc->message_type()->full_name()) +
                          "'";
                      Rcpp::stop(message.c_str());
                    }
                    break;
                }
                default:
                    Rcpp::stop("impossible to convert to a message");
            }
            break;
        }
        case TYPE_ENUM: {
            const GPB::EnumDescriptor* enum_desc = field_desc->enum_type();

            /* check first, it means we have to loop twice, but
               otherwise this could have some side effects before the
               exception is thrown */

            /* FIXME: the checking should go before the resizing */

            switch (TYPEOF(value)) {
                // {{{ numbers
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    int nenums = enum_desc->value_count();
                    std::vector<int> possibles(nenums);
                    for (int i = 0; i < nenums; i++) {
                        possibles[i] = enum_desc->value(i)->number();
                    }

                    /* loop around the numbers to see if they are in the possibles */
                    for (int i = 0; i < value_size; i++) {
                        int val = GET_int(value, i);
                        int ok = 0;
                        for (int j = 0; j < nenums; j++) {
                            if (val == possibles[j]) {
                                ok = 1;
                                break;
                            }
                        }
                        if (!ok) {
                            Rcpp::stop("wrong value for enum");
                        }
                    }
                    break;
                }
                // }}}

                // {{{ STRSXP
                case STRSXP: {
                    int nenums = enum_desc->value_count();
                    std::vector<std::string> possibles(nenums);
                    for (int i = 0; i < nenums; i++) {
                        possibles[i] = enum_desc->value(i)->name();
                    }

                    /* loop around the numbers to see if they are in the possibles */
                    for (int i = 0; i < value_size; i++) {
                        const char* val = CHAR(STRING_ELT(value, i));
                        int ok = 0;
                        /* FIXME: there is probably something more efficient */
                        for (int j = 0; j < nenums; j++) {
                            if (!possibles[j].compare(val)) {
                                ok = 1;
                                break;
                            }
                        }
                        if (!ok) {
                            Rcpp::stop("wrong value for enum");
                        }
                    }

                    break;
                }
                // }}}

                default:
                    Rcpp::stop("impossible to convert to a enum");
            }
            break;
        }
        case TYPE_DOUBLE:
        case TYPE_FLOAT:
        case TYPE_INT64:
        case TYPE_UINT64:
        case TYPE_INT32:
        case TYPE_FIXED64:
        case TYPE_FIXED32:
        case TYPE_BOOL:
        case TYPE_STRING:
        case TYPE_BYTES:
        case TYPE_UINT32:
        case TYPE_SFIXED32:
        case TYPE_SFIXED64:
        case TYPE_SINT32:
        case TYPE_SINT64: {
            ;  // nothing, just to satisfy -Wall
        }
    }
}

/**
 * set a non-repeated message field to a new value
 *
 * @param message pointer to a message
 * @param ref pointer to reflection object for message
 * @param field_desc pointer to field descriptor to update
 * @param value new value for the field
 * @param value_size size of the new value for the field
 * @throws Rcpp::exception on error (uncaught)
 * @return void, the message is modified by reference
 */
void setNonRepeatedMessageField(GPB::Message* message, const Reflection* ref,
                                const GPB::FieldDescriptor* field_desc, SEXP value,
                                int value_size) {
    if (value_size > 1) {
        Rcpp::stop("cannot set non-repeated field to vector of length > 1");
    }
    switch (GPB::FieldDescriptor::TypeToCppType(field_desc->type())) {
// {{{ simple cases using macro expansion
#undef HANDLE_SINGLE_FIELD
#define HANDLE_SINGLE_FIELD(CPPTYPE, CAMEL, TYPE)                    \
    case CPPTYPE: {                                                  \
        ref->Set##CAMEL(message, field_desc, Rcpp::as<TYPE>(value)); \
        break;                                                       \
    }

        HANDLE_SINGLE_FIELD(CPPTYPE_DOUBLE, Double, double)
        HANDLE_SINGLE_FIELD(CPPTYPE_FLOAT, Float, float)
        case CPPTYPE_BOOL: {
            // TODO(mstokely): Rcpp should handle this!
            if ((TYPEOF(value) == LGLSXP) && (LOGICAL(value)[0] == NA_LOGICAL)) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            } else if ((TYPEOF(value) == INTSXP) && (INTEGER(value)[0] == R_NaInt)) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            } else if ((TYPEOF(value) == REALSXP) && (REAL(value)[0] == R_NaReal)) {
                Rcpp::stop("NA boolean values can not be stored in bool protocol buffer fields");
            }
            ref->SetBool(message, field_desc, Rcpp::as<bool>(value));
            break;
        }
        case CPPTYPE_INT32: {
            if (TYPEOF(value) == STRSXP) {
                const std::string int32str = COPYSTRING(CHAR(STRING_ELT(value, 0)));
                ref->SetInt32(message, field_desc, Int32FromString<GPB::int32>(int32str));
                break;
            } else {
                ref->SetInt32(message, field_desc, Rcpp::as<GPB::int32>(value));
                break;
            }
        }
        case CPPTYPE_UINT32: {
            if (TYPEOF(value) == STRSXP) {
                const std::string uint32str = COPYSTRING(CHAR(STRING_ELT(value, 0)));
                ref->SetUInt32(message, field_desc, Int32FromString<GPB::uint32>(uint32str));
                break;
            } else {
                // Rcpp::as is broken for uint32 types, so we just get Rcpp
                // to give us a valid double,
                ref->SetUInt32(message, field_desc, Rcpp::as<double>(value));
                break;
            }
        }

#ifdef RCPP_HAS_LONG_LONG_TYPES
        case CPPTYPE_INT64: {
            // TODO(mstokely) Rcpp::as<int64> of a STRSEXP should just
            // work for strings representing int64s.
            if (TYPEOF(value) == STRSXP) {
                const std::string int64str = COPYSTRING(CHAR(STRING_ELT(value, 0)));
                ref->SetInt64(message, field_desc, Int64FromString<GPB::int64>(int64str));
                break;
            } else {
                ref->SetInt64(message, field_desc, Rcpp::as<GPB::int64>(value));
                break;
            }
        }
        case CPPTYPE_UINT64: {
            // TODO(mstokely) Rcpp::as<int64> of a STRSEXP should just
            // work for strings representing int64s.
            if (TYPEOF(value) == STRSXP) {
                const std::string int64str = COPYSTRING(CHAR(STRING_ELT(value, 0)));
                ref->SetUInt64(message, field_desc, Int64FromString<GPB::uint64>(int64str));
                break;
            } else {
                ref->SetUInt64(message, field_desc, Rcpp::as<GPB::uint64>(value));
                break;
            }
        }
#endif
#undef HANDLE_SINGLE_FIELD
        default:
            Rcpp::stop("Unsupported type");
        // }}}

        // {{{ string
        case CPPTYPE_STRING: {
            switch (TYPEOF(value)) {
                case STRSXP: {
                    ref->SetString(message, field_desc, COPYSTRING(CHAR(STRING_ELT(value, 0))));
                    break;
                }
                case RAWSXP: {
                    ref->SetString(message, field_desc, GET_bytes(value, 0));
                    break;
                }
                case S4SXP: {
                    /* check if value is a message */
                    if (!Rf_inherits(value, "Message")) {
                        Rcpp::stop("Can only convert S4 objects of class 'Message'");
                    }
                    GPB::Message* __mess = GET_MESSAGE_POINTER_FROM_S4(value);
                    ref->SetString(message, field_desc, __mess->SerializeAsString());
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to string");
            }
            break;
        }
        // }}}

        // {{{ message
        case CPPTYPE_MESSAGE: {
            if (TYPEOF(value) == S4SXP && Rf_inherits(value, "Message")) {
                GPB::Message* mess =
                    (GPB::Message*)EXTPTR_PTR(GET_SLOT(value, Rf_install("pointer")));
                std::string_view type = mess->GetDescriptor()->full_name();
                std::string_view target = field_desc->message_type()->full_name();
                if (type != target) {
                    Rcpp::stop("wrong message type");
                }
                GPB::Message* m = ref->MutableMessage(message, field_desc);
                m->CopyFrom(*mess);
            } else {
                Rcpp::stop("type mismatch, expecting a 'Message' object");
            }
            break;
        }
        // }}}

        // {{{ enum
        case CPPTYPE_ENUM: {
            const GPB::EnumDescriptor* enum_desc = field_desc->enum_type();
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    int val = Rcpp::as<int>(value);
                    const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByNumber(val);
                    if (!evd) {
                        Rcpp::stop("wrong value for enum");
                    } else {
                        ref->SetEnum(message, field_desc, evd);
                    }
                    break;
                }
                case STRSXP: {
                    std::string val = Rcpp::as<std::string>(value);
                    const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val);
                    if (!evd) {
                        Rcpp::stop("wrong value for enum");
                    } else {
                        ref->SetEnum(message, field_desc, evd);
                    }
                    break;
                }
                default:
                    Rcpp::stop("cannot set enum value");
            }
            break;
        }
        // }}}
    }
}

/**
 * set a repeated message field to a new value
 *
 * @param message pointer to a message
 * @param ref pointer to reflection object for message
 * @param field_desc pointer to field descriptor to update
 * @param value new value for the field
 * @param value_size size of the new value for the field
 * @throws Rcpp::exception on error (uncaught)
 * @return void, the message is modified by reference
 */

void setRepeatedMessageField(GPB::Message* message, const Reflection* ref,
                             const GPB::FieldDescriptor* field_desc, SEXP value,
                             R_xlen_t value_size) {
    // The number of elements already in the repeated field.
    int field_size = ref->FieldSize(*message, field_desc);

    /* in case of messages or enum, we have to check that all
       values are ok before doing anything, othewise this could leed
       to modify a few values and then fail which is not good */
    CHECK_repeated_vals(field_desc, value, value_size);

    /* Remove some items if there are too many. */
    if (field_size > value_size) {
        /* we need to remove some */
        while (field_size > value_size) {
            ref->RemoveLast(message, field_desc);
            field_size--;
        }
    }

    switch (field_desc->type()) {
        // {{{ int32
        case TYPE_INT32:
        case TYPE_SINT32:
        case TYPE_SFIXED32: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP:
                case STRSXP:  // For int32, we support chars.
                {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedInt32(message, field_desc, i, GET_int32(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddInt32(message, field_desc, GET_int32(value, i));
                        }
                    }

                    break;
                }

                default:
                    Rcpp::stop("Cannot convert to int32");
            }
            break;
        }
        // }}}

        // {{{ int64
        case TYPE_INT64:
        case TYPE_SINT64:
        case TYPE_SFIXED64: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP:
                case STRSXP:  // For int64, we support chars.
                {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedInt64(message, field_desc, i, GET_int64(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddInt64(message, field_desc, GET_int64(value, i));
                        }
                    }
                    break;
                }

                default:
                    Rcpp::stop("Cannot convert to int64");
            }
            break;
        }
        // }}}

        // {{{ uint32
        case TYPE_UINT32:
        case TYPE_FIXED32: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP:
                case STRSXP:  // For int32, we support chars.
                {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedUInt32(message, field_desc, i, GET_uint32(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddUInt32(message, field_desc, GET_uint32(value, i));
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to uint32");
            }
            break;
        }
        // }}}

        // {{{ uint64
        case TYPE_UINT64:
        case TYPE_FIXED64: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP:
                case STRSXP:  // For int64, we support chars.
                {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedUInt64(message, field_desc, i, GET_uint64(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddUInt64(message, field_desc, GET_uint64(value, i));
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to int64");
            }
            break;
        }
        // }}}

        // {{{ double
        case TYPE_DOUBLE: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedDouble(message, field_desc, i, GET_double(value, i));
                    }
                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddDouble(message, field_desc, GET_double(value, i));
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to double");
            }
            break;
        }
        // }}}

        // {{{ float
        case TYPE_FLOAT: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedFloat(message, field_desc, i, GET_float(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddFloat(message, field_desc, GET_float(value, i));
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to float");
            }
            break;
        }
        // }}}

        // {{{ bool
        case TYPE_BOOL: {
            switch (TYPEOF(value)) {
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    R_xlen_t i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        ref->SetRepeatedBool(message, field_desc, i, GET_bool(value, i));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddBool(message, field_desc, GET_bool(value, i));
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to bool");
            }
            break;
        }
        // }}}

        // {{{ string
        case TYPE_STRING:
        case TYPE_BYTES: {
            switch (TYPEOF(value)) {
                case STRSXP: {
                    /* in any case, fill the values up to field_size */
                    R_xlen_t i = 0;
                    for (; i < field_size; i++) {
                        ref->SetRepeatedString(message, field_desc, i,
                                               COPYSTRING(CHAR(STRING_ELT(value, i))));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddString(message, field_desc,
                                           COPYSTRING(CHAR(STRING_ELT(value, i))));
                        }
                    }
                    break;
                }
                case RAWSXP: {
                    /* in any case, fill the values up to field_size */
                    R_xlen_t i = 0;
                    for (; i < field_size; i++) {
                        ref->SetRepeatedString(message, field_desc, i, GET_bytes(value, 0));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            ref->AddString(message, field_desc, GET_bytes(value, 0));
                        }
                    }
                    break;
                }
                case S4SXP: {
                    /* check if value is a message */
                    if (!Rf_inherits(value, "Message")) {
                        Rcpp::stop("Can only convert S4 objects of class 'Message'");
                    }
                    GPB::Message* __mess = GET_MESSAGE_POINTER_FROM_S4(value);
                    ref->SetRepeatedString(message, field_desc, 0, __mess->SerializeAsString());
                    break;
                }
                case VECSXP: {
                    // we know it is a list of messages or raws because it
                    // has been tested above
                    if (LENGTH(value) > 0 && TYPEOF(VECTOR_ELT(value, 0)) == RAWSXP) {
                        /* in any case, fill the values up to field_size */
                        R_xlen_t i = 0;
                        for (; i < field_size; i++) {
                            ref->SetRepeatedString(message, field_desc, i, GET_bytes(value, i));
                        }

                        /* then add some if needed */
                        if (value_size > field_size) {
                            for (; i < value_size; i++) {
                                ref->AddString(message, field_desc, GET_bytes(value, i));
                            }
                        }
                    } else {
                        // FIXME: we should probably use SerializeToString
                        //        as indicated in the protobuf api documentation
                        //        http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.message_lite.html#MessageLite.SerializeAsString.details
                        GPB::Message* __mess;

                        /* in any case, fill the values up to field_size */
                        R_xlen_t i = 0;
                        for (; i < field_size; i++) {
                            __mess = GET_MESSAGE_POINTER_FROM_S4(VECTOR_ELT(value, i));
                            ref->SetRepeatedString(message, field_desc, i,
                                                   __mess->SerializeAsString());
                        }
                        /* then add some if needed */
                        if (value_size > field_size) {
                            for (; i < value_size; i++) {
                                __mess = GET_MESSAGE_POINTER_FROM_S4(VECTOR_ELT(value, i));
                                ref->AddString(message, field_desc, __mess->SerializeAsString());
                            }
                        }
                    }
                    break;
                }
                default:
                    Rcpp::stop("Cannot convert to string");
            }
            break;
        }
        // }}}

        // {{{ message
        case TYPE_MESSAGE:
        case TYPE_GROUP: {
            if (TYPEOF(value) == S4SXP) {
                /* we know it is a message of the correct type (tested above) */
                GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4(value);

                if (field_size == 1) {
                    /* FIXME: we should not __copy__ the message */
                    ref->MutableRepeatedMessage(message, field_desc, 0)->CopyFrom(*mess);
                } else {
                    /* FIXME */
                    ref->ClearField(message, field_desc);

                    /* FIXME: we should not __copy__ the message */
                    ref->AddMessage(message, field_desc)->CopyFrom(*mess);
                }
            } else if (TYPEOF(value) == VECSXP) {
                /* in any case, fill the values up to field_size */
                int i = 0;
                for (; i < field_size; i++) {
                    GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4(VECTOR_ELT(value, i));
                    /* we already know it is of the correct type because of the
                       premptive check above */
                    ref->MutableRepeatedMessage(message, field_desc, i)->CopyFrom(*mess);
                }

                /* then add some if needed */
                if (value_size > field_size) {
                    for (; i < value_size; i++) {
                        GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4(VECTOR_ELT(value, i));
                        /* we already know it is of the correct type
                           because of the premptive check above */

                        ref->AddMessage(message, field_desc)->CopyFrom(*mess);
                    }
                }
            } else {
                Rcpp::stop("type mismatch, expecting a 'Message' object or a list of them");
            }
            break;
        }
        // }}}

        // {{{ enum
        case TYPE_ENUM: {
            const GPB::EnumDescriptor* enum_desc = field_desc->enum_type();

            switch (TYPEOF(value)) {
                // {{{ numbers
                case INTSXP:
                case REALSXP:
                case LGLSXP:
                case RAWSXP: {
                    int i = 0;
                    /* in any case, fill the values up to field_size */
                    for (; i < field_size; i++) {
                        int val = GET_int(value, i);
                        ref->SetRepeatedEnum(message, field_desc, i,
                                             enum_desc->FindValueByNumber(val));
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            int val = GET_int(value, i);
                            ref->AddEnum(message, field_desc, enum_desc->FindValueByNumber(val));
                        }
                    }
                    break;
                }
                // }}}

                // {{{ STRSXP
                case STRSXP: {
                    /* in any case, fill the values up to field_size */
                    int i = 0;
                    for (; i < field_size; i++) {
                        std::string val = CHAR(STRING_ELT(value, i));
                        const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val);
                        ref->SetRepeatedEnum(message, field_desc, i, evd);
                    }

                    /* then add some if needed */
                    if (value_size > field_size) {
                        for (; i < value_size; i++) {
                            std::string val = CHAR(STRING_ELT(value, i));
                            const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val);
                            ref->AddEnum(message, field_desc, evd);
                        }
                    }
                    break;
                }
                // }}}

                default:
                    Rcpp::stop("cannot set enum value");
            }
        }
        // }}}
    }
}

/**
 * set a message field to a new value
 *
 * @param pointer external pointer to a message
 * @param name name of the field, or an S4 FieldDescriptor object.
 * @param value new value for the field
 *
 * @return allways NULL, the message is modified by reference
 */
SEXP setMessageField(SEXP pointer, SEXP name, SEXP value) {
    BEGIN_RCPP
    RPB_DEBUG_BEGIN("setMessageField")
    PRINT_DEBUG_INFO("pointer", pointer);
    PRINT_DEBUG_INFO("name", name);
    PRINT_DEBUG_INFO("value", value);

    /* grab the Message pointer */
    GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer);

    /* check that we can get a file descriptor from name */
    const GPB::FieldDescriptor* field_desc = getFieldDescriptor(message, name);

    const Reflection* ref = message->GetReflection();

    if (value == R_NilValue || (Rf_isVector(value) && LENGTH(value) == 0)) {
        ref->ClearField(message, field_desc);
        return R_NilValue;
    }

    // {{{ preliminary checks
    R_xlen_t value_size = 1;
    if (Rf_isVector(value)) {
        if (IS_LONG_VEC(value)) {
            // field_size is an int, so presumably it would generate
            // a CHECK failure in protobuf code on 2^32 element anyway.
            Rcpp_error("Long vectors not supported for repeated fields.");
        } else {
            value_size = LENGTH(value);
        }
    }

    // if the R type is RAWSXP and the cpp type is string or bytes,
    // then value_size is actually one because the raw vector
    // is converted to a string
    GPB::FieldDescriptor::Type field_type = field_desc->type();
    if (field_type == TYPE_STRING || field_type == TYPE_BYTES) {
        if (TYPEOF(value) == RAWSXP) {
            value_size = 1;
        } else if (TYPEOF(value) == STRSXP) {
            value_size = LENGTH(value);
        } else if (TYPEOF(value) == S4SXP && Rf_inherits(value, "Message")) {
            value_size = 1; /* we will store the message payload */
        } else if (TYPEOF(value) == VECSXP && allAreMessages(value)) {
            value_size = LENGTH(value);
        } else if (TYPEOF(value) == VECSXP && allAreRaws(value)) {
            value_size = LENGTH(value);
        } else {
            Rcpp::stop("cannot convert to string");
        }
    }
    // }}}

    if (field_desc->is_repeated()) {
        setRepeatedMessageField(message, ref, field_desc, value, value_size);
    } else {
        setNonRepeatedMessageField(message, ref, field_desc, value, value_size);
    }
    RPB_DEBUG_END("setMessageField")
    END_RCPP
}

RPB_FUNCTION_VOID_2(update_message, Rcpp::XPtr<GPB::Message> message, Rcpp::List list) {
    Rcpp::CharacterVector names = list.attr("names");
    int n = list.size();
    for (int i = 0; i < n; i++) {
        (void)setMessageField(message, names[i], list[i]);
    }
}

}  // namespace rprotobuf
