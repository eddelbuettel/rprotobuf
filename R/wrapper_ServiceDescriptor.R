setGeneric( "method_count", function(object ){
	standardGeneric( "method_count" )
} )
setMethod( "method_count", "ServiceDescriptor", function(object){
	.Call("ServiceDescriptor_method_count", object@pointer)
} )


setGeneric( "method", function(object, index, name ){
	standardGeneric( "method" )
} )
setMethod( "method", "ServiceDescriptor", function(object, index, name){

	has_index  <- !missing(index)
	has_name   <- !missing(name)

	if( as.integer(has_index) + as.integer(has_name) != 1L ){
		stop( "need exactly one of `index` or `name`" )
	}

	if( has_index ){
		stop( "No routine for getting a method from a ServiceDescriptor by index." )
	}

	if( has_name ){
		stop( "No routine for getting a method from a ServiceDescriptor by name." )
	}

} )
