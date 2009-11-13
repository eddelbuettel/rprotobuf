
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

setMethod( "as.character", "protobufMessage", ._toString_protobufMessage  )
setMethod( "as.character", "protobufDescriptor", ._toString_protobufDescriptor  )
setMethod( "as.character", "protobufEnumDescriptor", ._toString_protobufEnumDescriptor )
setMethod( "as.character", "protobufFieldDescriptor", ._toString_protobufFieldDescriptor )

setGeneric( "toString" )
setMethod( "toString", "protobufMessage", ._toString_protobufMessage  )
setMethod( "toString", "protobufDescriptor", ._toString_protobufDescriptor  )
setMethod( "toString", "protobufEnumDescriptor", ._toString_protobufEnumDescriptor )
setMethod( "toString", "protobufFieldDescriptor", ._toString_protobufFieldDescriptor )

