
.onLoad <- function(libname, pkgname ){
	readProtoFiles( package = pkgname )
	attachDescriptorPool( pos = length(search()) )
}

