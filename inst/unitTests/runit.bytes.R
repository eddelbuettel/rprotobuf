
.setUp <- function(){
    if( ! exists( "TestBytes", "RProtoBuf:DescriptorPool" ) ){
        unitest.proto.file <- system.file( "unitTests", "data", "bytes.proto", package = "RProtoBuf" )
        readProtoFiles(file = unitest.proto.file)
    }
}

test.all <- function() {
    test <- new(TestBytes, req = "abc", rep = list(charToRaw("def"), raw(10)))
    checkEquals(rawToChar(test$req), "abc")
    test$req <- charToRaw("abc")
    checkEquals(rawToChar(test$req), "abc")
    checkEquals(rawToChar(test$opt), "hello world")
    checkEquals(test$rep, list(charToRaw("def"), raw(10)))
    test$rep[[3]]=charToRaw("ghi")
    checkEquals(test$rep, list(charToRaw("def"), raw(10), charToRaw("ghi")))
    ser <- serialize(test, NULL)
    test1 <- read(TestBytes, ser)
    checkEquals(rawToChar(test1$req), "abc")
    checkEquals(rawToChar(test1$opt), "hello world")
    checkEquals(test1$rep, list(charToRaw("def"), raw(10), charToRaw("ghi")))

    # Test raw(10) can be set to a single req field.
    test$req <- raw(10)
    checkEquals(length(test$req), 10)
    checkTrue(all(test$req == raw(10)))
}
