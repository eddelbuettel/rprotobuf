setGeneric( "field_count", function(object){
	standardGeneric( "field_count" )
} )
setMethod( "field_count", "protobufDescriptor", function(object){
	.Call( "field_count__Descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "nested_type_count", function(object){
	standardGeneric( "nested_type_count" )
} )
setMethod( "nested_type_count", "protobufDescriptor", function(object){
	.Call( "nested_type_count__Descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "enum_type_count", function(object){
	standardGeneric( "enum_type_count" )
} )
setMethod( "enum_type_count", "protobufDescriptor", function(object){
	.Call( "enum_type_count__Descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )


setGeneric( "field", function(object, index, number, name){
	standardGeneric( "field" )
} )
setMethod( "field", "protobufDescriptor", function( object, index, number, name){
	has_index  <- !missing(index)
	has_number <- !missing(number)
	has_name   <- !missing(name)
	
	if( as.integer(has_index) + as.integer(has_number) + as.integer(has_name) != 1L ){
		stop( "need exactly one of `index`, `number` or `name`" )
	}
	
	if( has_index ){
		return( .Call( "Descriptor_getFieldByIndex", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		return( .Call( "Descriptor_getFieldByNumber", object@pointer, as.integer(number), PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		return( .Call( "Descriptor_getFieldByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
} )

setGeneric( "nested_type", function(object, index, name){
	standardGeneric( "nested_type" )
} )
setMethod( "nested_type", "protobufDescriptor", function(object, index, name ){
	
	has_index  <- !missing(index)
	has_name   <- !missing(name)
	if( !identical( as.integer(has_index) + as.integer(has_number) + as.integer(has_name), 1L ) ){
		stop( "need exactly one of `index` or `name`" )
	}
	
	if( has_index ){
		return( .Call( "Descriptor_getNestedTypeByIndex", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		return( .Call( "Descriptor_getNestedTypeByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
} )

setGeneric( "enum_type", function( object, index, name ){
	standardGeneric( "enum_type" )
})

setMethod( "enum_type", "protobufDescriptor", function(object, index, name){
	has_index  <- !missing(index)
	has_name   <- !missing(name)
	if( !identical( as.integer(has_index) + as.integer(has_number) + as.integer(has_name), 1L ) ){
		stop( "need exactly one of `index` or `name`" )
	}
	if( has_index ){
		return( .Call( "Descriptor_getEnumTypeByIndex", object@pointer, as.integer(index)-1L, PACKAGE = "RProtoBuf" ) )
	}
	
	if( has_number ){
		return( .Call( "Descriptor_EnumTypeByName", object@pointer, as.character(name), PACKAGE = "RProtoBuf" ) )
	}
	
})
