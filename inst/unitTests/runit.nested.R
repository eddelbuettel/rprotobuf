.setUp <- function(){
    if( ! exists( "NestedOuter", "RProtoBuf:DescriptorPool" ) ) {
        ## None of the messages in unittest.proto is exactly right to tickle this bug.
        unitest.proto.file <- system.file( "unitTests", "data", "nested.proto", package = "RProtoBuf" )
        readProtoFiles(file = unitest.proto.file)
    }
}

# RProtoBuf before v0.2.5 had a bug whereby uninitialized memory was read and used
# to determine whether or not to update a nested message field in new() / update().
test.nested <- function() {
    for (i in 1:1000) {
        q <- new(NestedOuter, b=new(NestedInner, x=1))
        checkTrue(q$isInitialized())
    }
}
