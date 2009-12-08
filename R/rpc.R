
setGeneric( "invoke", function( method, message, protocol){
	standardGeneric( "invoke" )
} )

check_valid_implementation <- function( method, implementation ){
	if( !is.function( implementation ) ){
		stop( "should be a function" )
	}
	if( !identical( length(formals(implementation)), 1L ) ){
		stop( "should have exactly one argument" )
	}
	invisible(NULL)
}

check_valid_input_message <- function( method, message){
	# check that message is of correct type
	valid <- .Call( "valid_input_message", method@pointer, message@pointer, 
		PACKAGE = "RProtoBuf" )
	if( !valid ){
		expected <- .Call( "get_method_input_type", method@pointer, PACKAGE = "RProtoBuf" )@type
		stop( sprintf( "invalid input message, expecting a message of type : %s", expected ) )
	}
}

setMethod( "invoke", c(method = "MethodDescriptor", message = "Message", protocol = "missing" ), 
function( method, message, protocol){
	# check that the message is valid
	check_valid_input_message( method, message )
	
	# grab the implementation
	if( exists( method@name, envir = IMPLEMENTATIONS ) ){
		impl <- get( method@name, envir = IMPLEMENTATIONS )
		check_valid_implementation( method, impl )
		result <- impl( message )
		valid <- .Call( "valid_output_message", method@pointer, message@pointer, 
			PACKAGE = "RProtoBuf" )
		if( !valid ){
			stop( "invalid method output" )
		}
		result
	} else{
		warning( "unimplemented method, returning output message prototype" )
		.Call( "get_method_output_prototype", method@pointer, PACKAGE = "RProtoBuf" )
	}
	
	# return the message
} )

setMethod( "invoke" , c( method = "MethodDescriptor", message = "Message", protocol = "RpcHTTP"), 
function(method, message, protocol ){
	# check that the message is valid
	check_valid_input_message( method, message )
	
	.Call( "invoke_method_http", method@pointer, message@pointer, 
		protocol@host, protocol@port, PACKAGE = "RProtoBuf" )
	
} )

