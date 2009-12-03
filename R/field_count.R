setGeneric( "field_count", function(object){
	standardGeneric( "field_count" )
} )
setMethod( "field_count", "protobufDescriptor", function(object){
	.Call( "field_count__Descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

