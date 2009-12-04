# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

# implementation of completion for proto messages
# through the .DollarNames method (R>= 2.10.0)

# S4 dispatch does not work for .DollarNames, so we'll use S3
# {{{ bring .DollarNames from the future if necessary
if( !exists( ".DollarNames", envir = asNamespace("utils") ) ){
	.DollarNames <- function(x, pattern)
    	UseMethod(".DollarNames")
} 
# }}}

# {{{ protobufMessage
.DollarNames.protobufMessage <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "getMessageFieldNames", x@pointer, PACKAGE = "RProtoBuf" ) ,
		"has(", "clone()", "clone(", "isInitialized()", "serialize(", 
		"clear()", "clear(", "size(", "bytesize()", 
		"swap(", "str()", "as.character()", "update(", "as.list()", 
		"descriptor()", "set(", "toString(", "add(", "fileDescriptor()" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufDescriptor
.DollarNames.protobufDescriptor <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "getDescriptorMemberNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"new(", "read(", "fileDescriptor()", "name(", "fileDescriptor()", 
		"containing_type()", "field_count()", "nested_type_count()", "enum_type_count", 
		"field(", "nested_type(", "enum_type(" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufEnumDescriptor
.DollarNames.protobufEnumDescriptor <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "getEnumDescriptorConstantNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"name(", "fileDescriptor()", "as.character()", "toString()", 
		"containing_type()" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufFieldDescriptor
.DollarNames.protobufFieldDescriptor <- function(x, pattern = "" ){
	names <- c("as.character()", "toString()", "name(", 
	"fileDescriptor()", "containing_type()", 
	"is_extension()", "number()", "type(", "cpp_type(" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufServiceDescriptor
.DollarNames.protobufServiceDescriptor <- function(x, pattern = "" ){
	names <- c(
		.Call( "getServiceDescriptorMethodNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"as.character()", "toString()", "name(", "fileDescriptor()")
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufMethodDescriptor
.DollarNames.protobufMethodDescriptor <- function(x, pattern = "" ){
	names <- c("as.character()", "toString()", "name(", "fileDescriptor()")
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ protobufFileDescriptor
.DollarNames.protobufFileDescriptor <- function(x, pattern = "" ){
	names <- c(
		.Call( "getFileDescriptorMemberNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"as.character()", "toString()", "name(" )
	grep( pattern, names, value = TRUE )
}
# }}}
