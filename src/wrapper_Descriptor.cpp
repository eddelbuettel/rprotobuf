// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "RcppMacros.h"

namespace rprotobuf {

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Descriptor__, __NAME__)

RPB_XP_METHOD_0(METHOD(as_character), GPB::Descriptor, DebugString)
RPB_XP_METHOD_0(METHOD(field_count), GPB::Descriptor, field_count)
RPB_XP_METHOD_0(METHOD(nested_type_count), GPB::Descriptor, nested_type_count)
RPB_XP_METHOD_0(METHOD(enum_type_count), GPB::Descriptor, enum_type_count)

RPB_XP_METHOD_CAST_0(METHOD(containing_type), GPB::Descriptor, containing_type, S4_Descriptor)

/**
 * returns the names of the members contained in the descriptor
 * (nested types, enums, fields)
 *
 * @param xp external pointer to a Descriptor
 *
 * @return member names, as an R character vector (STRSXP)
 */
RPB_FUNCTION_1(Rcpp::CharacterVector, METHOD(getMemberNames), Rcpp::XPtr<GPB::Descriptor> desc) {

    int nfields = desc->field_count();
    int ntypes = desc->nested_type_count();
    int nenums = desc->enum_type_count();

    Rcpp::CharacterVector res(nfields + ntypes + nenums);
    int j = 0;
    for (int i = 0; i < nfields; i++, j++) {
        res[j] = std::string(desc->field(i)->name());
    }
    for (int i = 0; i < ntypes; i++, j++) {
        res[j] = std::string(desc->nested_type(i)->name());
    }
    for (int i = 0; i < nenums; i++, j++) {
        res[j] = std::string(desc->enum_type(i)->name());
    }
    return (res);
}

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RPB_FUNCTION_1(Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::Descriptor> desc) {

    int nfields = desc->field_count();
    int ntypes = desc->nested_type_count();
    int nenums = desc->enum_type_count();
    int n = nfields + ntypes + nenums;

    Rcpp::CharacterVector names(n);
    Rcpp::List res(n);
    int cnt = 0;
    for (int i = 0; i < nfields; cnt++, i++) {
        const GPB::FieldDescriptor* fd = desc->field(i);
        res[cnt] = S4_FieldDescriptor(fd);
        names[cnt] = std::string(fd->name());
    }
    for (int i = 0; i < ntypes; cnt++, i++) {
        const GPB::Descriptor* d = desc->nested_type(i);
        res[cnt] = S4_Descriptor(d);
        names[cnt] = std::string(d->name());
    }
    for (int i = 0; i < nenums; cnt++, i++) {
        const GPB::EnumDescriptor* ed = desc->enum_type(i);
        res[cnt] = S4_EnumDescriptor(ed);
        names[cnt] = std::string(ed->name());
    }
    res.names() = names;

    return res;
}

RPB_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::Descriptor> d) {
    GPB::DescriptorProto* message = new GPB::DescriptorProto();
    d->CopyTo(message);
    return message;
}

RPB_FUNCTION_2(S4_FieldDescriptor, METHOD(field), Rcpp::XPtr<GPB::Descriptor> d, int i) {
    return d->field(i);
}

RPB_FUNCTION_2(S4_FieldDescriptor, METHOD(FindFieldByNumber), Rcpp::XPtr<GPB::Descriptor> d,
               int num) {
    return d->FindFieldByNumber(num);
}

RPB_FUNCTION_2(S4_FieldDescriptor, METHOD(FindFieldByName), Rcpp::XPtr<GPB::Descriptor> d,
               std::string nam) {
    return d->FindFieldByName(nam);
}

RPB_FUNCTION_2(S4_Descriptor, METHOD(nested_type), Rcpp::XPtr<GPB::Descriptor> d, int i) {
    return d->nested_type(i);
}

RPB_FUNCTION_2(S4_Descriptor, METHOD(FindNestedTypeByName), Rcpp::XPtr<GPB::Descriptor> d,
               std::string nam) {
    return d->FindNestedTypeByName(nam);
}

RPB_FUNCTION_2(S4_EnumDescriptor, METHOD(enum_type), Rcpp::XPtr<GPB::Descriptor> d, int i) {
    return d->enum_type(i);
}

// FIXME: two methods cant have the same name
// RPB_FUNCTION_2( S4_EnumDescriptor, METHOD(enum_type),
// Rcpp::XPtr<GPB::Descriptor> d, std::string name){
// 	return d->FindEnumTypeByName( i ) ;
// }

RPB_FUNCTION_1(S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::Descriptor> desc) {
    return S4_FileDescriptor(desc->file());
}

RPB_FUNCTION_2(std::string, METHOD(name), Rcpp::XPtr<GPB::Descriptor> d, bool full) {
    return std::string(full ? d->full_name() : d->name());
}

RPB_FUNCTION_2(S4_Message, METHOD(readMessageFromFile), Rcpp::XPtr<GPB::Descriptor> desc,
               std::string filename) {
    /* open the file to read in binary mode */
    int file = open(filename.c_str(), O_RDONLY | O_BINARY);

    /* create a prototype of the message we are going to read */
    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        throw std::range_error("could not call factory->GetPrototype(desc)->New()");
    }

    /* read the message from the file */
    // TODO(mstokely): Check return value!
    message->ParsePartialFromFileDescriptor(file);
    close(file);
    return (S4_Message(message));
}

RPB_FUNCTION_2(S4_Message, METHOD(readMessageFromConnection), Rcpp::XPtr<GPB::Descriptor> desc,
               int conn_id) {
    RconnectionCopyingInputStream wrapper(conn_id);
    GPB::io::CopyingInputStreamAdaptor stream(&wrapper);
    GPB::io::CodedInputStream coded_stream(&stream);

    /* create a prototype of the message we are going to read */
    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        throw std::range_error("could not call factory->GetPrototype(desc)->New()");
    }
    // TODO(mstokely): Check return value!
    message->ParsePartialFromCodedStream(&coded_stream);

    S4_Message res(message);
    return res;
}

RPB_FUNCTION_2(S4_Message, METHOD(readMessageFromRawVector), Rcpp::XPtr<GPB::Descriptor> desc,
               Rcpp::RawVector raw) {
    GPB::io::ArrayInputStream ais((void*)raw.begin(), raw.size());
    GPB::io::CodedInputStream stream(&ais);

    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        throw std::range_error("could not call factory->GetPrototype(desc)->New()");
    }

    message->MergePartialFromCodedStream(&stream);
    return (S4_Message(message));
}

RPB_FUNCTION_3(S4_Message, METHOD(readASCIIFromString), Rcpp::XPtr<GPB::Descriptor> desc,
               std::string input, bool partial) {
    GPB::Message* message = PROTOTYPE(desc);
    if (partial) {
        // Allow partial messages where object is not fully initialized
        GPB::TextFormat::Parser parser;
        parser.AllowPartialMessage(partial);
        if (parser.ParseFromString(input, message)) {
            return (S4_Message(message));
        } else {
            throw std::range_error("Could not parse ASCII protocol buffer from text string.");
        }
    } else {
        // Default parser requires fully initialized ascii messages.
        if (GPB::TextFormat::ParseFromString(input, message)) {
            return (S4_Message(message));
        } else {
            throw std::range_error("Could not parse ASCII protocol buffer from text string."
                                   " Consider setting partial=TRUE");
        }
    }
}

RPB_FUNCTION_3(S4_Message, METHOD(readASCIIFromConnection), Rcpp::XPtr<GPB::Descriptor> desc,
               int conn_id, bool partial) {
    RconnectionCopyingInputStream wrapper(conn_id);
    GPB::io::CopyingInputStreamAdaptor stream(&wrapper);

    /* create a prototype of the message we are going to read */
    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        throw std::range_error("could not call factory->GetPrototype(desc)->New()");
    }
    if (partial) {
        // Allow partial messages where object is not fully initialized
        GPB::TextFormat::Parser parser;
        parser.AllowPartialMessage(partial);
        if (!parser.Parse(&stream, message)) {
            throw std::range_error("Could not parse ASCII protocol buffer.");
        }
    } else {
        // Default parser requires fully initialized ascii messages.
        if (!GPB::TextFormat::Parse(&stream, message)) {
            throw std::range_error("Could not parse ASCII protocol buffer.");
        }
    }
    if (wrapper.Failure()) {
        throw std::range_error("Could not read ASCII protocol buffer.");
    }
    return (S4_Message(message));
}

RPB_FUNCTION_2(S4_Message, METHOD(readJSONFromString), Rcpp::XPtr<GPB::Descriptor> desc,
               std::string input) {
#ifdef PROTOBUF_JSON_UTIL
    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        Rcpp::stop("could not call factory->GetPrototype(desc)->New()");
    }
    #if GOOGLE_PROTOBUF_VERSION < 4022000
        GPB::util::Status status = GPB::util::JsonStringToMessage(input, message);
    #else
        absl::Status status = GPB::util::JsonStringToMessage(input, message);
    #endif
    if (!status.ok()) {
        Rcpp::stop(status.ToString().c_str());
    }
    return (S4_Message(message));
#else
    Rcpp::stop(
        "The protobuf library you are using is too old for using JSON utility functions, "
        "please upgrade to version 3 or above.");
#endif
}

RPB_FUNCTION_2(S4_Message, METHOD(readJSONFromConnection), Rcpp::XPtr<GPB::Descriptor> desc,
               int conn_id) {
#ifdef PROTOBUF_JSON_UTIL
    std::string json_string;
    RconnectionCopyingInputStream wrapper(conn_id);
    GPB::io::CopyingInputStreamAdaptor stream(&wrapper);
    const void* buffer;
    int size;
    while (stream.Next(&buffer, &size)) {
        json_string.append((char *) buffer, size);
    }
    if (wrapper.Failure()) {
        Rcpp::stop("Could not read JSON protocol buffer.");
    }

    /* create a prototype of the message we are going to read */
    GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        Rcpp::stop("could not call factory->GetPrototype(desc)->New()");
    }
    #if GOOGLE_PROTOBUF_VERSION < 4022000
        GPB::util::Status status = GPB::util::JsonStringToMessage(json_string, message);
    #else
        absl::Status status = GPB::util::JsonStringToMessage(json_string, message);
    #endif
    if (!status.ok()) {
        Rcpp::stop(status.ToString().c_str());
    }
    return (S4_Message(message));
#else
    Rcpp::stop(
        "The protobuf library you are using is too old for using JSON utility functions, "
        "please upgrade to version 3 or above.");
#endif
}

RcppExport SEXP Descriptor_getField(SEXP pointer, SEXP name) {
    GPB::FieldDescriptor* field_desc = (GPB::FieldDescriptor*)0;
    BEGIN_RCPP
    std::string error_message = "could not get FieldDescriptor for field";
    SEXP retVal = R_NilValue;
    switch (TYPEOF(name)) {
        case CHARSXP:
        case STRSXP:
            // This tries to get the field by name for various types of descriptors.
            retVal = do_dollar_Descriptor(pointer, name);
            if (retVal == R_NilValue) {
                error_message = "Unknown field";
            } else {
                return retVal;
            }
            break;
        default: {
            error_message = "Invalid type for get field extractor.";
            break;
        }
    }
    if (!field_desc) {
        Rcpp::stop(error_message.c_str());
    }
    return S4_FieldDescriptor(field_desc);
    VOID_END_RCPP
    return S4_FieldDescriptor(field_desc);
}

#undef METHOD

}  // namespace rprotobuf
