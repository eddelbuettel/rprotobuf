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

