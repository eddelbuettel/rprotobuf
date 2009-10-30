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
	
	names <- .Call( "getMessageFieldNames", x@pointer, PACKAGE = "RProtoBuf" ) 
	# TODO: add 'methods' here, such as "read()", "write()"
	grep( pattern, names, value = TRUE )
}
# }}}


# {{{ protobufDescriptor
.DollarNames.protobufDescriptor <- function(x, pattern = "" ){
	
	names <- .Call( "getDescriptorMemberNames", x@pointer, PACKAGE = "RProtoBuf" ) 
	grep( pattern, names, value = TRUE )
}
# }}}
