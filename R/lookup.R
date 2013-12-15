
# attaches the descriptor pool to the search path at the given
# position

OTABLE <- NULL
NAMESPACE <- environment()

attachDescriptorPool <- function(pos = 2) {
    if (is.null(OTABLE)) {
        ##unlockBinding( "OTABLE", NAMESPACE )
        otable <- .Call("newProtocolBufferLookup", pos, PACKAGE = "RProtoBuf")
        #attach(otable, pos=pos, name="RProtoBuf:DescriptorPool")
        assign("OTABLE", otable, envir = NAMESPACE, inherits = FALSE)
        lockBinding("OTABLE", NAMESPACE )
    }

}

