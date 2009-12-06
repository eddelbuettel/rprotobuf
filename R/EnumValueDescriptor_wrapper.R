
setMethod( "enum_type", c( object = "EnumValueDescriptor", index = "missing", name = "missing"), function(object, index, name){
	.Call( "EnumValueDescriptor__enum_type", object@pointer, PACKAGE = "RProtoBuf" )
} )

