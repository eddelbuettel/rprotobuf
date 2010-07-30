setGeneric("swap", function( object, field, left, right) {
	standardGeneric( "swap" )
} )
setMethod( "swap", "Message", function( object, field, left, right ){
	left <- as.integer( left ) - 1L
	right <- as.integer( right ) - 1L
	
	if( length(left) != length(right) ){
		stop( "left and right should have the same length" )
	}
	.Call( "Message__swap", object@pointer, field, left, right, 
		PACKAGE = "RProtoBuf" ) 
	invisible( object )
} )
