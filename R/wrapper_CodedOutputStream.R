setGeneric( "WriteRaw", function(object, payload){
	standardGeneric("WriteRaw")
} )
setMethod( "WriteRaw", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteRaw, object@pointer, payload)
} )

setGeneric( "WriteString", function(object, payload){
	standardGeneric("WriteString")
} )
setMethod( "WriteString", c(object="ZeroCopyOutputStream", payload = "character" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteString, object@pointer, payload)
} )

setGeneric( "WriteLittleEndian32", function(object, payload){
	standardGeneric("WriteLittleEndian32")
} )
setMethod( "WriteLittleEndian32", c(object="ZeroCopyOutputStream", payload = "integer" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian32, object@pointer, payload)
} )
setMethod( "WriteLittleEndian32", c(object="ZeroCopyOutputStream", payload = "numeric" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian32, object@pointer, payload)
} )
setMethod( "WriteLittleEndian32", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian32, object@pointer, payload)
} )

setGeneric( "WriteLittleEndian64", function(object, payload){
	standardGeneric("WriteLittleEndian64")
} )
setMethod( "WriteLittleEndian64", c(object="ZeroCopyOutputStream", payload = "integer" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian64, object@pointer, payload)
} )
setMethod( "WriteLittleEndian64", c(object="ZeroCopyOutputStream", payload = "numeric" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian64, object@pointer, payload)
} )
setMethod( "WriteLittleEndian64", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteLittleEndian64, object@pointer, payload)
} )


setGeneric( "WriteVarint32", function(object, payload){
	standardGeneric("WriteVarint32")
} )
setMethod( "WriteVarint32", c(object="ZeroCopyOutputStream", payload = "integer" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint32, object@pointer, payload)
} )
setMethod( "WriteVarint32", c(object="ZeroCopyOutputStream", payload = "numeric" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint32, object@pointer, payload)
} )
setMethod( "WriteVarint32", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint32, object@pointer, payload)
} )


setGeneric( "WriteVarint64", function(object, payload){
	standardGeneric("WriteVarint64")
} )
setMethod( "WriteVarint64", c(object="ZeroCopyOutputStream", payload = "integer" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint64, object@pointer, payload)
} )
setMethod( "WriteVarint64", c(object="ZeroCopyOutputStream", payload = "numeric" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint64, object@pointer, payload)
} )
setMethod( "WriteVarint64", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call(ZeroCopyOutputStream_WriteVarint64, object@pointer, payload)
} )
