
# serialization of protobuf messages
# at the moment, we grab the payload as a raw vector and send this
# to the connection, but in the future, we will directly stream out
# the payload to the connection

setGeneric( "serialize" )
setMethod( "serialize", c( object = "Message" ) ,
	function( object, connection, ascii = FALSE, refhook = NULL){
                stopifnot(object$isInitialized())
		iscon <- inherits(connection, "connection")
		isnull <- is.null( connection )

		if( is.character( connection ) ){
			# pretend it is a file name
			if( !file.exists(connection) ){
				if( !file.exists( dirname(connection) ) ){
					stop( "directory does not exist" )
				}
				file <- normalizePath(connection, mustWork=FALSE)
			} else{
				file <- file_path_as_absolute(connection)
			}
			.Call( "Message__serialize_to_file", object@pointer, file, PACKAGE = "RProtoBuf" )
			invisible( NULL)
		} else if( iscon || isnull ) {

			# first grab the payload as a raw vector,
			payload <- .Call( "Message__get_payload", object@pointer, PACKAGE = "RProtoBuf" )
			if( isnull ){
				# just return it if the connection is NULL
				payload
			} else{
				# otherwise write the payload to the connection
				# FIXME: we might want to be more clever about this so that
				#        we don't have to store the full payload in memory
				#        but for now it will do just fine
				writeBin( payload, connection )
				invisible( NULL )
			}

		}
	}
)
