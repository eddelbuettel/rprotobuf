
setGeneric( "descriptor", function(object, ...){
	standardGeneric( "descriptor" )
} )
setMethod( "descriptor", "Message", function(object, ...){
	.Call(Message__descriptor, object@pointer)
} )

setGeneric( "fileDescriptor", function(object, ...){
	standardGeneric( "fileDescriptor" )
} )
setMethod( "fileDescriptor", "Message", function(object, ...){
	.Call(Message__fileDescriptor, object@pointer)
} )
setMethod( "fileDescriptor", "Descriptor", function(object, ...){
	.Call(Descriptor__fileDescriptor, object@pointer)
} )
setMethod( "fileDescriptor", "EnumDescriptor", function(object, ...){
	.Call(EnumDescriptor__fileDescriptor, object@pointer)
} )
setMethod( "fileDescriptor", "FieldDescriptor", function(object, ...){
	.Call(FieldDescriptor__fileDescriptor, object@pointer)
} )
setMethod( "fileDescriptor", "ServiceDescriptor", function(object, ...){
	.Call(ServiceDescriptor__fileDescriptor, object@pointer)
} )
setMethod( "fileDescriptor", "MethodDescriptor", function(object, ...){
	.Call(MethodDescriptor__fileDescriptor, object@pointer)
} )
