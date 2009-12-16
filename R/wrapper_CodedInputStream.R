
setGeneric( "ReadRaw", function(object, size ){
	standardGeneric( "ReadRaw" )
} )
setMethod( "ReadRaw", c( object="ZeroCopyInputStream", size = "integer" ), function(object, size){
	.Call( "ZeroCopyInputStream_ReadRaw", object@pointer, size, PACKAGE = "RProtoBuf" )
} )

setGeneric( "ReadString", function(object, size ){
	standardGeneric( "ReadString" )
} )
setMethod( "ReadString", c( object="ZeroCopyInputStream", size = "integer" ), function(object, size){
	.Call( "ZeroCopyInputStream_ReadString", object@pointer, size, PACKAGE = "RProtoBuf" )
} )

