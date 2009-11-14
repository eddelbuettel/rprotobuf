
setGeneric( "identical" )
setMethod( "identical", c(x="protobufMessage", y = "protobufMessage" ), function( x, y, num.eq = TRUE, single.NA = TRUE, attrib.as.set = TRUE){
	.Call( "identical_messages", x@pointer, y@pointer, PACKAGE = "RProtoBuf" ) 
} )

