
setGeneric( "is_extension", function(object){
	standardGeneric("is_extension")
} )
setMethod( "is_extension", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_is_extension", object@pointer, PACKAGE = "RProtoBuf" )
})

setGeneric( "number", function(object){
	standardGeneric( "number" )
} )
setMethod( "number", "protobufFieldDescriptor", function(object){
	.Call( "FieldDescriptor_number", object@pointer, PACKAGE = "RProtoBuf" )
} )

