
# serialization of protobuf messages
# at the moment, we grab the payload as a raw vector and send this 
# to the connection, but in the future, we will directly stream out 
# the payload to the connection

setGeneric( "serialize" )
setMethod( "serialize", c( object = "protobufMessage" ) , 
	function( object, connection, ascii = FALSE, refhook = NULL){
		
		iscon <- inherits(connection, "connection")
		isnull <- is.null( connection )
		
		if( is.character( connection ) ){
			# pretend it is a file name
			if( !file.exists(connection) ){
				# FIXME: hack to grab the absoulte path name
				file.create( connection )
				file <- tools:::file_path_as_absolute(connection)
				unlink( file )
			} else{
				file <- tools:::file_path_as_absolute(connection)
			}
			.Call( "serializeMessageToFile", object@pointer, file, PACKAGE = "RProtoBuf" )
			invisible( NULL)
		} else if( iscon || isnull ) {
			# not anymore
			# # right now we go through a file anyway
			# # and write it all back into the connection later
			# file <- tempfile()
			
			payload <- .Call( "getMessagePayload", object@pointer, PACKAGE = "RProtoBuf" )
			if( isnull ){
				payload
			} else{
				writeBin( payload, connection )
				invisible( NULL )
			}
			
		}
	}
)

# serializeToConn <- function( message, con ){
# 	.Call( "serialize_to_connection", message@pointer, con, PACKAGE = "RProtoBuf" ) 
# }


