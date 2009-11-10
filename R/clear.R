setGeneric( "clear", function(object, field, ...){
	standardGeneric( "clear" )
} )
setMethod( "clear", signature( "protobufMessage", "missing" ), function(object, field, ...){
	.Call( "clear_message", object@pointer, PACKAGE = "RProtoBuf" )
	invisible( object )
} )

setMethod( "clear", signature( "protobufMessage", "character" ), function(object, field, ...){
	.Call( "clear_message_field", object@pointer, field, PACKAGE = "RProtoBuf" )
	invisible( object )
} )

setMethod( "clear", signature( "protobufMessage", "integer" ), function(object, field, ...){
	.Call( "clear_message_field", object@pointer, field, PACKAGE = "RProtoBuf" )
	invisible( object )
} )

setMethod( "clear", signature( "protobufMessage", "numeric" ), function(object, field, ...){
	.Call( "clear_message_field", object@pointer, as.integer(field), PACKAGE = "RProtoBuf" )
	invisible( object )
} )

setMethod( "clear", signature( "protobufMessage", "raw" ), function(object, field, ...){
	.Call( "clear_message_field", object@pointer, as.integer(field), PACKAGE = "RProtoBuf" )
	invisible( object )
} )

