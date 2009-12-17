
setGeneric( "WriteRaw", function(object, payload){
	standardGeneric("WriteRaw")
} )

setMethod( "WriteRaw", c(object="ZeroCopyOutputStream", payload = "raw" ), function(object, payload){
	.Call( "ZeroCopyOutputStream_WriteRaw", object@pointer, payload, 
		PACKAGE = "RProtoBuf" )
} )


