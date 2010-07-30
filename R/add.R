
setGeneric( "add", function(object, field, values){
	standardGeneric( "add" )
} )
setMethod( "add", "Message", function( object, field, values ){
	
	if( is( values, "Message" ) ){
		values <- list( values )
	}
	
	.Call( "Message__add_values", object@pointer, field, values, PACKAGE = "RProtoBuf" )
	invisible( object )
} )

