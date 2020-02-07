
library(RProtoBuf)

# this is executed before each test function
#.setUp <- function() {
if (! exists("protobuf_unittest_import.TestAllTypes", "RProtoBuf:DescriptorPool")) {
    unitest.proto.file <- system.file("tinytest", "data", "unittest.proto", package = "RProtoBuf")
    readProtoFiles(file = unitest.proto.file)
}
#}

#.tearDown <- function() {}

#test.import <- function() {
expect_true(exists("protobuf_unittest_import.ImportMessage", "RProtoBuf:DescriptorPool"),
            info = "exists( protobuf_unittest_import.ImportMessage ) ")
expect_true(exists( "protobuf_unittest_import.ImportEnum", "RProtoBuf:DescriptorPool" ),
            info = "exists( protobuf_unittest_import.ImportEnum ) ")
expect_equal(names(as.list( protobuf_unittest_import.ImportMessage)), "d",
             info = "names( protobuf_unittest_import.ImportMessage ) == 'd'")
import_enum <- as.list(protobuf_unittest_import.ImportEnum )
expect_true(all( c("IMPORT_FOO", "IMPORT_BAR", "IMPORT_BAZ") %in% names(import_enum)),
            info = "expected names for 'protobuf_unittest_import.ImportEnum'")
expect_equal(unlist(unname(import_enum)), 7:9,
             info = "expected values for 'protobuf_unittest_import.ImportEnum' ")
#}

#test.readProtoFile <- function() {
expect_true(exists( "protobuf_unittest.TestAllTypes", "RProtoBuf:DescriptorPool" ),
            info = "exists( protobuf_unittest_import.TestAllTypes ) ")
expect_true(exists( "protobuf_unittest.TestAllTypes.NestedMessage", "RProtoBuf:DescriptorPool" ),
            info = "exists( protobuf_unittest_import.TestAllTypes.NestedMessage ) " )
expect_true(exists( "protobuf_unittest.TestAllTypes.NestedEnum", "RProtoBuf:DescriptorPool" ),
            info = "exists( protobuf_unittest_import.TestAllTypes.NestedEnum ) " )
expect_true(exists( "protobuf_unittest.TestAllTypes.OptionalGroup", "RProtoBuf:DescriptorPool" ),
          info = "exists( protobuf_unittest.TestAllTypes.OptionalGroup ) " )
types <- c("int32", "int64", "uint32", "uint64", "sint32", "sint64",
           "fixed32", "fixed64", "sfixed32", "sfixed64", "float", "double",
           "bool", "string", "bytes" )
fieldnames <- names( as.list( protobuf_unittest.TestAllTypes ) )
prefixes <- c("optional", "default", "repeated" )
for (prefix in prefixes ) {
    for (type in types ) {
        expect_true(sprintf( "%s_%s", prefix, type ) %in% fieldnames,
                  info = sprintf( "%s_%s in field names", prefix, type))
    }
    expect_true(sprintf("%s_foreign_enum"  , prefix ) %in% fieldnames,
              info = sprintf( "%s_foreign_enum in field names"   , prefix ) )
    expect_true(sprintf("%s_import_enum"   , prefix ) %in% fieldnames,
              info = sprintf( "%s_import_enum in field names"    , prefix ) )
}
expect_true(exists( "protobuf_unittest.ForeignMessage", "RProtoBuf:DescriptorPool"),
          info = "exists( protobuf_unittest.ForeignMessage ) " )
expect_equal(names(as.list(protobuf_unittest.ForeignMessage)), "c")
expect_true(exists( "protobuf_unittest.ForeignEnum", "RProtoBuf:DescriptorPool"),
          info = "exists( protobuf_unittest.ForeignEnum ) ")
foreign_enum <- as.list( protobuf_unittest.ForeignEnum )
expect_equal(length(foreign_enum), 3L,
            info = "length( protobuf_unittest.ForeignEnum ) == 3" )
expect_true(all(c("FOREIGN_FOO", "FOREIGN_BAR", "FOREIGN_BAZ") %in% names( foreign_enum )),
          info = "expected names for enum `protobuf_unittest.ForeignEnum`" )
expect_equal( unlist(unname(as.list(protobuf_unittest.ForeignEnum))), 4:6,
            info = "expected values for enum `protobuf_unittest.ForeignEnum`" )
#}

## Early versions of RProtoBuf did not support repeated messages properly.
#test.repeatedFields <- function() {
test <- new(protobuf_unittest.TestAllTypes)
test$add("repeated_int32", c(1:5))
expect_equal(test$repeated_int32, c(1:5))

test$repeated_int32 <- 1
expect_equal(test$repeated_int32, 1)

## Prior to RProtoBuf v0.2.5, this was not handled properly.
test.2 <- new(protobuf_unittest.TestAllTypes,
              repeated_string=c("foo", "bar"))
expect_equal(test.2$repeated_string, c("foo", "bar"))

## Versions of RProtoBuf <= 0.2.5 had non-deterministic behavior due to a
## memory management bug when setting a repeated field to a
## non-vector type (e.g. a Message).
test$repeated_foreign_message <- list(new(protobuf_unittest.ForeignMessage,
                                          c = 1),
                                      new(protobuf_unittest.ForeignMessage,
                                          c = 2))
expect_equal(length(test$repeated_foreign_message), 2)
test$repeated_foreign_message <- new(protobuf_unittest.ForeignMessage,
                                     c = 3)
expect_equal(length(test$repeated_foreign_message), 1)
#}

#test.repeated.bools <- function() {
test <- new(protobuf_unittest.TestAllTypes)
test$add("repeated_bool", c(TRUE, FALSE))
expect_equal(test$repeated_bool, c(TRUE, FALSE))

test$add("repeated_bool", as.integer(c(TRUE, FALSE)))
test$add("repeated_bool", as.numeric(c(TRUE, FALSE)))

expect_equal(test$repeated_bool, rep(c(TRUE, FALSE), 3))

## Verify that we don't silently cast NA into TRUE or FALSE.
expect_error(test$add("repeated_bool", c(TRUE, FALSE, NA)))
#}

## Versions of RProtoBuf <= 0.2.5 would terminate the R instance with unhandled Rcpp exceptions.
#test.invalidAssignments <- function() {
test <- new(protobuf_unittest.TestAllTypes)
expect_error(test$optional_int32 <- 1:10)
#}

## Versions of RProtoBuf <= 0.2.5 did not distinguish between non-existant
## and not-set fields with has().
#test.has <- function() {
test <- new(protobuf_unittest.TestAllTypes)
test$add("repeated_int32", c(1:5))
expect_true( has(test, "repeated_int32"))
expect_true( test$has("repeated_int32"))
expect_true( is.null(test$has("nonexistant")))
expect_true( !test$has("optional_int32"))
#}
