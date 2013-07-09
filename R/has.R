
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
._has_enum_name <- function( object, name, ...){
  return(.Call( "has_enum_name", object@pointer, name, package = "RProtoBuf"))
}

setMethod( "has", "Message", ._has_message )
setMethod( "has", "EnumDescriptor", ._has_enum_name)
