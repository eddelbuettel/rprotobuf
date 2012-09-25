
setGeneric( "has", function( object, name, ... ){
	standardGeneric( "has" )
} )
._has_message <- function( object, name, ...){
	if (!.Call( "Message__field_exists", object@pointer, name, PACKAGE = "RProtoBuf" )) {
		return(NULL)
	} else {
		return(.Call( "Message__has_field", object@pointer, name, PACKAGE = "RProtoBuf" ))
	}
}
setMethod( "has", "Message", ._has_message )
