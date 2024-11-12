// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "DescriptorPoolLookup.h"
#include "RcppMacros.h"

namespace rprotobuf {

GPB::Message* PROTOTYPE(const GPB::Descriptor* desc) {
    RPB_DEBUG_BEGIN("PROTOTYPE")
#ifdef RPB_DEBUG
    Rprintf("desc = %d\n", desc);
#endif
    /* first try the runtime factory */
    GPB::Message* m = (GPB::Message*)((GPB::DynamicMessageFactory*)DescriptorPoolLookup::factory())
                          ->GetPrototype(desc)
                          ->New();

#ifdef RPB_DEBUG
    Rprintf("generated factory = %d\n", m);
#endif
    if (!m) {
        /* then the dynamic runtime factory */
        m = (GPB::Message*)GPB::MessageFactory::generated_factory()->GetPrototype(desc)->New();
#ifdef RPB_DEBUG
        Rprintf("runtime  factory = %d\n", m);
#endif
    }
    RPB_DEBUG_END("PROTOTYPE")
    return m;
}

GPB::Message* CLONE(const GPB::Message* origin) {
    RPB_DEBUG_BEGIN("CLONE")
    const GPB::Descriptor* desc = origin->GetDescriptor();
    GPB::Message* sheep = PROTOTYPE(desc);
    sheep->CopyFrom(*origin);
    RPB_DEBUG_END("CLONE")
    return sheep;
}

/**
 * read a proto file and cache the message definitions it contains
 *
 * @param file proto file name
 */
RcppExport SEXP readProtoFiles_cpp(SEXP file, SEXP dirs) {
    BEGIN_RCPP
    DescriptorPoolLookup::importProtoFiles(file, dirs);
    return R_NilValue;
    END_RCPP
}

/**
 * reset the descriptor pool, clearing all persisted state
 */
RcppExport SEXP resetDescriptorPool_cpp() {
    BEGIN_RCPP
    DescriptorPoolLookup::reset();
    return R_NilValue;
    END_RCPP
}

/**
 * get the descriptor associated with a message type
 *
 * @param type message type
 *
 * @return an S4 object of class Descriptor, or NULL if the type
 *  is unknown
 */
RcppExport SEXP getProtobufDescriptor(SEXP type) {

#ifdef RPB_DEBUG
    Rprintf("<getProtobufDescriptor>\n      type = ");
    Rf_PrintValue(type);
#endif

    const char* typeName = CHAR(STRING_ELT(type, 0));

    /* first try the generated pool */
    const GPB::DescriptorPool* pool = GPB::DescriptorPool::generated_pool();
    const GPB::Descriptor* desc = pool->FindMessageTypeByName(typeName);
    if (!desc) {
        /* then try the "runtime" pool" */
        pool = DescriptorPoolLookup::pool();
        desc = pool->FindMessageTypeByName(typeName);
        if (!desc) {
            /* unlucky */
            return R_NilValue;
        }
    }

    return (S4_Descriptor(desc));
}

/**
 * get the descriptor associated with an extension
 *
 * @param type message type
 *
 * @return an S4 object of class FieldDescriptor, or NULL if the type
 *  is unknown
 */
RcppExport SEXP getExtensionDescriptor(SEXP type) {
#ifdef RPB_DEBUG
    Rprintf("<getExtensionDescriptor>\n      type = ");
    Rf_PrintValue(type);
#endif

    const char* typeName = CHAR(STRING_ELT(type, 0));

    /* first try the generated pool */
    const GPB::DescriptorPool* pool = GPB::DescriptorPool::generated_pool();
    const GPB::FieldDescriptor* desc = pool->FindExtensionByName(typeName);
    if (!desc) {
        /* then try the "runtime" pool" */
        pool = DescriptorPoolLookup::pool();
        desc = pool->FindExtensionByName(typeName);
        if (!desc) {
            /* unlucky */
            return R_NilValue;
        }
    }

    return (S4_FieldDescriptor(desc));
}

/**
 * get the descriptor associated with an enum
 *
 * @param type message type
 *
 * @return an S4 object of class EnumDescriptor, or NULL if the type
 *  is unknown
 */
RcppExport SEXP getEnumDescriptor(SEXP type) {
#ifdef RPB_DEBUG
    Rprintf("<getEnumDescriptor>\n      type = ");
    Rf_PrintValue(type);
#endif

    const char* typeName = CHAR(STRING_ELT(type, 0));

    /* first try the generated pool */
    const GPB::DescriptorPool* pool = GPB::DescriptorPool::generated_pool();
    const GPB::EnumDescriptor* desc = pool->FindEnumTypeByName(typeName);
    if (!desc) {
        /* then try the "runtime" pool" */
        pool = DescriptorPoolLookup::pool();
        desc = pool->FindEnumTypeByName(typeName);
        if (!desc) {
            /* unlucky */
            return R_NilValue;
        }
    }

    return (S4_EnumDescriptor(desc));
}

/**
 * make a new protobuf message
 *
 * @param descriptor a "Descriptor" R object
 */
SEXP newProtoMessage(SEXP descriptor) {
    BEGIN_RCPP
    RPB_DEBUG_BEGIN("newProtoMessage")
#ifdef RPB_DEBUG
    /* FIXME: the message type, we don't really need that*/
    SEXP type = GET_SLOT(descriptor, Rf_install("type"));
#endif

    /* the pointer to the c++ descriptor object */
    GPB::Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_S4(descriptor);

#ifdef RPB_DEBUG
    Rprintf("desc = %d\n", desc);
    PRINT_DEBUG_INFO("type", type);
#endif

    /* grab the Message from the factory */
    const GPB::Message* message = PROTOTYPE(desc);
    if (!message) {
        Rcpp_error("could not call factory->GetPrototype(desc)->New()");
    }
    RPB_DEBUG_END("newProtoMessage")

    return (S4_Message(message));
    END_RCPP
}

/**
 * dollar extractor for Descriptor objects
 * it may return a Field descriptor or a nested type descriptor
 *
 * @param pointer external pointer to a google::protobuf::Descriptor object
 * @param name name of the thing to extract
 */
RcppExport SEXP do_dollar_Descriptor(SEXP pointer, SEXP name) {

    const char* what = CHAR(STRING_ELT(name, 0));
    GPB::Descriptor* desc = (GPB::Descriptor*)EXTPTR_PTR(pointer);

    // trying fields first :

    if (desc->field_count()) {
        const GPB::FieldDescriptor* fd = desc->FindFieldByName(what);
        if (fd) {
            return (S4_FieldDescriptor(fd));
        }
    }

    // now trying nested types
    if (desc->nested_type_count()) {
        const GPB::Descriptor* d = desc->FindNestedTypeByName(what);
        if (d) {
            return (S4_Descriptor(d));
        }
    }

    // now for enum types
    if (desc->enum_type_count()) {
        const GPB::EnumDescriptor* ed = desc->FindEnumTypeByName(what);
        if (ed) {
            return (S4_EnumDescriptor(ed));
        }
    }

    // TODO: extensions (later)

    // give up
    // TODO: should this be unbound instead
    return (R_NilValue);
}

/**
 *
 * @param m potentially a message
 * @param target the expected type
 *
 * @return TRUE if m is a a message of the given type
 */
Rboolean isMessage(SEXP m, std::string_view target) {
    RPB_DEBUG_BEGIN("isMessage")

    if (TYPEOF(m) != S4SXP || !Rf_inherits(m, "Message")) return _FALSE_;

    GPB::Message* message = (GPB::Message*)EXTPTR_PTR(GET_SLOT(m, Rf_install("pointer")));

    std::string_view type = message->GetDescriptor()->full_name();
    RPB_DEBUG_END("isMessage")
    if (type != target) {
        return _FALSE_;
    }
    return _TRUE_;
}

RcppExport GPB::FieldDescriptor* getFieldDescriptor(const GPB::Message* message, SEXP name) {
    GPB::FieldDescriptor* field_desc = (GPB::FieldDescriptor*)0;
    BEGIN_RCPP
    const GPB::Descriptor* desc = message->GetDescriptor();
    std::string error_message = "could not get FieldDescriptor for field";
    switch (TYPEOF(name)) {
        case S4SXP: {
            if (Rf_inherits(name, "FieldDescriptor")) {
                field_desc = GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(name);
            } else {
                Rcpp::stop("S4 class is not a FieldDescriptor");
            }
            break;
        }
        case CHARSXP: {
            field_desc = (GPB::FieldDescriptor*)desc->FindFieldByName(CHAR(name));
            error_message = error_message + " '" + CHAR(name) + "'";
            break;
        }
        case STRSXP: {
            field_desc = (GPB::FieldDescriptor*)desc->FindFieldByName(CHAR(STRING_ELT(name, 0)));
            error_message = error_message + " '" + CHAR(STRING_ELT(name, 0)) + "'";
            break;
        }
        case REALSXP:
        case INTSXP: {
            field_desc = (GPB::FieldDescriptor*)desc->FindFieldByNumber(Rcpp::as<int>(name));
            break;
        }
    }
    if (!field_desc) {
        Rcpp::stop(error_message.c_str());
    }
    return field_desc;
    VOID_END_RCPP
    return field_desc;
}

RPB_FUNCTION_VOID_1(check_libprotobuf_version, int minversion) {
    if (GOOGLE_PROTOBUF_VERSION < minversion) {
        throw std::range_error(
            "The protobuf library you are using is too old for this package, "
            "please upgrade");
    }
}

RPB_FUNCTION_0(int, get_protobuf_library_version) { return GOOGLE_PROTOBUF_VERSION; }

}  // namespace rprotobuf
