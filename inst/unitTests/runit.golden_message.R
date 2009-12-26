
.setUp <- function(){
	if( exists( "protobuf_unittest_import.TestAllTypes", "RProtoBuf:DescriptorPool" ) ){
		unitest_proto_file <- system.file( "unitTests", "data", "unittest.proto", package = "RProtoBuf" )
		readProtoFiles( file = unitest_proto_file ) 
	}
}

.tearDown <- function(){}

test.import <- function(){
	checkTrue( exists( "protobuf_unittest_import.ImportMessage", "RProtoBuf:DescriptorPool" ) , 
		msg = "exists( protobuf_unittest_import.ImportMessage ) " )
	checkTrue( exists( "protobuf_unittest_import.ImportEnum", "RProtoBuf:DescriptorPool" ) , 
		msg = "exists( protobuf_unittest_import.ImportEnum ) " )
}

test.read_proto_file <- function(){
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
		checkTrue( sprintf("%s_nested_message", prefix ) %in% fieldnames, msg = sprintf( "%_nested_message in field names" , prefix ) )
		checkTrue( sprintf("%s_foreign_enum"  , prefix ) %in% fieldnames, msg = sprintf( "%_foreign_enum in field names"   , prefix ) )
		checkTrue( sprintf("%s_import_enum"   , prefix ) %in% fieldnames, msg = sprintf( "%_import_enum in field names"    , prefix ) )
	}
	
	checkTrue( exists( "protobuf_unittest.ForeignMessage", "RProtoBuf:DescriptorPool" ) ,  msg = "exists( protobuf_unittest.ForeignMessage ) " )
	checkEquals( names(as.list(protobuf_unittest.ForeignMessage)), "c" )
	
	checkTrue( exists( "protobuf_unittest.ForeignEnum", "RProtoBuf:DescriptorPool" ) ,  msg = "exists( protobuf_unittest.ForeignEnum ) " )
	
}


