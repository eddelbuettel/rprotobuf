
.onLoad <- function(libname, pkgname ){
    ##minversion <- packageDescription(pkgname, lib.loc=libname)$MinimumLibProtoVersion
    ##minversion <- as.integer( gsub( "[[:space:]]+", "", minversion ) )
    ##.Call( "check_libprotobuf_version", minversion, PACKAGE = "RProtoBuf" )
    readProtoFiles( package=pkgname, lib.loc=libname )
    attachDescriptorPool( pos = length(search()) )
    options("RProtoBuf.int64AsString" = FALSE)
    #if( exists( ".httpd.handlers.env", asNamespace( "tools" ) ) ){
    #    e <- tools:::.httpd.handlers.env
    #    e[["RProtoBuf"]] <- RProtoBuf.http.handler
    #}
}
