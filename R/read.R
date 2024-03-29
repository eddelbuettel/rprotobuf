
setGeneric( "read", function( descriptor, input ){
	standardGeneric( "read" )
} )

setMethod( "read", c( descriptor = "Descriptor" , input = "character" ),
function(descriptor, input ){
	file <- file_path_as_absolute( input )
	.Call(Descriptor__readMessageFromFile, descriptor@pointer, file)
} )

setMethod( "read", c( descriptor = "Descriptor", input = "raw" ), function(descriptor, input ){
	.Call(Descriptor__readMessageFromRawVector, descriptor@pointer, input)
} )

setMethod( "read", c( descriptor = "Descriptor" ),
function( descriptor, input ){
	if( !inherits( input, "connection" ) ){
		stop( "can only read from connections" )
	}
	wasopen <- identical( summary(input)[["opened"]], "opened" )
	if( !wasopen ) open( input, "rb")
        stopifnot(summary(input)[["text"]] == "binary")
	message <- .Call(Descriptor__readMessageFromConnection, descriptor@pointer, input)
	if( !wasopen ) close( input )
	message
} )




setGeneric( "readASCII", function( descriptor, input, partial=FALSE ){
	standardGeneric( "readASCII" )
} )

setMethod( "readASCII", c( descriptor = "Descriptor" , input = "character" ),
function(descriptor, input, partial=FALSE){
        stopifnot(is.logical(partial), length(partial) == 1)
	.Call(Descriptor__readASCIIFromString, descriptor@pointer, input, partial)
} )

setMethod( "readASCII", c( descriptor = "Descriptor" ),
function( descriptor, input, partial=FALSE){
        stopifnot(is.logical(partial), length(partial) == 1)
	if( !inherits( input, "connection" ) ){
		stop( "can only read from connections" )
	}
	wasopen <- identical( summary(input)[["opened"]], "opened" )
	if( !wasopen ) open( input, "rb" )
        stopifnot(summary(input)[["text"]] == "binary")
	message <- .Call(Descriptor__readASCIIFromConnection, descriptor@pointer, input, partial)
    close(input)
	message
} )




setGeneric( "readJSON", function( descriptor, input ){
	standardGeneric( "readJSON" )
} )

setMethod( "readJSON", c( descriptor = "Descriptor" , input = "character" ),
function(descriptor, input){
	.Call(Descriptor__readJSONFromString, descriptor@pointer, input)
} )

setMethod( "readJSON", c( descriptor = "Descriptor" ),
function( descriptor, input){
	if( !inherits( input, "connection" ) ){
		stop( "can only read from connections" )
	}
	wasopen <- identical( summary(input)[["opened"]], "opened" )
	if( !wasopen ) open( input, "rb" )
        stopifnot(summary(input)[["text"]] == "binary")
	message <- .Call(Descriptor__readJSONFromConnection, descriptor@pointer, input)
	close(input)
	message
} )
