#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/*
  The following name(s) appear with different usages
  e.g., with different numbers of arguments:

    Message__clone

  This needs to be resolved in the tables and any declarations.

  DE 2017-03-05: Resolved, second entry with two arguments was in error
*/

/*
  DE 2017-03-05:
   - Below several entries were commented out as unresolvable
   - A few were renamed with suffix _cpp to avoid name clash with R symbols of
     the same name as we also enable .registration=TRUE in useDynLib in NAMESPACE
*/

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP all_equal_messages(SEXP, SEXP, SEXP);
extern SEXP ArrayInputStream__new(SEXP, SEXP);
extern SEXP ArrayOutputStream__new(SEXP, SEXP);
extern SEXP ConnectionInputStream_new(SEXP, SEXP);
extern SEXP ConnectionOutputStream_new(SEXP, SEXP);
extern SEXP Descriptor__as_character(SEXP);
extern SEXP Descriptor__as_list(SEXP);
extern SEXP Descriptor__as_Message(SEXP);
extern SEXP Descriptor__containing_type(SEXP);
extern SEXP Descriptor__enum_type(SEXP, SEXP);
extern SEXP Descriptor__enum_type_count(SEXP);
extern SEXP Descriptor__field(SEXP, SEXP);
extern SEXP Descriptor__field_count(SEXP);
extern SEXP Descriptor__fileDescriptor(SEXP);
/*extern SEXP Descriptor__FindEnumTypeByName(SEXP, SEXP);*/
extern SEXP Descriptor__FindFieldByName(SEXP, SEXP);
extern SEXP Descriptor__FindFieldByNumber(SEXP, SEXP);
extern SEXP Descriptor__FindNestedTypeByName(SEXP, SEXP);
extern SEXP Descriptor__getMemberNames(SEXP);
extern SEXP Descriptor__name(SEXP, SEXP);
extern SEXP Descriptor__nested_type(SEXP, SEXP);
extern SEXP Descriptor__nested_type_count(SEXP);
extern SEXP Descriptor__readASCIIFromConnection(SEXP, SEXP, SEXP);
extern SEXP Descriptor__readASCIIFromString(SEXP, SEXP, SEXP);
extern SEXP Descriptor__readJSONFromConnection(SEXP, SEXP);
extern SEXP Descriptor__readJSONFromString(SEXP, SEXP);
extern SEXP Descriptor__readMessageFromConnection(SEXP, SEXP);
extern SEXP Descriptor__readMessageFromFile(SEXP, SEXP);
extern SEXP Descriptor__readMessageFromRawVector(SEXP, SEXP);
extern SEXP Descriptor_getField(SEXP, SEXP);
extern SEXP do_dollar_Descriptor(SEXP, SEXP);
extern SEXP EnumDescriptor__as_character(SEXP);
extern SEXP EnumDescriptor__as_list(SEXP);
extern SEXP EnumDescriptor__as_Message(SEXP);
extern SEXP EnumDescriptor__containing_type(SEXP);
extern SEXP EnumDescriptor__fileDescriptor(SEXP);
extern SEXP EnumDescriptor__getConstantNames(SEXP);
extern SEXP EnumDescriptor__getValueByIndex(SEXP, SEXP);
extern SEXP EnumDescriptor__getValueByName(SEXP, SEXP);
extern SEXP EnumDescriptor__getValueByNumber(SEXP, SEXP);
extern SEXP EnumDescriptor__length(SEXP);
extern SEXP EnumDescriptor__name(SEXP, SEXP);
extern SEXP EnumDescriptor__value_count(SEXP);
extern SEXP EnumValueDescriptor__as_character(SEXP);
extern SEXP EnumValueDescriptor__as_Message(SEXP);
extern SEXP EnumValueDescriptor__enum_type(SEXP);
extern SEXP EnumValueDescriptor__number(SEXP);
extern SEXP FieldDescriptor__as_character(SEXP);
extern SEXP FieldDescriptor__as_Message(SEXP);
extern SEXP FieldDescriptor__containing_type(SEXP);
extern SEXP FieldDescriptor__cpp_type(SEXP);
extern SEXP FieldDescriptor__default_value(SEXP);
extern SEXP FieldDescriptor__enum_type(SEXP);
extern SEXP FieldDescriptor__fileDescriptor(SEXP);
extern SEXP FieldDescriptor__has_default_value(SEXP);
extern SEXP FieldDescriptor__is_extension(SEXP);
extern SEXP FieldDescriptor__is_optional(SEXP);
extern SEXP FieldDescriptor__is_repeated(SEXP);
extern SEXP FieldDescriptor__is_required(SEXP);
extern SEXP FieldDescriptor__label(SEXP);
extern SEXP FieldDescriptor__message_type(SEXP);
extern SEXP FieldDescriptor__name(SEXP, SEXP);
extern SEXP FieldDescriptor__number(SEXP);
extern SEXP FieldDescriptor__type(SEXP);
extern SEXP FileDescriptor__as_character(SEXP);
extern SEXP FileDescriptor__as_list(SEXP);
extern SEXP FileDescriptor__as_Message(SEXP);
extern SEXP FileDescriptor__getMemberNames(SEXP);
extern SEXP FileDescriptor__name(SEXP);
extern SEXP FileInputStream_Close(SEXP);
extern SEXP FileInputStream_GetErrno(SEXP);
extern SEXP FileInputStream_new(SEXP, SEXP, SEXP);
extern SEXP FileInputStream_SetCloseOnDelete(SEXP, SEXP);
extern SEXP FileOutputStream_Close(SEXP);
extern SEXP FileOutputStream_Flush(SEXP);
extern SEXP FileOutputStream_GetErrno(SEXP);
extern SEXP FileOutputStream_new(SEXP, SEXP, SEXP);
extern SEXP FileOutputStream_SetCloseOnDelete(SEXP, SEXP);
/*extern SEXP get_method_input_type(SEXP);*/
extern SEXP get_method_output_prototype(SEXP);
extern SEXP get_protobuf_library_version();
extern SEXP get_value_of_enum(SEXP, SEXP);
extern SEXP getEnumDescriptor(SEXP);
extern SEXP getExtension_cpp(SEXP, SEXP);
extern SEXP getExtensionDescriptor(SEXP);
extern SEXP getMessageField(SEXP, SEXP);
extern SEXP getProtobufDescriptor(SEXP);
extern SEXP has_enum_name(SEXP, SEXP);
extern SEXP identical_messages(SEXP, SEXP);
extern SEXP Message__add_values(SEXP, SEXP, SEXP);
extern SEXP Message__as_character(SEXP);
extern SEXP Message__as_json(SEXP);
extern SEXP Message__as_list(SEXP);
extern SEXP Message__bytesize(SEXP);
extern SEXP Message__clear(SEXP);
extern SEXP Message__clear_field(SEXP, SEXP);
extern SEXP Message__clone(SEXP);
/*extern SEXP Message__clone(SEXP, SEXP);*/
extern SEXP Message__descriptor(SEXP);
extern SEXP Message__field_exists(SEXP, SEXP);
extern SEXP Message__field_size(SEXP, SEXP);
extern SEXP Message__fieldNames(SEXP);
extern SEXP Message__fileDescriptor(SEXP);
extern SEXP Message__get_field_values(SEXP, SEXP, SEXP);
extern SEXP Message__get_payload(SEXP);
extern SEXP Message__has_field(SEXP, SEXP);
extern SEXP Message__is_initialized(SEXP);
extern SEXP Message__length(SEXP);
extern SEXP Message__merge(SEXP, SEXP);
extern SEXP Message__num_extensions(SEXP);
extern SEXP Message__serialize_to_file(SEXP, SEXP);
extern SEXP Message__set_field_size(SEXP, SEXP, SEXP);
extern SEXP Message__set_field_values(SEXP, SEXP, SEXP, SEXP);
extern SEXP Message__swap(SEXP, SEXP, SEXP, SEXP);
extern SEXP MethodDescriptor__as_character(SEXP);
extern SEXP MethodDescriptor__as_Message(SEXP);
extern SEXP MethodDescriptor__fileDescriptor(SEXP);
extern SEXP MethodDescriptor__input_type(SEXP);
extern SEXP MethodDescriptor__name(SEXP, SEXP);
extern SEXP MethodDescriptor__output_type(SEXP);
extern SEXP newProtocolBufferLookup(SEXP);
extern SEXP newProtoMessage(SEXP);
extern SEXP readProtoFiles_cpp(SEXP, SEXP);
extern SEXP resetDescriptorPool_cpp();
extern SEXP ServiceDescriptor__as_character(SEXP);
extern SEXP ServiceDescriptor__as_list(SEXP);
extern SEXP ServiceDescriptor__as_Message(SEXP);
extern SEXP ServiceDescriptor__fileDescriptor(SEXP);
extern SEXP ServiceDescriptor__getMethodNames(SEXP);
/*extern SEXP ServiceDescriptor__method(SEXP, SEXP);*/
extern SEXP ServiceDescriptor__name(SEXP, SEXP);
/*extern SEXP ServiceDescriptor_getMethodByIndex(SEXP, SEXP);*/
/*extern SEXP ServiceDescriptor_getMethodByName(SEXP, SEXP);*/
/*extern SEXP ServiceDescriptor_method_count(SEXP);*/
extern SEXP setMessageField(SEXP, SEXP, SEXP);
extern SEXP update_message(SEXP, SEXP);
extern SEXP valid_input_message(SEXP, SEXP);
extern SEXP valid_output_message(SEXP, SEXP);
extern SEXP ZeroCopyInputStream_BackUp(SEXP, SEXP);
extern SEXP ZeroCopyInputStream_ByteCount(SEXP);
extern SEXP ZeroCopyInputStream_Next(SEXP);
extern SEXP ZeroCopyInputStream_ReadLittleEndian32(SEXP);
extern SEXP ZeroCopyInputStream_ReadLittleEndian64(SEXP);
extern SEXP ZeroCopyInputStream_ReadRaw(SEXP, SEXP);
extern SEXP ZeroCopyInputStream_ReadString(SEXP, SEXP);
extern SEXP ZeroCopyInputStream_ReadVarint32(SEXP);
extern SEXP ZeroCopyInputStream_ReadVarint64(SEXP);
extern SEXP ZeroCopyInputStream_Skip(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_BackUp(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_ByteCount(SEXP);
extern SEXP ZeroCopyOutputStream_Next(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteLittleEndian32(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteLittleEndian64(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteRaw(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteString(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteVarint32(SEXP, SEXP);
extern SEXP ZeroCopyOutputStream_WriteVarint64(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"all_equal_messages",                       (DL_FUNC) &all_equal_messages,                        3},
    {"ArrayInputStream__new",                    (DL_FUNC) &ArrayInputStream__new,                     2},
    {"ArrayOutputStream__new",                   (DL_FUNC) &ArrayOutputStream__new,                    2},
    {"ConnectionInputStream_new",                (DL_FUNC) &ConnectionInputStream_new,                 2},
    {"ConnectionOutputStream_new",               (DL_FUNC) &ConnectionOutputStream_new,                2},
    {"Descriptor__as_character",                 (DL_FUNC) &Descriptor__as_character,                  1},
    {"Descriptor__as_list",                      (DL_FUNC) &Descriptor__as_list,                       1},
    {"Descriptor__as_Message",                   (DL_FUNC) &Descriptor__as_Message,                    1},
    {"Descriptor__containing_type",              (DL_FUNC) &Descriptor__containing_type,               1},
    {"Descriptor__enum_type",                    (DL_FUNC) &Descriptor__enum_type,                     2},
    {"Descriptor__enum_type_count",              (DL_FUNC) &Descriptor__enum_type_count,               1},
    {"Descriptor__field",                        (DL_FUNC) &Descriptor__field,                         2},
    {"Descriptor__field_count",                  (DL_FUNC) &Descriptor__field_count,                   1},
    {"Descriptor__fileDescriptor",               (DL_FUNC) &Descriptor__fileDescriptor,                1},
/*    {"Descriptor__FindEnumTypeByName",           (DL_FUNC) &Descriptor__FindEnumTypeByName,            2}, */
    {"Descriptor__FindFieldByName",              (DL_FUNC) &Descriptor__FindFieldByName,               2},
    {"Descriptor__FindFieldByNumber",            (DL_FUNC) &Descriptor__FindFieldByNumber,             2},
    {"Descriptor__FindNestedTypeByName",         (DL_FUNC) &Descriptor__FindNestedTypeByName,          2},
    {"Descriptor__getMemberNames",               (DL_FUNC) &Descriptor__getMemberNames,                1},
    {"Descriptor__name",                         (DL_FUNC) &Descriptor__name,                          2},
    {"Descriptor__nested_type",                  (DL_FUNC) &Descriptor__nested_type,                   2},
    {"Descriptor__nested_type_count",            (DL_FUNC) &Descriptor__nested_type_count,             1},
    {"Descriptor__readASCIIFromConnection",      (DL_FUNC) &Descriptor__readASCIIFromConnection,       3},
    {"Descriptor__readASCIIFromString",          (DL_FUNC) &Descriptor__readASCIIFromString,           3},
    {"Descriptor__readJSONFromConnection",       (DL_FUNC) &Descriptor__readJSONFromConnection,        2},
    {"Descriptor__readJSONFromString",           (DL_FUNC) &Descriptor__readJSONFromString,            2},
    {"Descriptor__readMessageFromConnection",    (DL_FUNC) &Descriptor__readMessageFromConnection,     2},
    {"Descriptor__readMessageFromFile",          (DL_FUNC) &Descriptor__readMessageFromFile,           2},
    {"Descriptor__readMessageFromRawVector",     (DL_FUNC) &Descriptor__readMessageFromRawVector,      2},
    {"Descriptor_getField",                      (DL_FUNC) &Descriptor_getField,                       2},
    {"do_dollar_Descriptor",                     (DL_FUNC) &do_dollar_Descriptor,                      2},
    {"EnumDescriptor__as_character",             (DL_FUNC) &EnumDescriptor__as_character,              1},
    {"EnumDescriptor__as_list",                  (DL_FUNC) &EnumDescriptor__as_list,                   1},
    {"EnumDescriptor__as_Message",               (DL_FUNC) &EnumDescriptor__as_Message,                1},
    {"EnumDescriptor__containing_type",          (DL_FUNC) &EnumDescriptor__containing_type,           1},
    {"EnumDescriptor__fileDescriptor",           (DL_FUNC) &EnumDescriptor__fileDescriptor,            1},
    {"EnumDescriptor__getConstantNames",         (DL_FUNC) &EnumDescriptor__getConstantNames,          1},
    {"EnumDescriptor__getValueByIndex",          (DL_FUNC) &EnumDescriptor__getValueByIndex,           2},
    {"EnumDescriptor__getValueByName",           (DL_FUNC) &EnumDescriptor__getValueByName,            2},
    {"EnumDescriptor__getValueByNumber",         (DL_FUNC) &EnumDescriptor__getValueByNumber,          2},
    {"EnumDescriptor__length",                   (DL_FUNC) &EnumDescriptor__length,                    1},
    {"EnumDescriptor__name",                     (DL_FUNC) &EnumDescriptor__name,                      2},
    {"EnumDescriptor__value_count",              (DL_FUNC) &EnumDescriptor__value_count,               1},
    {"EnumValueDescriptor__as_character",        (DL_FUNC) &EnumValueDescriptor__as_character,         1},
    {"EnumValueDescriptor__as_Message",          (DL_FUNC) &EnumValueDescriptor__as_Message,           1},
    {"EnumValueDescriptor__enum_type",           (DL_FUNC) &EnumValueDescriptor__enum_type,            1},
    {"EnumValueDescriptor__number",              (DL_FUNC) &EnumValueDescriptor__number,               1},
    {"FieldDescriptor__as_character",            (DL_FUNC) &FieldDescriptor__as_character,             1},
    {"FieldDescriptor__as_Message",              (DL_FUNC) &FieldDescriptor__as_Message,               1},
    {"FieldDescriptor__containing_type",         (DL_FUNC) &FieldDescriptor__containing_type,          1},
    {"FieldDescriptor__cpp_type",                (DL_FUNC) &FieldDescriptor__cpp_type,                 1},
    {"FieldDescriptor__default_value",           (DL_FUNC) &FieldDescriptor__default_value,            1},
    {"FieldDescriptor__enum_type",               (DL_FUNC) &FieldDescriptor__enum_type,                1},
    {"FieldDescriptor__fileDescriptor",          (DL_FUNC) &FieldDescriptor__fileDescriptor,           1},
    {"FieldDescriptor__has_default_value",       (DL_FUNC) &FieldDescriptor__has_default_value,        1},
    {"FieldDescriptor__is_extension",            (DL_FUNC) &FieldDescriptor__is_extension,             1},
    {"FieldDescriptor__is_optional",             (DL_FUNC) &FieldDescriptor__is_optional,              1},
    {"FieldDescriptor__is_repeated",             (DL_FUNC) &FieldDescriptor__is_repeated,              1},
    {"FieldDescriptor__is_required",             (DL_FUNC) &FieldDescriptor__is_required,              1},
    {"FieldDescriptor__label",                   (DL_FUNC) &FieldDescriptor__label,                    1},
    {"FieldDescriptor__message_type",            (DL_FUNC) &FieldDescriptor__message_type,             1},
    {"FieldDescriptor__name",                    (DL_FUNC) &FieldDescriptor__name,                     2},
    {"FieldDescriptor__number",                  (DL_FUNC) &FieldDescriptor__number,                   1},
    {"FieldDescriptor__type",                    (DL_FUNC) &FieldDescriptor__type,                     1},
    {"FileDescriptor__as_character",             (DL_FUNC) &FileDescriptor__as_character,              1},
    {"FileDescriptor__as_list",                  (DL_FUNC) &FileDescriptor__as_list,                   1},
    {"FileDescriptor__as_Message",               (DL_FUNC) &FileDescriptor__as_Message,                1},
    {"FileDescriptor__getMemberNames",           (DL_FUNC) &FileDescriptor__getMemberNames,            1},
    {"FileDescriptor__name",                     (DL_FUNC) &FileDescriptor__name,                      1},
    {"FileInputStream_Close",                    (DL_FUNC) &FileInputStream_Close,                     1},
    {"FileInputStream_GetErrno",                 (DL_FUNC) &FileInputStream_GetErrno,                  1},
    {"FileInputStream_new",                      (DL_FUNC) &FileInputStream_new,                       3},
    {"FileInputStream_SetCloseOnDelete",         (DL_FUNC) &FileInputStream_SetCloseOnDelete,          2},
    {"FileOutputStream_Close",                   (DL_FUNC) &FileOutputStream_Close,                    1},
    {"FileOutputStream_Flush",                   (DL_FUNC) &FileOutputStream_Flush,                    1},
    {"FileOutputStream_GetErrno",                (DL_FUNC) &FileOutputStream_GetErrno,                 1},
    {"FileOutputStream_new",                     (DL_FUNC) &FileOutputStream_new,                      3},
    {"FileOutputStream_SetCloseOnDelete",        (DL_FUNC) &FileOutputStream_SetCloseOnDelete,         2},
/*    {"get_method_input_type",                    (DL_FUNC) &get_method_input_type,                     1},*/
    {"get_method_output_prototype",              (DL_FUNC) &get_method_output_prototype,               1},
    {"get_protobuf_library_version",             (DL_FUNC) &get_protobuf_library_version,              0},
    {"get_value_of_enum",                        (DL_FUNC) &get_value_of_enum,                         2},
    {"getEnumDescriptor",                        (DL_FUNC) &getEnumDescriptor,                         1},
    {"getExtension_cpp",                         (DL_FUNC) &getExtension_cpp,                          2},
    {"getExtensionDescriptor",                   (DL_FUNC) &getExtensionDescriptor,                    1},
    {"getMessageField",                          (DL_FUNC) &getMessageField,                           2},
    {"getProtobufDescriptor",                    (DL_FUNC) &getProtobufDescriptor,                     1},
    {"has_enum_name",                            (DL_FUNC) &has_enum_name,                             2},
    {"identical_messages",                       (DL_FUNC) &identical_messages,                        2},
    {"Message__add_values",                      (DL_FUNC) &Message__add_values,                       3},
    {"Message__as_character",                    (DL_FUNC) &Message__as_character,                     1},
    {"Message__as_json",                         (DL_FUNC) &Message__as_json,                          1},
    {"Message__as_list",                         (DL_FUNC) &Message__as_list,                          1},
    {"Message__bytesize",                        (DL_FUNC) &Message__bytesize,                         1},
    {"Message__clear",                           (DL_FUNC) &Message__clear,                            1},
    {"Message__clear_field",                     (DL_FUNC) &Message__clear_field,                      2},
    {"Message__clone",                           (DL_FUNC) &Message__clone,                            1},
/*    {"Message__clone",                           (DL_FUNC) &Message__clone,                            2},*/
    {"Message__descriptor",                      (DL_FUNC) &Message__descriptor,                       1},
    {"Message__field_exists",                    (DL_FUNC) &Message__field_exists,                     2},
    {"Message__field_size",                      (DL_FUNC) &Message__field_size,                       2},
    {"Message__fieldNames",                      (DL_FUNC) &Message__fieldNames,                       1},
    {"Message__fileDescriptor",                  (DL_FUNC) &Message__fileDescriptor,                   1},
    {"Message__get_field_values",                (DL_FUNC) &Message__get_field_values,                 3},
    {"Message__get_payload",                     (DL_FUNC) &Message__get_payload,                      1},
    {"Message__has_field",                       (DL_FUNC) &Message__has_field,                        2},
    {"Message__is_initialized",                  (DL_FUNC) &Message__is_initialized,                   1},
    {"Message__length",                          (DL_FUNC) &Message__length,                           1},
    {"Message__merge",                           (DL_FUNC) &Message__merge,                            2},
    {"Message__num_extensions",                  (DL_FUNC) &Message__num_extensions,                   1},
    {"Message__serialize_to_file",               (DL_FUNC) &Message__serialize_to_file,                2},
    {"Message__set_field_size",                  (DL_FUNC) &Message__set_field_size,                   3},
    {"Message__set_field_values",                (DL_FUNC) &Message__set_field_values,                 4},
    {"Message__swap",                            (DL_FUNC) &Message__swap,                             4},
    {"MethodDescriptor__as_character",           (DL_FUNC) &MethodDescriptor__as_character,            1},
    {"MethodDescriptor__as_Message",             (DL_FUNC) &MethodDescriptor__as_Message,              1},
    {"MethodDescriptor__fileDescriptor",         (DL_FUNC) &MethodDescriptor__fileDescriptor,          1},
    {"MethodDescriptor__input_type",             (DL_FUNC) &MethodDescriptor__input_type,              1},
    {"MethodDescriptor__name",                   (DL_FUNC) &MethodDescriptor__name,                    2},
    {"MethodDescriptor__output_type",            (DL_FUNC) &MethodDescriptor__output_type,             1},
    {"newProtocolBufferLookup",                  (DL_FUNC) &newProtocolBufferLookup,                   1},
    {"newProtoMessage",                          (DL_FUNC) &newProtoMessage,                           1},
    {"readProtoFiles_cpp",                       (DL_FUNC) &readProtoFiles_cpp,                        2},
    {"resetDescriptorPool_cpp",                  (DL_FUNC) &resetDescriptorPool_cpp,                   0},
    {"ServiceDescriptor__as_character",          (DL_FUNC) &ServiceDescriptor__as_character,           1},
    {"ServiceDescriptor__as_list",               (DL_FUNC) &ServiceDescriptor__as_list,                1},
    {"ServiceDescriptor__as_Message",            (DL_FUNC) &ServiceDescriptor__as_Message,             1},
    {"ServiceDescriptor__fileDescriptor",        (DL_FUNC) &ServiceDescriptor__fileDescriptor,         1},
    {"ServiceDescriptor__getMethodNames",        (DL_FUNC) &ServiceDescriptor__getMethodNames,         1},
/*    {"ServiceDescriptor__method",                (DL_FUNC) &ServiceDescriptor__method,                 2},*/
    {"ServiceDescriptor__name",                  (DL_FUNC) &ServiceDescriptor__name,                   2},
/*    {"ServiceDescriptor_getMethodByIndex",       (DL_FUNC) &ServiceDescriptor_getMethodByIndex,        2},*/
/*    {"ServiceDescriptor_getMethodByName",        (DL_FUNC) &ServiceDescriptor_getMethodByName,         2},*/
/*    {"ServiceDescriptor_method_count",           (DL_FUNC) &ServiceDescriptor_method_count,            1},*/
    {"setMessageField",                          (DL_FUNC) &setMessageField,                           3},
    {"update_message",                           (DL_FUNC) &update_message,                            2},
    {"valid_input_message",                      (DL_FUNC) &valid_input_message,                       2},
    {"valid_output_message",                     (DL_FUNC) &valid_output_message,                      2},
    {"ZeroCopyInputStream_BackUp",               (DL_FUNC) &ZeroCopyInputStream_BackUp,                2},
    {"ZeroCopyInputStream_ByteCount",            (DL_FUNC) &ZeroCopyInputStream_ByteCount,             1},
    {"ZeroCopyInputStream_Next",                 (DL_FUNC) &ZeroCopyInputStream_Next,                  1},
    {"ZeroCopyInputStream_ReadLittleEndian32",   (DL_FUNC) &ZeroCopyInputStream_ReadLittleEndian32,    1},
    {"ZeroCopyInputStream_ReadLittleEndian64",   (DL_FUNC) &ZeroCopyInputStream_ReadLittleEndian64,    1},
    {"ZeroCopyInputStream_ReadRaw",              (DL_FUNC) &ZeroCopyInputStream_ReadRaw,               2},
    {"ZeroCopyInputStream_ReadString",           (DL_FUNC) &ZeroCopyInputStream_ReadString,            2},
    {"ZeroCopyInputStream_ReadVarint32",         (DL_FUNC) &ZeroCopyInputStream_ReadVarint32,          1},
    {"ZeroCopyInputStream_ReadVarint64",         (DL_FUNC) &ZeroCopyInputStream_ReadVarint64,          1},
    {"ZeroCopyInputStream_Skip",                 (DL_FUNC) &ZeroCopyInputStream_Skip,                  2},
    {"ZeroCopyOutputStream_BackUp",              (DL_FUNC) &ZeroCopyOutputStream_BackUp,               2},
    {"ZeroCopyOutputStream_ByteCount",           (DL_FUNC) &ZeroCopyOutputStream_ByteCount,            1},
    {"ZeroCopyOutputStream_Next",                (DL_FUNC) &ZeroCopyOutputStream_Next,                 2},
    {"ZeroCopyOutputStream_WriteLittleEndian32", (DL_FUNC) &ZeroCopyOutputStream_WriteLittleEndian32,  2},
    {"ZeroCopyOutputStream_WriteLittleEndian64", (DL_FUNC) &ZeroCopyOutputStream_WriteLittleEndian64,  2},
    {"ZeroCopyOutputStream_WriteRaw",            (DL_FUNC) &ZeroCopyOutputStream_WriteRaw,             2},
    {"ZeroCopyOutputStream_WriteString",         (DL_FUNC) &ZeroCopyOutputStream_WriteString,          2},
    {"ZeroCopyOutputStream_WriteVarint32",       (DL_FUNC) &ZeroCopyOutputStream_WriteVarint32,        2},
    {"ZeroCopyOutputStream_WriteVarint64",       (DL_FUNC) &ZeroCopyOutputStream_WriteVarint64,        2},
    {NULL, NULL, 0}
};

void R_init_RProtoBuf(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

void R_unload_RProtoBuf(DllInfo* dll) {
    resetDescriptorPool_cpp();
}
