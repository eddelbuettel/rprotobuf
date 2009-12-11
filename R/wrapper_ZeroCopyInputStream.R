# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

# {{{ methods
setGeneric( "Next", function(object, size ){
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
setMethod( "Next", "ZeroCopyInputStream", function(object, size){
	.Call( "ZeroCopyInputStream_Next", object@pointer, size, PACKAGE = "RProtoBuf" )
} )

setMethod( "BackUp", "ZeroCopyInputStream", function(object, count){
	.Call( "ZeroCopyInputStream_BackUp", object@pointer, count, PACKAGE = "RProtoBuf" )
} )

setMethod( "ByteCount", "ZeroCopyInputStream", function(object){
	.Call( "ZeroCopyInputStream_ByteCount", object@pointer, PACKAGE = "RProtoBuf" )
} )

setMethod( "Skip", "ZeroCopyInputStream", function(object, count){
	.Call( "ZeroCopyInputStream_Skip", object@pointer, count, PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ zero copy output stream
setMethod( "Next", c( object = "ZeroCopyOutputStream", size = "raw" ), function(object, size){
	.Call( "ZeroCopyOutputStream_Next", object@pointer, size, PACKAGE = "RProtoBuf" )
} )

setMethod( "BackUp", "ZeroCopyOutputStream", function(object, count){
	.Call( "ZeroCopyOutputStream_BackUp", object@pointer, count, PACKAGE = "RProtoBuf" )
} )

setMethod( "ByteCount", "ZeroCopyOutputStream", function(object){
	.Call( "ZeroCopyOutputStream_ByteCount", object@pointer, PACKAGE = "RProtoBuf" )
} )
# }}}
