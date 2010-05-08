setGeneric( "field_count", function(object){
	standardGeneric( "field_count" )
} )
setMethod( "field_count", "Descriptor", function(object){
	.Call( "Descriptor__field_count", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "nested_type_count", function(object){
	standardGeneric( "nested_type_count" )
} )
setMethod( "nested_type_count", "Descriptor", function(object){
	.Call( "Descriptor__nested_type_count", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "enum_type_count", function(object){
	standardGeneric( "enum_type_count" )
} )
setMethod( "enum_type_count", "Descriptor", function(object){
	.Call( "Descriptor__enum_type_count", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "field", function(object, index, number, name){
	standardGeneric( "field" )
} )
setMethod( "field", "Descriptor", function( object, index, number, name){
	has_index  <- !missing(index)
	has_number <- !missing(number)
	has_name   <- !missing(name)
	
	if( as.integer(has_index) + as.integer(has_number) + as.integer(has_name) != 1L ){
		stop( "need exactly one of `index`, `number` or `name`" )
	}
	
	if( has_index ){
		return( .Call( "Descriptor__field", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		return( .Call( "Descriptor__FindFieldByNumber", object@pointer, as.integer(number), PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_name ){
		return( .Call( "Descriptor__FindFieldByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
} )

setGeneric( "nested_type", function(object, index, name){
	standardGeneric( "nested_type" )
} )
setMethod( "nested_type", "Descriptor", function(object, index, name ){
	
	has_index  <- !missing(index)
	has_name   <- !missing(name)
	if( !identical( as.integer(has_index) + as.integer(has_name), 1L ) ){
		stop( "need exactly one of `index` or `name`" )
	}
	
	if( has_index ){
		return( .Call( "Descriptor__nested_type", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_name ){
		return( .Call( "Descriptor__FindNestedTypeByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
} )

setMethod( "enum_type", "Descriptor", function(object, index, name){
	has_index  <- !missing(index)
	has_name   <- !missing(name)
	if( !identical( as.integer(has_index) + as.integer(has_name), 1L ) ){
		stop( "need exactly one of `index` or `name`" )
	}
	if( has_index ){
		return( .Call( "Descriptor__enum_type", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_name ){
		return( .Call( "Descriptor__FindEnumTypeByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
})
