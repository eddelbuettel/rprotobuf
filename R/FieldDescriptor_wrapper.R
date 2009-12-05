
setGeneric( "is_extension", function(object){
	standardGeneric("is_extension")
} )
setMethod( "is_extension", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_extension", object@pointer, PACKAGE = "RProtoBuf" )
})

setGeneric( "number", function(object){
	standardGeneric( "number" )
} )
setMethod( "number", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_number", object@pointer, PACKAGE = "RProtoBuf" )
} )

TYPE_DOUBLE   <- 1L
TYPE_FLOAT    <- 2L
TYPE_INT64    <- 3L
TYPE_UINT64   <- 4L
TYPE_INT32    <- 5L
TYPE_FIXED64  <- 6L
TYPE_FIXED32  <- 7L
TYPE_BOOL     <- 8L
TYPE_STRING   <- 9L
TYPE_GROUP    <- 10L
TYPE_MESSAGE  <- 11L
TYPE_BYTES    <- 12L
TYPE_UINT32   <- 13L
TYPE_ENUM     <- 14L
TYPE_SFIXED32 <- 15L
TYPE_SFIXED64 <- 16L
TYPE_SINT32   <- 17L
TYPE_SINT64   <- 18L

.TYPES <- ls( pattern = "^TYPE_" )

setGeneric( "type", function(object, as.string = FALSE){
	standardGeneric( "type" )
} )
setMethod( "type", "protobufFieldDescriptor", function(object, as.string = FALSE){
	type <- .Call( "FieldDescriptor_type", object@pointer, PACKAGE = "RProtoBuf" )
	if( as.string ) .TYPES[type] else type
} )


CPPTYPE_INT32 <- 1L
CPPTYPE_INT64 <- 2L
CPPTYPE_UINT32 <- 3L
CPPTYPE_UINT64 <- 4L
CPPTYPE_DOUBLE <- 5L
CPPTYPE_FLOAT <- 6L
CPPTYPE_BOOL <- 7L
CPPTYPE_ENUM <- 8L
CPPTYPE_STRING <- 9L
CPPTYPE_MESSAGE <- 10L
.CPPTYPES <- ls( pattern = "^CPPTYPE_" )

setGeneric( "cpp_type", function(object, as.string = FALSE ){
	standardGeneric( "cpp_type" )
} )
setMethod( "cpp_type", "protobufFieldDescriptor", function(object, as.string = FALSE){
	cpptype <- .Call( "FieldDescriptor_cpp_type", object@pointer, PACKAGE = "RProtoBuf" )
	if( as.string ) .CPPTYPES[cpptype] else cpptype
} )

LABEL_OPTIONAL <- 1L
LABEL_REQUIRED <- 2L
LABEL_REPEATED <- 3L
.LABELS <-  ls( pattern = "^LABEL_" )

setGeneric( "label", function(object, as.string = FALSE ){
	standardGeneric( "label" )
} )
setMethod( "label", "protobufFieldDescriptor", function(object, as.string = FALSE){
	lab <- .Call( "FieldDescriptor_label", object@pointer, PACKAGE = "RProtoBuf" )
	if( as.string ) .LABELS[lab] else lab
} )

setGeneric( "is_repeated", function(object ){
	standardGeneric( "is_repeated" )
} )
setMethod( "is_repeated", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_repeated", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "is_optional", function(object){
	standardGeneric( "is_optional" )
} )
setMethod( "is_optional", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_optional", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "is_required", function(object ){
	standardGeneric( "is_required" )
} )
setMethod( "is_required", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_required", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "has_default_value", function(object ){
	standardGeneric( "has_default_value" )
} )
setMethod( "has_default_value", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_has_default_value", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "default_value", function(object ){
	standardGeneric( "default_value" )
} )
setMethod( "default_value", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_default_value", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "message_type", function(object ){
	standardGeneric( "message_type" )
} )
setMethod( "message_type", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_message_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "enum_type", c( object = "protobufFieldDescriptor", index = "missing", name = "missing"), function(object){
	.Call( "FieldDescriptor_enum_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

