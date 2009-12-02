
setGeneric( "descriptor", function(object, ...){
	standardGeneric( "descriptor" )
} )
setMethod( "descriptor", "protobufMessage", function(object, ...){
	.Call( "get_message_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "fileDescriptor", function(object, ...){
	standardGeneric( "fileDescriptor" )
} )
setMethod( "fileDescriptor", "protobufMessage", function(object, ...){
	.Call( "get_message_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "protobufDescriptor", function(object, ...){
	.Call( "get_descriptor_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "protobufEnumDescriptor", function(object, ...){
	.Call( "get_enum_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "protobufFieldDescriptor", function(object, ...){
	.Call( "get_field_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "protobufServiceDescriptor", function(object, ...){
	.Call( "get_service_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "protobufMethodDescriptor", function(object, ...){
	.Call( "get_method_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

