
setGeneric( "clone", function( object, ... ){
	standardGeneric( "clone" )
} )
._clone.message <- function( object, ... ){
	message <- .Call( "Message__clone", object@pointer )
	update( message, ... )
	message
}
setMethod( "clone", "Message", ._clone.message )

