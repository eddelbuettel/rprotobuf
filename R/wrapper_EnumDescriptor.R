
setGeneric( "value_count", function(object ){
	standardGeneric( "value_count" )
} )
setMethod( "value_count", "EnumDescriptor", function(object){
	.Call( "EnumDescriptor__value_count", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "value", function(object, index, name, number ){
	standardGeneric( "value" )
} )
setMethod( "value", "EnumDescriptor", function(object, index, name, number){
	
	has_index  <- !missing(index)
	has_number <- !missing(number)
	has_name   <- !missing(name)
	
	if( as.integer(has_index) + as.integer(has_number) + as.integer(has_name) != 1L ){
		stop( "need exactly one of `index`, `number` or `name`" )
	}
	
	if( has_index ){
		stopifnot(is.numeric(index))
		return( .Call( "EnumDescriptor__getValueByIndex", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		stopifnot(is.numeric(number))
		return( .Call( "EnumDescriptor__getValueByNumber", object@pointer, as.integer(number), PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_name ){
		stopifnot(is.character(name))
		return( .Call( "EnumDescriptor__getValueByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
} )

