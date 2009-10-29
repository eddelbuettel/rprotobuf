
setClass( "protobufDescriptor", representation( 
	pointer = "externalptr",   # pointer to some C++ variable
	type = "character"         # message type
), prototype = list( pointer = NULL, type = character(0) ) )


setClass( "protobufMessage",  representation( 
   pointer = "externalptr",    # pointer to some C++ variable
   type    = "character"       # message type (fully qualified, with package path)
), prototype = list( pointer = NULL, type = character(0) ) ) 

setClass( "protobufEnum",  representation( 
   pointer = "externalptr",    # pointer to some C++ variable
   type    = "character"       # enum type (fully qualified, with package path)
), prototype = list( pointer = NULL, type = character(0) ) ) 



setGeneric("new")
setMethod("new", signature(Class="protobufDescriptor"), function(Class, ...) newProto(Class, ...))

P <- function( type, file ){
	
	if( missing( type ) ){
		stop( "'type' is required" )
	}
	if( !missing(file) ){
		readProtoFiles( file ) 
	}
	ptr <- .Call( "getProtobufDescriptor", type, PACKAGE = "RProtoBuf" )
	new( "protobufDescriptor", pointer = ptr, type = type ) 
}

newProto <- function( descriptor ){
	ptr <- .Call( "newProtoMessage", descriptor, PACKAGE = "RProtoBuf" )
	new( "protobufMessage", pointer = ptr, type = descriptor@type )
}

setMethod("$", c(x="protobufMessage"), function(x, name) {
	.Call( "getMessageField", x@pointer, name )
} )
setMethod("$<-", c(x="protobufMessage"), function(x, name, value) {
	.Call( "setMessageField", x@pointer, name, value )
	x
} )

