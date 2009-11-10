
setGeneric( "bytesize", function(object, ...){
	standardGeneric( "bytesize" )
} )
setMethod( "bytesize", "protobufMessage", function(object, ...){
	.Call( "get_message_bytesize", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "size", function( object, field, ... ){
	standardGeneric( "size" )
} )
setMethod( "size", "protobufMessage", function(object, field, ...){
	
	if( is.character( field ) || is.numeric( field ) ){
		.Call( "get_field_size", object@pointer, field, PACKAGE = "RProtoBuf" )
	} else{
		stop( "field should be a character or a number" )
	}
	
} )

