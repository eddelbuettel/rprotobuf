setGeneric( "merge" )
setMethod( "merge", 
	c( x = "protobufMessage", y = "protobufMessage" ), 
	function( x, y , ... ){
		if( !identical( x@type, y@type ) ){
			throw( 
				sprintf( "incompatible message types, cannot merge '%s' and '%s'", x@type, y@type ), 
				"IncompatibleType" )
		}
		
		message <- .Call( "merge_message", x@pointer, y@pointer )
		message
} )

