# S3 dispatch does not work for some reason

generateActiveBindings <- function(data){
	env <- new.env( parent = environment() )
	xp <- data@pointer
	names <- .Call( "Message__fieldNames", xp, PACKAGE = "RProtoBuf" )

	if( !is.null(names) && length(names) ){
		lapply( names, function(x ){
  		  makeActiveBinding( x, function(v){
  		    if( missing(v) ){
  		    	# get
  		      .Call( "getMessageField", xp, x )
  		    } else {
  		    	# set
  		      .Call( "setMessageField", xp, x, v )
  		    }
  		  }, env )
  		} )
  	}
  	env
}

with.Message <- function( data, expr, ...){
	envir <- generateActiveBindings(data)
  	eval( substitute( expr ), envir = envir )
}

within.Message <- function(data, expr, ... ){
	envir <- generateActiveBindings(data)
  	eval( substitute( expr ), envir = envir )
  	data
}

