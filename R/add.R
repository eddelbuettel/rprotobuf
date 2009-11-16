
setGeneric( "add", function(object, field, values){
	standardGeneric( "add" )
} )
setMethod( "add", "protobufMessage", function( object, field, values ){
	
	if( is( values, "protobufMessage" ) ){
		values <- list( values )
	}
	
	.Call( "message_add_values", object@pointer, field, values, PACKAGE = "RProtoBuf" )
	invisible( object )
} )

