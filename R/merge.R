setGeneric( "merge" )
setMethod( "merge", 
	c( x = "Message", y = "Message" ), 
	function( x, y , ... ){
		if( !identical( x@type, y@type ) ){
			throw( 
				sprintf( "incompatible message types, cannot merge '%s' and '%s'", x@type, y@type ), 
				"IncompatibleType" )
		}
		
		message <- .Call( "Message__merge", x@pointer, y@pointer )
		message
} )

