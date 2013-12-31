
setGeneric( "bytesize", function(object, ...){
	standardGeneric( "bytesize" )
} )
setMethod( "bytesize", "Message", function(object, ...){
	.Call( "Message__bytesize", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "size", function( object, field, ... ){
	standardGeneric( "size" )
} )
setMethod( "size", "Message", function(object, field, ...){
	
	if( is.character( field ) || is.numeric( field ) ){
		.Call( "Message__field_size", object@pointer, field, PACKAGE = "RProtoBuf" )
	} else{
		stop( "field should be a character or a number" )
	}
	
} )


setGeneric( "size<-", function( object, field, ..., value ){
	standardGeneric( "size<-" )
} )
setMethod( "size<-", "Message", function(object, field, ..., value){
	
	if( !is.numeric( value ) ){
		stop("value should be a number")
	}
	value <- as.integer( value )[1]
	
	if( is.character( field ) || is.numeric( field ) ){
		.Call( "Message__set_field_size", object@pointer, field, value, PACKAGE = "RProtoBuf" )
	} else{
		stop( "field should be a character or a number" )
	}
	object
} )


