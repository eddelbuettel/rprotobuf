setGeneric( "clear", function(object, ...){
	standardGeneric( "clear" )
} )
setMethod( "clear", "protobufMessage", function(object, ...){
	.Call( "clear_message", object@pointer, PACKAGE = "RProtoBuf" )
	object
} )

