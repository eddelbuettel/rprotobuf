
#' throw a particular protobuf error condition
#' all conditions have the class "ProtobufError", "error" and "condition"
#' plus any number of classes as defined by the class argument
#'
#' @param message the message of the error
#' @param class the sub class of the condition

# this is exported at the moment, but I would prefer it not to be
# so need to find a way to call a namespace private function from the
# C call
throw <- function( message = " error", class = NULL ){
	
	callstack <- sys.calls()
	ncalls <- length(callstack)
	call <- if( ncalls > 1L) callstack[[ ncalls - 1L ]] else match.call()
	classes <- c( class, "ProtobufError", "error", "condition" )
	condition <- structure( 
		list( message = message, call = call ), 
		class = classes )
	stop( condition )
}

