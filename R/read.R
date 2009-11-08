
setGeneric( "read", function( descriptor, input ){
	standardGeneric( "read" )
} )

setMethod( "read", c( descriptor = "protobufDescriptor" , input = "character" ), 
function(descriptor, input ){
	file <- tools:::file_path_as_absolute( input )
	.Call( "readMessageFromFile", descriptor@pointer, file, PACKAGE = "RProtoBuf" ) 
} )

setMethod( "read", c( descriptor = "protobufDescriptor" ), 
function( descriptor, input ){
	if( !inherits( input, "connection" ) ){ 
		stop( "can only read from connections" )
	}
	
	.NotYetImplemented( ) 
	
} )

