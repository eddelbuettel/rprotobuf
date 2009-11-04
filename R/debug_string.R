
setMethod( "as.character", "protobufMessage", function(x, ...){
	.Call( "as_character_message", x@pointer, PACKAGE = "RProtoBuf" ) 
} )
setMethod( "as.character", "protobufDescriptor", function(x, ...){
	.Call( "as_character_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
} )
setMethod( "as.character", "protobufEnumDescriptor", function(x, ...){
	.Call( "as_character_enum_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
} )
setMethod( "as.character", "protobufFieldDescriptor", function(x, ...){
	.Call( "as_character_field_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
} )

