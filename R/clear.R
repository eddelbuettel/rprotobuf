setGeneric( "clear", function(object, field, ...){
	standardGeneric( "clear" )
} )
setMethod( "clear", signature( "Message", "missing" ), function(object, field, ...){
	.Call( Message__clear, object@pointer )
	invisible( object )
} )

setMethod( "clear", signature( "Message", "character" ), function(object, field, ...){
	.Call( Message__clear_field, object@pointer, field )
	invisible( object )
} )

setMethod( "clear", signature( "Message", "integer" ), function(object, field, ...){
	.Call( Message__clear_field, object@pointer, field )
	invisible( object )
} )

setMethod( "clear", signature( "Message", "numeric" ), function(object, field, ...){
	.Call( Message__clear_field, object@pointer, as.integer(field) )
	invisible( object )
} )

setMethod( "clear", signature( "Message", "raw" ), function(object, field, ...){
	.Call( Message__clear_field, object@pointer, as.integer(field) )
	invisible( object )
} )
