setGeneric( "set", function(object, field, index, values ){
	standardGeneric( "set" )
} )
setMethod( "set", "protobufMessage", function(object, field, index, values ){
	
	if( !is.numeric( index ) ){
		stop( "index should be numbers" )
	}
	
	if( inherits( values, "protobufMessage" ) ){
		values <- list( values )
	}
	
	if( !identical( length( values ), length(index) ) ){
		# TODO: we might want to be more flexible about that later
		#       recycling, ...
		stop( "`index` should have the same length as `values`" )
	}
	
	fsize <- size( object, field )
	if( any( index > fsize ) || any( index < 1) ){
		stop( sprintf( "index should only contain values between 1 and %d", fsize )  ) 
	}
	
	.Call( "set_field_values", object@pointer, 
		field, index - 1L , values, 
		PACKAGE = "RProtoBuf" )
		
	# we work by reference
	invisible( NULL )
} )

