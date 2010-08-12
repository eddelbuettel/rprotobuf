
setGeneric( "isInitialized", function( object, ... ){
	standardGeneric( "isInitialized" )
} )
setMethod( "isInitialized", "Message", function(object, ... ){
	.Call( "Message__is_initialized", object@pointer, PACKAGE = "RProtoBuf" )
} )

