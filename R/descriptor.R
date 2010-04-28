
setGeneric( "descriptor", function(object, ...){
	standardGeneric( "descriptor" )
} )
setMethod( "descriptor", "Message", function(object, ...){
	.Call( "Message__descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "fileDescriptor", function(object, ...){
	standardGeneric( "fileDescriptor" )
} )
setMethod( "fileDescriptor", "Message", function(object, ...){
	.Call( "get_message_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "Descriptor", function(object, ...){
	.Call( "get_descriptor_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "EnumDescriptor", function(object, ...){
	.Call( "get_enum_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "FieldDescriptor", function(object, ...){
	.Call( "get_field_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "ServiceDescriptor", function(object, ...){
	.Call( "get_service_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "fileDescriptor", "MethodDescriptor", function(object, ...){
	.Call( "get_method_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

