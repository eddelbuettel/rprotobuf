
setGeneric( "input_type", function(object){
	standardGeneric( "input_type" )
} )
setGeneric( "output_type", function(object){
	standardGeneric( "output_type" )
} )

setMethod( "input_type", "protobufMethodDescriptor", function(object){
	.Call("get_method_input_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "output_type", "protobufMethodDescriptor", function(object){
	.Call("get_method_output_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

