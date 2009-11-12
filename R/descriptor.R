
setGeneric( "descriptor", function(object, ...){
	standardGeneric( "descriptor" )
} )
setMethod( "descriptor", "protobufMessage", function(object, ...){
	.Call( "get_message_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

