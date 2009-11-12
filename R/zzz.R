
.onLoad <- function(libname, pkgname ){
	minversion <- packageDescription( pkgname)$MinimumLibProtoVersion
	minversion <- as.integer( gsub( "[[:space:]]+", "", minversion ) )
	.Call( "check_libprotobuf_version", minversion, PACKAGE = "RProtoBuf" )
	readProtoFiles( package = pkgname )
	attachDescriptorPool( pos = length(search()) )
}

