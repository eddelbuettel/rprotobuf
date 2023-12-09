
setMethod( "enum_type", c( object = "EnumValueDescriptor", index = "missing", name = "missing"), function(object, index, name){
	.Call(EnumValueDescriptor__enum_type, object@pointer)
} )

setGeneric( "number", function(object){
	standardGeneric( "number" )
} )
setMethod( "number", "EnumValueDescriptor", function(object){
	.Call(EnumValueDescriptor__number, object@pointer)
} )
