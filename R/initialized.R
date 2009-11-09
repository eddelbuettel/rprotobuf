
setGeneric( "isInitialized", function( object, ... ){
	standardGeneric( "isInitialized" )
} )
setMethod( "isInitialized", "protobufMessage", function(object, ... ){
	.Call( "is_message_initialized", object@pointer, PACKAGE = "RProtoBuf" )
} )

