# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

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
	.Call( "ArrayInputStream_new", payload, -1L, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayInputStream", c( payload = "raw", block_size = "integer" ) , 
function(payload, block_size){
	.Call( "ArrayInputStream_new", payload, block_size, PACKAGE = "RProtoBuf" )
} )
setMethod( "ArrayInputStream", c( payload = "raw", block_size = "numeric" ) , 
function(payload, block_size){
	.Call( "ArrayInputStream_new", payload, as.integer(block_size), PACKAGE = "RProtoBuf" )
} )

# }}}
