as.list.Message <- function( x, ...){
	.Call( "as_list_message", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.Descriptor <- function(x, ...){
	.Call( "as_list_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.EnumDescriptor <- function( x, ...){
	.Call( "as_list_enum_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.FileDescriptor <- function( x, ...){
	.Call( "as_list_file_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.ServiceDescriptor <- function( x, ...){
	.Call( "as_list_service_descriptor", x@pointer, PACKAGE = "RProtoBuf" )
}

