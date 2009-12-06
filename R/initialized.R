
setGeneric( "isInitialized", function( object, ... ){
	standardGeneric( "isInitialized" )
} )
setMethod( "isInitialized", "Message", function(object, ... ){
	.Call( "is_message_initialized", object@pointer, PACKAGE = "RProtoBuf" )
} )

