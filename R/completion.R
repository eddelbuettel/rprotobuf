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

# {{{ Message
.DollarNames.Message <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "Message__fieldNames", x@pointer, PACKAGE = "RProtoBuf" ) ,
		"has(", "clone()", "clone(", "isInitialized()", "serialize(", 
		"clear()", "clear(", "size(", "bytesize()", "fetch(",
		"swap(", "str()", "as.character()", "update(", "as.list()", 
                "setExtension(", "getExtension(",
                "descriptor()", "set(", "toString(", "add(", "fileDescriptor()" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ Descriptor
.DollarNames.Descriptor <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "Descriptor__getMemberNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"new(", "read(", "readASCII(", "fileDescriptor()", "name(",
                "toString()", "as.character()", "asMessage()",
		"containing_type()", "field_count()", "nested_type_count()", "enum_type_count", 
		"field(", "nested_type(", "enum_type(" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ EnumDescriptor
.DollarNames.EnumDescriptor <- function(x, pattern = "" ){
	
	names <- c( 
		.Call( "EnumDescriptor__getConstantNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"name(", "fileDescriptor()", "as.character()", "toString()", 
		"containing_type()", "length()", "value_count()", "value(",
		"has(", "asMessage()")
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ EnumValueDescriptor
.DollarNames.EnumValueDescriptor <- function(x, pattern = "" ){
	names <- c("number()", "name()", "enum_type()",
		   "as.character()", "toString()", "asMessage()")
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ FieldDescriptor
.DollarNames.FieldDescriptor <- function(x, pattern = "" ){
	names <- c("as.character()", "toString()", "name(", 
		"fileDescriptor()", "containing_type()", 
		"is_extension()", "number()", "type(", "cpp_type(", "label(", 
		"is_repeated()", "is_required()", "is_optional()", 
		"message_type()", "enum_type()", "asMessage()",
		"has_default_value()", "default_value("
	)
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ ServiceDescriptor
.DollarNames.ServiceDescriptor <- function(x, pattern = "" ){
	names <- c(
		.Call( "ServiceDescriptor__getMethodNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"as.character()", "toString()", "name(", "fileDescriptor()", 
		"method_count()", "method(name=", "method(index="  )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ MethodDescriptor
.DollarNames.MethodDescriptor <- function(x, pattern = "" ){
	names <- c("as.character()", "toString()", "name(", "fileDescriptor()", 
	"input_type()", "output_type()" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ FileDescriptor
.DollarNames.FileDescriptor <- function(x, pattern = "" ){
	names <- c(
		.Call( "FileDescriptor__getMemberNames", x@pointer, PACKAGE = "RProtoBuf" ), 
		"as.character()", "toString()", "name(", "as.list()",
                   "asMessage()", "package()")
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ ZeroCopyInputStream
.DollarNames.ZeroCopyInputStream <- function(x, pattern = "" ){
	names <- c("Next()", "ByteCount()", "Skip(", 
		"BackUp(", "ReadRaw(", "ReadString()", 
		"ReadVarint32()", "ReadVarint64()", 
		"ReadLittleEndian32()", "ReadLittleEndian64()" )
	grep( pattern, names, value = TRUE )
}
# }}}

# {{{ ZeroCopyOutputStream
.DollarNames.ZeroCopyOutputStream <- function(x, pattern = "" ){
	names <- c("Next(", "ByteCount()", "BackUp(", 
		"WriteRaw(",  "WriteString(",  "WriteLittleEndian32(", 
		"WriteLittleEndian64(", "WriteVarint32(", "WriteVarint64(" )
	grep( pattern, names, value = TRUE )
}
# }}}
