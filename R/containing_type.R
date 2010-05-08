
setGeneric( "containing_type", function(object){
	standardGeneric( "containing_type" )
} )

setMethod( "containing_type", "Descriptor", function(object){
	.Call( "Descriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "containing_type", "EnumDescriptor", function(object){
	.Call( "EnumDescriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "containing_type", "FieldDescriptor", function(object){
	.Call( "FieldDescriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

