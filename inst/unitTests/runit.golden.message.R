
# this is executed before each test function
.setUp <- function(){
	if( ! exists( "protobuf_unittest_import.TestAllTypes", "RProtoBuf:DescriptorPool" ) ){
		unitest.proto.file <- system.file( "unitTests", "data", "unittest.proto", package = "RProtoBuf" )
		readProtoFiles( file = unitest.proto.file )
	}
}

.tearDown <- function(){}

test.import <- function(){
	checkTrue( exists( "protobuf_unittest_import.ImportMessage", "RProtoBuf:DescriptorPool" ) ,
		msg = "exists( protobuf_unittest_import.ImportMessage ) " )
	checkTrue( exists( "protobuf_unittest_import.ImportEnum", "RProtoBuf:DescriptorPool" ) ,
		msg = "exists( protobuf_unittest_import.ImportEnum ) " )
	checkEquals(
		names(as.list( protobuf_unittest_import.ImportMessage)),
		"d",
		msg = "names( protobuf_unittest_import.ImportMessage ) == 'd'" )
	import_enum <- as.list(protobuf_unittest_import.ImportEnum )
	checkTrue( all( c("IMPORT_FOO", "IMPORT_BAR", "IMPORT_BAZ") %in% names(import_enum) ),
		msg = "expected names for 'protobuf_unittest_import.ImportEnum'" )
	checkEquals( unlist(unname(import_enum)), 7:9,
		msg = "expected values for 'protobuf_unittest_import.ImportEnum' " )
}

test.readProtoFile <- function(){
	checkTrue( exists( "protobuf_unittest.TestAllTypes", "RProtoBuf:DescriptorPool" ),  msg = "exists( protobuf_unittest_import.TestAllTypes ) " )
	checkTrue( exists( "protobuf_unittest.TestAllTypes.NestedMessage", "RProtoBuf:DescriptorPool" ),  msg = "exists( protobuf_unittest_import.TestAllTypes.NestedMessage ) " )
	checkTrue( exists( "protobuf_unittest.TestAllTypes.NestedEnum", "RProtoBuf:DescriptorPool" ),  msg = "exists( protobuf_unittest_import.TestAllTypes.NestedEnum ) " )
	checkTrue( exists( "protobuf_unittest.TestAllTypes.OptionalGroup", "RProtoBuf:DescriptorPool" ) ,  msg = "exists( protobuf_unittest.TestAllTypes.OptionalGroup ) " )
	types <- c("int32", "int64", "uint32", "uint64", "sint32", "sint64",
		"fixed32", "fixed64", "sfixed32", "sfixed64", "float", "double",
		"bool", "string", "bytes" )
	fieldnames <- names( as.list( protobuf_unittest.TestAllTypes ) )
	prefixes <- c("optional", "default", "repeated" )
	for( prefix in prefixes ){
		for( type in types ){
			checkTrue( sprintf( "%s_%s", prefix, type ) %in% fieldnames, msg = sprintf( "%s_%s in field names", prefix, type ) )
		}
		checkTrue( sprintf("%s_foreign_enum"  , prefix ) %in% fieldnames, msg = sprintf( "%s_foreign_enum in field names"   , prefix ) )
		checkTrue( sprintf("%s_import_enum"   , prefix ) %in% fieldnames, msg = sprintf( "%s_import_enum in field names"    , prefix ) )
	}
	checkTrue( exists( "protobuf_unittest.ForeignMessage", "RProtoBuf:DescriptorPool" ) ,  msg = "exists( protobuf_unittest.ForeignMessage ) " )
	checkEquals( names(as.list(protobuf_unittest.ForeignMessage)), "c" )
	checkTrue( exists( "protobuf_unittest.ForeignEnum", "RProtoBuf:DescriptorPool" ) ,  msg = "exists( protobuf_unittest.ForeignEnum ) " )
	foreign_enum <- as.list( protobuf_unittest.ForeignEnum )
	checkEquals( length(foreign_enum), 3L, msg = "length( protobuf_unittest.ForeignEnum ) == 3" )
	checkTrue( all( c("FOREIGN_FOO", "FOREIGN_BAR", "FOREIGN_BAZ") %in% names( foreign_enum ) ), msg = "expected names for enum `protobuf_unittest.ForeignEnum`" )
	checkEquals( unlist(unname(as.list(protobuf_unittest.ForeignEnum))), 4:6, msg = "expected values for enum `protobuf_unittest.ForeignEnum`" )
}

# Early versions of RProtoBuf did not support repeated messages properly.
test.repeatedFields <- function(){
	test <- new(protobuf_unittest.TestAllTypes)
	test$add("repeated_int32", c(1:5))
	checkEquals(test$repeated_int32, c(1:5))

	test$repeated_int32 <- 1
	checkEquals(test$repeated_int32, 1)

        # Prior to RProtoBuf v0.2.5, this was not handled properly.
        test.2 <- new(protobuf_unittest.TestAllTypes,
                      repeated_string=c("foo", "bar"))
        checkEquals(test.2$repeated_string, c("foo", "bar"))

        # Versions of RProtoBuf <= 0.2.5 had non-deterministic behavior due to a
        # memory management bug when setting a repeated field to a
        # non-vector type (e.g. a Message).
	test$repeated_foreign_message <- list(new(protobuf_unittest.ForeignMessage,
						  c = 1),
					      new(protobuf_unittest.ForeignMessage,
						  c = 2))
	checkEquals(length(test$repeated_foreign_message), 2)
	test$repeated_foreign_message <- new(protobuf_unittest.ForeignMessage,
					     c = 3)
	checkEquals(length(test$repeated_foreign_message), 1)
}

test.repeated.bools <- function() {
	test <- new(protobuf_unittest.TestAllTypes)
        test$add("repeated_bool", c(TRUE, FALSE))
        checkEquals(test$repeated_bool, c(TRUE, FALSE))

        test$add("repeated_bool", as.integer(c(TRUE, FALSE)))
        test$add("repeated_bool", as.numeric(c(TRUE, FALSE)))

        checkEquals(test$repeated_bool, rep(c(TRUE, FALSE), 3))

        # Verify that we don't silently cast NA into TRUE or FALSE.
        checkException(test$add("repeated_bool"), c(TRUE, FALSE, NA))
}

# Versions of RProtoBuf <= 0.2.5 would terminate the R instance with unhandled Rcpp exceptions.
test.invalidAssignments <- function(){
	test <- new(protobuf_unittest.TestAllTypes)
	checkException(test$optional_int32 <- 1:10)
}

# Versions of RProtoBuf <= 0.2.5 did not distinguish between non-existant
# and not-set fields with has().
test.has <- function(){
	test <- new(protobuf_unittest.TestAllTypes)
	test$add("repeated_int32", c(1:5))
	checkTrue( has(test, "repeated_int32"))
	checkTrue( test$has("repeated_int32"))
	checkTrue( is.null(test$has("nonexistant")))
	checkTrue( !test$has("optional_int32"))
}
