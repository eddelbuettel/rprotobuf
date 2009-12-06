
setGeneric( "containing_type", function(object){
	standardGeneric( "containing_type" )
} )

setMethod( "containing_type", "Descriptor", function(object){
	.Call( "containing_type__Descriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "containing_type", "EnumDescriptor", function(object){
	.Call( "containing_type__EnumDescriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "containing_type", "FieldDescriptor", function(object){
	.Call( "containing_type__FieldDescriptor", object@pointer, PACKAGE = "RProtoBuf" )
} )

