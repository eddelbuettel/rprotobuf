
setGeneric( "read", function( descriptor, input ){
	standardGeneric( "read" )
} )

setMethod( "read", c( descriptor = "Descriptor" , input = "character" ),
function(descriptor, input ){
	file <- file_path_as_absolute( input )
	.Call( "Descriptor__readMessageFromFile", descriptor@pointer, file, PACKAGE = "RProtoBuf" )
} )

setMethod( "read", c( descriptor = "Descriptor", input = "raw" ), function(descriptor, input ){
	.Call( "Descriptor__readMessageFromRawVector", descriptor@pointer, input, PACKAGE="RProtoBuf" )
} )

setMethod( "read", c( descriptor = "Descriptor" ),
function( descriptor, input ){
	if( !inherits( input, "connection" ) ){
		stop( "can only read from connections" )
	}
	wasopen <- identical( summary(input)[["opened"]], "opened" )
	if( !wasopen ) open( input, "rb")
        stopifnot(summary(input)[["text"]] == "binary")
	message <- .Call( "Descriptor__readMessageFromConnection", descriptor@pointer, input, PACKAGE = "RProtoBuf" )
	if( !wasopen ) close( input )
	message
} )




setGeneric( "readASCII", function( descriptor, input ){
	standardGeneric( "readASCII" )
} )

setMethod( "readASCII", c( descriptor = "Descriptor" , input = "character" ),
function(descriptor, input ){
	.Call( "Descriptor__readASCIIFromString", descriptor@pointer, input, PACKAGE = "RProtoBuf" )
} )

setMethod( "readASCII", c( descriptor = "Descriptor" ),
function( descriptor, input ){
	if( !inherits( input, "connection" ) ){
		stop( "can only read from connections" )
	}
	wasopen <- identical( summary(input)[["opened"]], "opened" )
	if( !wasopen ) open( input, "rb" )
        stopifnot(summary(input)[["text"]] == "binary")
	message <- .Call( "Descriptor__readASCIIFromConnection", descriptor@pointer, input, PACKAGE = "RProtoBuf" )
	if( !wasopen ) close( input )
	message
} )
