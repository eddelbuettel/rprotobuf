
setGeneric( "clone", function( object, ... ){
	standardGeneric( "clone" )
} )
._clone.message <- function( object, ... ){
	message <- .Call( "clone_message", object@pointer )
	update( message, ... )
	message
}
setMethod( "clone", "protobufMessage", ._clone.message )

