
._toString_Message <- function(x, ...){
	.Call( "as_character_message", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_Descriptor <- function(x, ...){
	.Call( "as_character_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_EnumDescriptor <- function(x, ...){
	.Call( "as_character_enum_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_FieldDescriptor <- function(x, ...){
	.Call( "as_character_field_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_ServiceDescriptor <- function(x, ...){
	.Call( "as_character_service_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_MethodDescriptor <- function(x, ...){
	.Call( "as_character_method_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_FileDescriptor <- function(x, ...){
	.Call( "as_character_file_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
}
._toString_EnumValueDescriptor <- function(x, ...){
	.Call( "as_character_enum_value_descriptor", x@pointer, PACKAGE = "RProtoBuf" ) 
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

