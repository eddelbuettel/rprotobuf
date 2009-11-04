as.list.protobufMessage <- function( x, ...){
	.Call( "as_list_message", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.protobufDescriptor <- function(x, ...){
	.Call( "as_list_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.protobufEnumDescriptor <- function( x, ...){
	.Call( "as_list_enum_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}
