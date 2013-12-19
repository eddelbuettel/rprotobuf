
setGeneric( "containing_type", function(object){
	standardGeneric( "containing_type" )
} )

setMethod( "containing_type", "Descriptor", function(object){
	retval <- .Call( "Descriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
	if (length(retval@type) == 0) {
		# Descriptors do not always have containing types.
		# In such cases NULL is better return value than malformed Descriptor.
		return(NULL)
	} else {
                return(retval)
	}
} )
setMethod( "containing_type", "EnumDescriptor", function(object){
	retval <- .Call( "EnumDescriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
	if (length(name(retval)) == 0) {
		# If this enum type is nested in a message type, this
		# is that message type.	 Otherwise, NULL.
		return(NULL)
	} else {
                return(retval)
	}
} )
setMethod( "containing_type", "FieldDescriptor", function(object){
        # Never NULL
	.Call( "FieldDescriptor__containing_type", object@pointer, PACKAGE = "RProtoBuf" )
} )
