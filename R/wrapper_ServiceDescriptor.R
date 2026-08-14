setGeneric( "method_count", function(object ){
	standardGeneric( "method_count" )
} )
setMethod( "method_count", "ServiceDescriptor", function(object){
	.Call(ServiceDescriptor__method_count, object@pointer)
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
		stopifnot(is.numeric(index))
		return( .Call(ServiceDescriptor__getMethodByIndex, object@pointer, as.integer(index)-1L) )
	}

	if( has_name ){
		stopifnot(is.character(name))
		return( .Call(ServiceDescriptor__getMethodByName, object@pointer, as.character(name)) )
	}

} )
