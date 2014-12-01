# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

# {{{ generics
setGeneric( "flush" )
setGeneric( "close" )
setGeneric( "GetErrno", function(object){
	standardGeneric( "GetErrno" )
} )
setGeneric( "SetCloseOnDelete", function(object, close=FALSE){
	standardGeneric( "SetCloseOnDelete" )
} )
# }}}

# {{{ methods
setGeneric( "Next", function(object, payload){
	standardGeneric( "Next" )
} )
setGeneric( "BackUp", function(object, count){
	standardGeneric( "BackUp" )
} )
setGeneric( "ByteCount", function(object){
	standardGeneric( "ByteCount" )
} )
setGeneric( "Skip", function(object, count){
	standardGeneric( "Skip" )
} )
# }}}

# {{{ zero input stream
setMethod( "Next", c( object = "ZeroCopyInputStream", payload = "missing"), function(object, payload){
	.Call( "ZeroCopyInputStream_Next", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "BackUp", "ZeroCopyInputStream", function(object, count){
	invisible(.Call( "ZeroCopyInputStream_BackUp", object@pointer, count, PACKAGE = "RProtoBuf" ))
} )

setMethod( "ByteCount", "ZeroCopyInputStream", function(object){
	.Call( "ZeroCopyInputStream_ByteCount", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "Skip", "ZeroCopyInputStream", function(object, count){
	invisible( .Call( "ZeroCopyInputStream_Skip", object@pointer, count, PACKAGE = "RProtoBuf" ) )
} )
# }}}

# {{{ zero copy output stream
setMethod( "Next", c( object = "ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call( "ZeroCopyOutputStream_Next", object@pointer, payload, PACKAGE = "RProtoBuf" )
} )

setMethod( "BackUp", "ZeroCopyOutputStream", function(object, count){
	invisible( .Call( "ZeroCopyOutputStream_BackUp", object@pointer, count, PACKAGE = "RProtoBuf" ) )
} )

setMethod( "ByteCount", "ZeroCopyOutputStream", function(object){
	.Call( "ZeroCopyOutputStream_ByteCount", object@pointer, PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ ArrayInputStream
setGeneric( "ArrayInputStream", function(payload, block_size){
	standardGeneric( "ArrayInputStream" )
} )
setMethod( "ArrayInputStream", c( payload = "raw", block_size = "missing" ) ,
function(payload, block_size){
	.Call( "ArrayInputStream__new", payload, -1L, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayInputStream", c( payload = "raw", block_size = "integer" ) ,
function(payload, block_size){
	.Call( "ArrayInputStream__new", payload, block_size, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayInputStream", c( payload = "raw", block_size = "numeric" ) ,
function(payload, block_size){
	.Call( "ArrayInputStream__new", payload, as.integer(block_size), PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ ArrayOutputStream constructor function
setGeneric( "ArrayOutputStream", function(size, block_size){
	standardGeneric( "ArrayOutputStream" )
} )
setMethod( "ArrayOutputStream", signature( size = "integer", block_size = "missing" ), function(size, block_size){
	.Call( "ArrayOutputStream__new", size, -1L, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayOutputStream", signature( size = "integer", block_size = "integer" ), function(size, block_size){
	.Call( "ArrayOutputStream__new", size, block_size, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayOutputStream", signature( size = "integer", block_size = "numeric" ), function(size, block_size){
	.Call( "ArrayOutputStream__new", size, as.integer(block_size) , PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayOutputStream", signature( size = "numeric", block_size = "missing" ), function(size, block_size){
	.Call( "ArrayOutputStream__new", as.integer(size), -1L, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayOutputStream", signature( size = "numeric", block_size = "integer" ),function(size, block_size){
	.Call( "ArrayOutputStream__new", as.integer(size), block_size, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayOutputStream", signature( size = "numeric", block_size = "numeric" ), function(size, block_size){
	.Call( "ArrayOutputStream__new", as.integer(size), as.integer(block_size) , PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ FileInputStream
setGeneric( "FileInputStream", function(filename, block_size = -1L, close.on.delete = FALSE ){
	standardGeneric( "FileInputStream" )
} )
setMethod( "FileInputStream", signature( filename = "character", block_size = "integer", close.on.delete = "logical" ), function(filename, block_size = -1L, close.on.delete = FALSE){
	full_filename <- file_path_as_absolute(filename)
	.Call( "FileInputStream_new", filename, block_size, close.on.delete, PACKAGE = "RProtoBuf" )
} )
setMethod( "close", "FileInputStream", function(con, ...){
	.Call( "FileInputStream_Close", con@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "GetErrno", "FileInputStream", function(object){
	.Call( "FileInputStream_GetErrno", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "SetCloseOnDelete", "FileInputStream", function(object, close=FALSE){
	invisible( .Call( "FileInputStream_SetCloseOnDelete", object@pointer, isTRUE(close), PACKAGE = "RProtoBuf" ) )
} )
# }}}

# {{{ FileOutputStream
setGeneric( "FileOutputStream", function(filename, block_size = -1L, close.on.delete = FALSE ){
	standardGeneric( "FileOutputStream" )
} )
setMethod( "FileOutputStream", signature( filename = "character", block_size = "integer", close.on.delete = "logical" ), function(filename, block_size = -1L, close.on.delete = FALSE){
	if( !file.exists( filename ) ){
		if( !file.exists( dirname(filename) ) ){
			stop( "directory does not exist" )
		}
		filename <- normalizePath(filename, mustWork=FALSE)
	} else{
		filename <- file_path_as_absolute(filename)
	}

	.Call( "FileOutputStream_new", filename, block_size, close.on.delete, PACKAGE = "RProtoBuf" )
} )
setMethod( "flush", "FileOutputStream", function(con){
	.Call( "FileOutputStream_Flush", con@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "close", "FileOutputStream", function(con, ...){
	.Call( "FileOutputStream_Close", con@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "GetErrno", "FileOutputStream", function(object){
	.Call( "FileOutputStream_GetErrno", object@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "SetCloseOnDelete", "FileOutputStream", function(object, close=FALSE){
	invisible( .Call( "FileOutputStream_SetCloseOnDelete", object@pointer, isTRUE(close), PACKAGE = "RProtoBuf" ) )
} )
# }}}

# {{{ ConnectionInputStream
setGeneric( "ConnectionInputStream", function(object, ...){
	standardGeneric( "ConnectionInputStream" )
} )
setMethod( "ConnectionInputStream", "connection", function(object, ...){
	sc <- summary( object )
	if( ! identical( sc[["can read"]], "yes") ){
		stop( "cannot read from connection" )
	}
	if( ! identical( sc[["text"]], "binary" ) ){
		stop( "not a binary connection" )
	}
	was_open <- isOpen( object )
	if( ! was_open ){
		open( object )
	}
	.Call( "ConnectionInputStream_new", object, was_open, PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ ConnectionOutputStream
setGeneric( "ConnectionOutputStream", function(object, ...){
	standardGeneric( "ConnectionOutputStream" )
} )
setMethod( "ConnectionOutputStream", "connection", function(object, ...){
	sc <- summary( object )
	if( ! identical( sc[["can write"]], "yes") ){
		stop( "cannot write to connection" )
	}
	if( ! identical( sc[["text"]], "binary" ) ){
		stop( "not a binary connection" )
	}
	was_open <- isOpen( object )
	if( ! was_open ){
		open( object )
	}
	.Call( "ConnectionOutputStream_new", object, was_open, PACKAGE = "RProtoBuf" )
} )
# }}}
