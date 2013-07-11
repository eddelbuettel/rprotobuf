## TODO(mstokely): Set and fetch are undocumented in Message-class.Rd
## And untested.  Are they usful?

setGeneric( "set", function(object, field, index, values ){
	standardGeneric( "set" )
} )
setMethod( "set", "Message", function(object, field, index, values ){
	
	if( !is.numeric( index ) ){
		stop( "index should be numbers" )
	}
	
	if( inherits( values, "Message" ) ){
		values <- list( values )
	}
	# TODO: we need to handle R type = RAWSXP and cpp type == string or bytes
	if( !identical( length( values ), length(index) ) ){
		# TODO: we might want to be more flexible about that later
		#       recycling, ...
		stop( "`index` should have the same length as `values`" )
	}
	
	fsize <- size( object, field )
	if( any( index > fsize ) || any( index < 1) ){
		stop( sprintf( "index should only contain values between 1 and %d", fsize )  ) 
	}
	
	.Call( "Message__set_field_values", object@pointer, 
		field, index - 1L , values, 
		PACKAGE = "RProtoBuf" )
		
	# we work by reference
	invisible( NULL )
} )

setGeneric( "fetch", function(object, field, index ){
	standardGeneric( "fetch" )
} )
setMethod( "fetch", "Message", function(object, field, index ){
	
	if( !is.numeric( index ) ){
		stop( "index should be numbers" )
	}
	fsize <- size( object, field )
	if( any( index > fsize ) || any( index < 1) ){
		stop( sprintf( "index should only contain values between 1 and %d", fsize )  ) 
	}
	.Call( "Message__get_field_values", object@pointer, 
		field, index - 1L , PACKAGE = "RProtoBuf" )
} )


