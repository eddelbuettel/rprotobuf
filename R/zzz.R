
.onLoad <- function(libname, pkgname ){
    ##minversion <- packageDescription(pkgname, lib.loc=libname)$MinimumLibProtoVersion
    ##minversion <- as.integer( gsub( "[[:space:]]+", "", minversion ) )
    ##.Call(check_libprotobuf_version, minversion)
    readProtoFiles2( protoPath=system.file( "proto", package=pkgname, lib.loc=libname ) )
    attachDescriptorPool( pos = length(search()) )
    options("RProtoBuf.int64AsString" = FALSE)
    #if( exists( ".httpd.handlers.env", asNamespace( "tools" ) ) ){
    #    e <- tools:::.httpd.handlers.env
    #    e[["RProtoBuf"]] <- RProtoBuf.http.handler
    #}
    .RProtoBuf_libname <<- libname
}

.onAttach <- function(libname, pkgName) {
    if (interactive()) {
        packageStartupMessage("RProtoBuf ", packageVersion("RProtoBuf"),
                              " using Protocol Buffers library version ",
                              format(getProtobufLibVersion(TRUE)), ".")
    }
}

utils::globalVariables(c("Descriptor__FindEnumTypeByName",
                         "ServiceDescriptor_getMethodByIndex",
                         "ServiceDescriptor_getMethodByName",
                         "ServiceDescriptor_method_count",
                         "ServiceDescriptor__method"))
