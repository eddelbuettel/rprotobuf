setGeneric("swap", function( object, field, left, right) {
	standardGeneric( "swap" )
} )
setMethod( "swap", "protobufMessage", function( object, field, left, right ){
	left <- as.integer( left )
	right <- as.integer( right )
	
	if( length(left) != length(right) ){
		stop( "left and right should have the same length" )
	}
	.Call( "message_swap_fields", object@pointer, field, left, right, 
		PACKAGE = "RProtoBuf" ) 
	object
} )
