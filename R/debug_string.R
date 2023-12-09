
._toString_Message <- function(x, debug = getOption("RProtoBuf.toString.debug", TRUE), ...){
	if (isTRUE(debug)) {
		.Call( Message__as_character, x@pointer )
	} else {
		.Call( Message__print_text_format, x@pointer)
	}
}
._toString_Descriptor <- function(x, ...){
	.Call( Descriptor__as_character, x@pointer )
}
._toString_EnumDescriptor <- function(x, ...){
	.Call( EnumDescriptor__as_character, x@pointer )
}
._toString_FieldDescriptor <- function(x, ...){
	.Call( FieldDescriptor__as_character, x@pointer )
}
._toString_ServiceDescriptor <- function(x, ...){
	.Call( ServiceDescriptor__as_character, x@pointer )
}
._toString_MethodDescriptor <- function(x, ...){
	.Call( MethodDescriptor__as_character, x@pointer )
}
._toString_FileDescriptor <- function(x, ...){
	.Call( FileDescriptor__as_character, x@pointer )
}
._toString_EnumValueDescriptor <- function(x, ...){
	.Call( EnumValueDescriptor__as_character, x@pointer )
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

setGeneric( "toJSON", function( x, ... ) {
    standardGeneric( "toJSON" )
} )
setMethod( "toJSON", c( x = "Message"),
function(x, preserve_proto_field_names = FALSE, always_print_primitive_fields = FALSE) {
    .Call( Message__as_json, x@pointer, preserve_proto_field_names, always_print_primitive_fields)
} )

setGeneric( "toDebugString", function( x ) {
  standardGeneric( "toDebugString" )
} )
setMethod( "toDebugString", c( x = "Message"),
  function(x) {
    .Call( Message__as_character, x@pointer)
  } )
