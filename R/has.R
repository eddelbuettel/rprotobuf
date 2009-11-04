
setGeneric( "has", function( object, name, ... ){
	standardGeneric( "has" )
} )
._has_message <- function( object, name, ...){
	.Call( "message_has_field", object@pointer, name, PACKAGE = "RProtoBuf" )
}
setMethod( "has", "protobufMessage", ._has_message )

