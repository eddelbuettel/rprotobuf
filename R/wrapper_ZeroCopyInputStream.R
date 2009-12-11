
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

