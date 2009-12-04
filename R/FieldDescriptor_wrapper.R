
setGeneric( "is_extension", function(object){
	standardGeneric("is_extension")
} )
setMethod( "is_extension", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_extension", object@pointer, PACKAGE = "RProtoBuf" )
})


