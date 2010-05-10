
setGeneric( "input_type", function(object){
	standardGeneric( "input_type" )
} )
setGeneric( "output_type", function(object){
	standardGeneric( "output_type" )
} )

setMethod( "input_type", "MethodDescriptor", function(object){
	.Call("MethodDescriptor__input_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "output_type", "MethodDescriptor", function(object){
	.Call("MethodDescriptor__output_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

