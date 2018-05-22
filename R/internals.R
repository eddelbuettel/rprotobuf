# set of functions not supposed to be called by the end user
# these are thin wrappers around C functions, to help with
# the error trapping on R side

#' thin wrapper around the C function of the same name
#'
#' @param files list of proto files to import
#' @param dir directory in which to look for proto files (ignored if files is given)
#' @param package if specified, proto files are imported from the "proto" directory
#'                of the package
#' @return invisible(NULL)
readProtoFiles <- function(files,
                           dir,
                           package = "RProtoBuf",
                           pattern = "\\.proto$",
                           lib.loc = NULL
	){

	if( missing( files ) ){
		if( missing( dir ) ){
			if( missing(package) ){
				dir <- getwd()
			} else {
				dir <- system.file( "proto", package = package, lib.loc = lib.loc )
				if( !file.exists( dir ) ){
					stop( sprintf("package '%s' does not have a 'proto' directory", package) )
				}
			}
		}
		files <- list.files( dir, pattern = pattern, full.names = TRUE )
	} else {
		if( !is.character( files )  ){
			stop( "'file' should be a character vector" )
		}

		ex <- sapply( files, file.exists )
		if( ! any( ex ) ){
			stop( "none of the files exist" )
		}

		# TODO: we need to pass the full path of the file
		#       or create a mapping from the current working directory
		#       in the DiskSourceTree
		files <- sapply(files[ex], function(x) file_path_as_absolute(x) )
	}
	directories <- unique( c( getwd(), dirname(files) ) )
	.Call( "readProtoFiles_cpp", files, directories, PACKAGE = "RProtoBuf" )
	invisible(NULL)
}

readProtoFiles2 <- function(files,
                            dir = ".",
                            pattern = "\\.proto$",
                            recursive = FALSE,
                            protoPath = getwd()
	){

	if( !is.character( protoPath ) || length( protoPath ) < 1 ){
		stop( "'protoPath' should be a character vector with at least one element" )
	}
	protoPath <- unique( normalizePath( protoPath ) )

	# Search for the base directory in the search path that contains the given filepath.
	file_search <- function(filepaths) {
		helper <- function(filepath) {
			if( file.exists( filepath ) && file_path_as_absolute( filepath ) == filepath ){
				return( TRUE )
			}
			for( baseDir in protoPath ){
				if( file.exists( file.path( baseDir, filepath ) ) ){
					return( baseDir )
				}
			}
			return( NA_character_ )
		}
		sapply( filepaths, helper )
	}

	if( missing( files ) ) {
		if( !is.character( dir ) || length( dir ) < 1 ){
			stop( "'dir' argument must be non-empty when 'files' is missing" )
		}

		files <- c()
		# search for dir relative to the search path.
		baseDirs <- file_search( dir )
		for( i in seq_along( dir ) ) {
			absPaths <-
				list.files( file.path( baseDirs[i], dir[i] ), pattern = pattern,
                    recursive = recursive, full.names = TRUE )
			files <- c( files, substr( absPaths, nchar( baseDirs[i] ) + 2, 10000L ) )
			files <- sub( "^\\./", "", files )
		}
	}
	missing_files <- files[ is.na( file_search( files ) ) ]
	if( length( missing_files) > 0 ){
		warning( "Missing files: ", paste(missing_files, collapse = ", " ) )
	}

	.Call( "readProtoFiles_cpp", files, protoPath, PACKAGE = "RProtoBuf" )
	invisible(NULL)
}

resetDescriptorPool <- function(){
	.Call( "resetDescriptorPool_cpp", PACKAGE = "RProtoBuf" )
	readProtoFiles2( protoPath=system.file( "proto", package="RProtoBuf", lib.loc=.RProtoBuf_libname) )
	invisible(NULL)
}

getProtobufLibVersion <- function( format = FALSE ){
	version <- .Call( "get_protobuf_library_version", PACKAGE = "RProtoBuf" )

	if( format ){
		major <- version %/% 10^6
		minor <- ( tmp <- (version - major * 10^6) ) %/% 10^3
		revision <- (tmp - minor * 10^3 )
		sprintf( "%d.%d.%d", major, minor, revision )
	} else {
		version
	}

}



