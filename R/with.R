# S3 dispatch does not work for some reason

generateActiveBindings <- function(data){
	env <- new.env( parent = environment() )
	xp <- data@pointer
	names <- .Call( "getMessageFieldNames", xp, PACKAGE = "RProtoBuf" ) 
	
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

with.protobufMessage <- function( data, expr, ...){
	env <- generateActiveBindings(data)
  	eval( substitute( expr ), env = env )
}

within.protobufMessage <- function(data, expr, ... ){
	env <- generateActiveBindings(data)
  	eval( substitute( expr ), env = env )
  	data
}

