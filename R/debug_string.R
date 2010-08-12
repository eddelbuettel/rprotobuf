
._toString_Message <- function(x, ...){
	.Call( "Message__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_Descriptor <- function(x, ...){
	.Call( "Descriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_EnumDescriptor <- function(x, ...){
	.Call( "EnumDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_FieldDescriptor <- function(x, ...){
	.Call( "FieldDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_ServiceDescriptor <- function(x, ...){
	.Call( "ServiceDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_MethodDescriptor <- function(x, ...){
	.Call( "MethodDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_FileDescriptor <- function(x, ...){
	.Call( "FileDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_EnumValueDescriptor <- function(x, ...){
	.Call( "EnumValueDescriptor__as_character", x@pointer, PACKAGE = "RProtoBuf" ) 
}


setMethod( "as.character", "Message", ._toString_Message  )
setMethod( "as.character", "Descriptor", ._toString_Descriptor  )
setMethod( "as.character", "EnumDescriptor", ._toString_EnumDescriptor )
setMethod( "as.character", "FieldDescriptor", ._toString_FieldDescriptor )
setMethod( "as.character", "ServiceDescriptor", ._toString_ServiceDescriptor )
setMethod( "as.character", "MethodDescriptor", ._toString_MethodDescriptor )
setMethod( "as.character", "FileDescriptor", ._toString_FileDescriptor )
setMethod( "as.character", "EnumValueDescriptor", ._toString_EnumValueDescriptor )

setGeneric( "toString" )
setMethod( "toString", "Message", ._toString_Message  )
setMethod( "toString", "Descriptor", ._toString_Descriptor  )
setMethod( "toString", "EnumDescriptor", ._toString_EnumDescriptor )
setMethod( "toString", "FieldDescriptor", ._toString_FieldDescriptor )
setMethod( "toString", "ServiceDescriptor", ._toString_ServiceDescriptor )
setMethod( "toString", "MethodDescriptor", ._toString_MethodDescriptor )
setMethod( "toString", "FileDescriptor", ._toString_FileDescriptor )
setMethod( "toString", "EnumValueDescriptor", ._toString_EnumValueDescriptor )

