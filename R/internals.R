# set of functions not supposed to be called by the end user
# these are thin wrappers around C functions, to help with 
# the error trapping on R side

#' thin wrapper around the C function of the same name
#'
#' @param files list of proto files to import
#' @param dir directory in which to look for proto files (ignored if files is given)
#' 
#' @return invisible(NULL)
readProtoFiles <- function( 
	files= list.files( dir, pattern = "\\.proto$", full.names = TRUE ), 
	dir = getwd()
	){
	
	if( !is.character( files )  ){
		stop( "file should be a character vector" )
	}
	# TODO: we need to pass the full path of the file
	#       or create a mapping from the current working directory
	#       in the DiskSourceTree 
	
	ex <- sapply( files, file.exists )
	if( ! any( ex ) ){
		stop( "none of the files exist" ) 
	}
	files <- files[ex]

	.Call( "readProtoFiles", files, PACKAGE = "RProtoBuf" )
	invisible(NULL)
}

