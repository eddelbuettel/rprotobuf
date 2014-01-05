
setGeneric( "ReadRaw", function(object, size ){
	standardGeneric( "ReadRaw" )
} )
setMethod( "ReadRaw", c( object="ZeroCopyInputStream", size = "integer" ), function(object, size){
	.Call( "ZeroCopyInputStream_ReadRaw", object@pointer, size, PACKAGE = "RProtoBuf" )
} )
setMethod("ReadRaw", c( object="ZeroCopyInputStream", size = "numeric" ),
          function(object, size) {
        if (size %% 1 == 0) {
                .Call( "ZeroCopyInputStream_ReadRaw", object@pointer, as.integer(size),
                      PACKAGE = "RProtoBuf" )
        } else {
                stop("Size must be a whole number.")
        }
} )

setGeneric( "ReadString", function(object, size ){
	standardGeneric( "ReadString" )
} )
setMethod( "ReadString", c( object="ZeroCopyInputStream", size = "integer" ), function(object, size){
	.Call( "ZeroCopyInputStream_ReadString", object@pointer, size, PACKAGE = "RProtoBuf" )
} )
setMethod("ReadString", c( object="ZeroCopyInputStream", size = "numeric" ),
          function(object, size) {
        if (size %% 1 == 0) {
                .Call("ZeroCopyInputStream_ReadString", object@pointer, as.integer(size),
                      PACKAGE = "RProtoBuf" )
        } else {
                stop("Size must be a whole number.")
        }
} )

setGeneric( "ReadVarint32", function(object){
	standardGeneric( "ReadVarint32" )
} )
setMethod( "ReadVarint32", c( object="ZeroCopyInputStream"), function(object){
	.Call( "ZeroCopyInputStream_ReadVarint32", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "ReadLittleEndian32", function(object){
	standardGeneric( "ReadLittleEndian32" )
} )
setMethod( "ReadLittleEndian32", c( object="ZeroCopyInputStream"), function(object){
	.Call( "ZeroCopyInputStream_ReadLittleEndian32", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "ReadLittleEndian64", function(object){
	standardGeneric( "ReadLittleEndian64" )
} )
setMethod( "ReadLittleEndian64", c( object="ZeroCopyInputStream"), function(object){
	.Call( "ZeroCopyInputStream_ReadLittleEndian64", object@pointer, PACKAGE = "RProtoBuf" )
} )

setGeneric( "ReadVarint64", function(object){
	standardGeneric( "ReadVarint64" )
} )
setMethod( "ReadVarint64", c( object="ZeroCopyInputStream"), function(object){
	.Call( "ZeroCopyInputStream_ReadVarint64", object@pointer, PACKAGE = "RProtoBuf" )
} )
