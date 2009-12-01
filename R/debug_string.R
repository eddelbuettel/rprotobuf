
._toString_protobufMessage <- function(x, ...){
	.Call( "as_character_message", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufDescriptor <- function(x, ...){
	.Call( "as_character_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufEnumDescriptor <- function(x, ...){
	.Call( "as_character_enum_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufFieldDescriptor <- function(x, ...){
	.Call( "as_character_field_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufServiceDescriptor <- function(x, ...){
	.Call( "as_character_service_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufMethodDescriptor <- function(x, ...){
	.Call( "as_character_method_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_protobufFileDescriptor <- function(x, ...){
	.Call( "as_character_file_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}

setMethod( "as.character", "protobufMessage", ._toString_protobufMessage  )
setMethod( "as.character", "protobufDescriptor", ._toString_protobufDescriptor  )
setMethod( "as.character", "protobufEnumDescriptor", ._toString_protobufEnumDescriptor )
setMethod( "as.character", "protobufFieldDescriptor", ._toString_protobufFieldDescriptor )
setMethod( "as.character", "protobufServiceDescriptor", ._toString_protobufServiceDescriptor )
setMethod( "as.character", "protobufMethodDescriptor", ._toString_protobufMethodDescriptor )
setMethod( "as.character", "protobufFileDescriptor", ._toString_protobufFileDescriptor )

setGeneric( "toString" )
setMethod( "toString", "protobufMessage", ._toString_protobufMessage  )
setMethod( "toString", "protobufDescriptor", ._toString_protobufDescriptor  )
setMethod( "toString", "protobufEnumDescriptor", ._toString_protobufEnumDescriptor )
setMethod( "toString", "protobufFieldDescriptor", ._toString_protobufFieldDescriptor )
setMethod( "toString", "protobufServiceDescriptor", ._toString_protobufServiceDescriptor )
setMethod( "toString", "protobufMethodDescriptor", ._toString_protobufMethodDescriptor )
setMethod( "toString", "protobufFileDescriptor", ._toString_protobufFileDescriptor )

