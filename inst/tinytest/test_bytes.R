
library(RProtoBuf)

#.setUp <- function(){
if( ! exists( "TestBytes", "RProtoBuf:DescriptorPool" ) ){
    unitest.proto.file <- system.file( "tinytest", "data", "bytes.proto", package = "RProtoBuf" )
    readProtoFiles(file = unitest.proto.file)
}
#}

#test.all <- function() {
test <- new(TestBytes, req = "abc", rep = list(charToRaw("def"), raw(10)))
expect_equal(rawToChar(test$req), "abc")
test$req <- charToRaw("abc")
expect_equal(rawToChar(test$req), "abc")
expect_equal(rawToChar(test$opt), "hello world")
expect_equal(test$rep, list(charToRaw("def"), raw(10)))
test$rep[[3]]=charToRaw("ghi")
expect_equal(test$rep, list(charToRaw("def"), raw(10), charToRaw("ghi")))
ser <- serialize(test, NULL)
test1 <- read(TestBytes, ser)
expect_equal(rawToChar(test1$req), "abc")
expect_equal(rawToChar(test1$opt), "hello world")
expect_equal(test1$rep, list(charToRaw("def"), raw(10), charToRaw("ghi")))

## Test raw(10) can be set to a single req field.
test$req <- raw(10)
expect_equal(length(test$req), 10)
expect_true(all(test$req == raw(10)))
#}
