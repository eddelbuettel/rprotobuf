
setMethod( "as.character", "protobufMessage", function(x, ...){
	.Call( "get_message_debug_string", x@pointer, PACKAGE = "RProtoBuf" ) 
} )
setMethod( "as.character", "protobufDescriptor", function(x, ...){
	.Call( "get_descriptor_debug_string", x@pointer, PACKAGE = "RProtoBuf" ) 
} )


