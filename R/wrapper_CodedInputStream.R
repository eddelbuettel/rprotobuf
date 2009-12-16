
setGeneric( "ReadRaw", function(object, size ){
	standardGeneric( "ReadRaw" )
} )
setMethod( "ReadRaw", c( object="ZeroCopyInputStream", size = "numeric" ), function(object, size){
	.Call( "ZeroCopyInputStream_ReadRaw", object@pointer, size, PACKAGE = "RProtoBuf" )
} )

