
setGeneric( "identical" )
setMethod( "identical", c(x="Message", y = "Message" ), function( x, y, num.eq = TRUE, single.NA = TRUE, attrib.as.set = TRUE){
	.Call( "identical_messages", x@pointer, y@pointer, PACKAGE = "RProtoBuf" ) 
} )

setMethod( "==", c( e1 = "Message", e2 = "Message" ), function(e1, e2 ){
	.Call( "identical_messages", e1@pointer, e2@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "!=", c( e1 = "Message", e2 = "Message" ), function(e1, e2 ){
	! .Call( "identical_messages", e1@pointer, e2@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "all.equal" )
setMethod( "all.equal", c( target = "Message", current = "Message" ), 
	function(target, current, tolerance = .Machine$double.eps^0.5, ...){
	.Call( "all_equal_messages", target@pointer, current@pointer, tolerance, PACKAGE = "RProtoBuf" )
} )

