
# or should we use "length"
setGeneric( "bytesize", function(object, ...){
	standardGeneric( "bytesize" )
} )
setMethod( "bytesize", "protobufMessage", function(object, ...){
	.Call( "get_message_bytesize", object@pointer, PACKAGE = "RProtoBuf" )
} )

