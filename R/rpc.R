
IMPLEMENTATIONS <- new.env( parent = emptyenv() )

check_valid_implementation <- function( method, implementation ){
	if( !is.function( implementation ) ){
		stop( "should be a function" )
	}
	if( !identical( length(formals(implementation)), 1L ) ){
		stop( "should have exactly one argument" )
	}
	invisible(NULL)
}

setGeneric( "invokeLocally", function( method, message ){
	standardGeneric( "invokeLocally" ) 
} )

setMethod( "invokeLocally", c(method = "protobufMethodDescriptor", message = "protobufMessage"), 
function( method, message){
	# check that message is of correct type
	valid <- .Call( "valid_input_message", method@pointer, message@pointer, 
		PACKAGE = "RProtoBuf" )
	if( !valid ){
		expected <- .Call( "get_method_input_type", method@pointer, PACKAGE = "RProtoBuf" )@type
		stop( sprintf( "invalid input message, expecting a message of type : %s", expected ) )
	}
	
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


setMethod( "$", "protobufMethodDescriptor", function(x, name ){
	switch( name, 
		"invokeLocally" = function(...) invokeLocally(x, ...),
		"implementation" = if( x@name %in% names(IMPLEMENTATIONS) ){
			get( x@name, IMPLEMENTATIONS )
		}, 
		"name" = function(...) name(x, ...), 
		"toString"  = function() toString(x) , 
		"as.character" = function() as.character(x), 
		"fileDescriptor" = function() fileDescriptor(x ),
		"input_type" = function() input_type(x), 
		"output_type" = function() output_type(x),
		
		invisible( NULL)
	)
} )

setMethod( "$<-", "protobufMethodDescriptor", function(x, name, value ){
	
	if( identical( name, "implementation" ) ){
		check_valid_implementation( x, value )
		assign( x@name, value, envir = IMPLEMENTATIONS )
	}
	x
} )


# client side rpc

# channel <- function( host = "localhost", port ){
# 	.Call( "getChannel", host, port, PACKAGE = "RProtoBuf" )
# }
# 
# getChannelId <- function( channel ){
# 	.Call( "getChannelId", channel@pointer, PACKAGE = "RProtoBuf" )
# }
# 
# setGeneric( "invoke" , function(method, message, channel){
# 	standardGeneric( "invoke" ) 
# } )
# setMethod( "invoke", c( method = "protobufMethodDescriptor", message = "protobufMessage", channel = "RpcChannel" ), 
# function( method, message, channel){
# 	.Call( "invoke", method@pointer, message@pointer, channel@pointer, 
# 		PACKAGE = "RProtoBuf" )
# } )

