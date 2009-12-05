setGeneric( "method_count", function(object ){
	standardGeneric( "method_count" )
} )
setMethod( "method_count", "protobufServiceDescriptor", function(object){
	.Call( "ServiceDescriptor_method_count", object@pointer, PACKAGE = "RProtoBuf" )
} )

