
setGeneric( "identical" )
setMethod( "identical", c(x="protobufMessage", y = "protobufMessage" ), function( x, y, num.eq = TRUE, single.NA = TRUE, attrib.as.set = TRUE){
	.Call( "identical_messages", x@pointer, y@pointer, PACKAGE = "RProtoBuf" ) 
} )

setMethod( "==", c( e1 = "protobufMessage", e2 = "protobufMessage" ), function(e1, e2 ){
	.Call( "identical_messages", e1@pointer, e2@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "!=", c( e1 = "protobufMessage", e2 = "protobufMessage" ), function(e1, e2 ){
	! .Call( "identical_messages", e1@pointer, e2@pointer, PACKAGE = "RProtoBuf" )
} )

