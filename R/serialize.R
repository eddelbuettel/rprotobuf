
# serialization of protobuf messages
# at the moment, we grab the payload as a raw vector and send this 
# to the connection, but in the future, we will directly stream out 
# the payload to the connection

setGeneric( "serialize" )
setMethod( "serialize", c( object = "protobufMessage" ) , 
	function( object, connection, ascii = FALSE, refhook = NULL){
		# grab the payload as a raw vector
		payload <- .Call( "getMessagePayload", object@pointer, PACKAGE = "RProtoBuf" )
		
		if( is.null(connection) ){
			payload
		} else {
			stop( "serialization of 'protobufMessage' to connection is not implemented yet" ) 
		}
		
	}
)

