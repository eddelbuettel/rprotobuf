
#' throw a particular protobuf error condition
#' all conditions have the class "ProtobufError", "error" and "condition"
#' plus any number of classes as defined by the class argument
#'
#' @param message the message of the error
#' @param class the sub class of the condition
throw <- function( message = "protobuf error", class = NULL ){
	
	callstack <- sys.calls()
	ncalls <- length(callstack)
	call <- if( ncalls > 1L) callstack[[ ncalls - 1L ]] else match.call()
	classes <- c( class, "ProtobufError", "error", "condition" )
	condition <- structure( 
		list( message = message, call = call ), 
		class = classes )
	stop( condition )
}

