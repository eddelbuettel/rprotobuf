as.list.Message <- function( x, ...){
	.Call( "Message__as_list", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.Descriptor <- function(x, ...){
        # Fields, then nested types, then enum types defined in the message
        # are returned in a list.
	.Call( "Descriptor__as_list", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.EnumDescriptor <- function( x, ...){
	.Call( "EnumDescriptor__as_list", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.FileDescriptor <- function( x, ...){
	.Call( "FileDescriptor__as_list", x@pointer, PACKAGE = "RProtoBuf" )
}
as.list.ServiceDescriptor <- function( x, ...){
	.Call( "ServiceDescriptor__as_list", x@pointer, PACKAGE = "RProtoBuf" )
}
