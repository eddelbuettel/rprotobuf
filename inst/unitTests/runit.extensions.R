# Copyright 2013 Google Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

test.extension <- function() {
    if (!exists("protobuf_unittest.TestAllTypes",
                "RProtoBuf:DescriptorPool")) {
        unittest.proto.file <- system.file("unitTests", "data",
                                           "unittest.proto",
                                           package="RProtoBuf")
        readProtoFiles(file=unittest.proto.file)
    }

    checkTrue(inherits(protobuf_unittest.optional_uint32_extension,
                       "FieldDescriptor"))

    # Verify we can pull in other extensions with P()
    checkTrue(inherits(P("protobuf_unittest.optional_uint32_extension"),
                       "FieldDescriptor"))

    ## Test setting and getting singular extensions.
    test <- new(protobuf_unittest.TestAllExtensions)
    test$setExtension(protobuf_unittest.optional_int32_extension,
                      as.integer(1))
    checkEquals(test$getExtension(protobuf_unittest.optional_int32_extension),
                as.integer(1))
    ## Unset extensions should return NULL.
    checkEquals(test$getExtension(protobuf_unittest.optional_double_extension),
                NULL)


    ## Test setting and getting repeated extensions.
    checkEquals(test$getExtension(protobuf_unittest.repeated_int32_extension),
                NULL)
    test$setExtension(protobuf_unittest.repeated_int32_extension, 1:10)
    checkEquals(test$getExtension(protobuf_unittest.repeated_int32_extension),
                1:10)

    ## Test nested extensions.
    checkEquals(test$getExtension(protobuf_unittest.TestNestedExtension.test),
                NULL)
    test$setExtension(protobuf_unittest.TestNestedExtension.test, "foo")
    checkEquals(test$getExtension(protobuf_unittest.TestNestedExtension.test),
                                  "foo")

    ## Test setting and getting enums.
    test$setExtension(protobuf_unittest.optional_nested_enum_extension,
                      protobuf_unittest.TestAllTypes.NestedEnum$BAR)

    ## Test foreign message extensions
    foo <- new(protobuf_unittest.ForeignMessage)
    foo$c <- 3
    test$setExtension(protobuf_unittest.optional_foreign_message_extension,
		      foo)
    checkEquals(test$getExtension(protobuf_unittest.optional_foreign_message_extension)$c,
		3)

    # This causes an Rcpp exception, but not an R stop error as of my
    # version of Rcpp, so we can't checkError unfortunately, but we
    # can at least make sure it doesn't crash R.
    # TODO(edd): Commented out now
    # test$setExtension(protobuf_unittest.optional_nested_enum_extension, 9)

    ## Test nested message extensions.
    tmp <- new( protobuf_unittest.TestAllTypes.NestedMessage )
    tmp$bb <- 3
    test$setExtension(protobuf_unittest.optional_nested_message_extension, tmp)
    checkEquals(test$getExtension(protobuf_unittest.optional_nested_message_extension)$bb, 3)

    ## Check that we do something sensible if invalid field descriptors are passed
    checkException(test$getExtension(protobuf_unittest.TestAllExtensions))
    checkException(test$setExtension(protobuf_unittest.TestAllExtensions, 3))

    ## Check that we don't CHECK fail in C++, but instead give a reasonable
    ## error message if incorrect extensions types are provided.
    checkException(test$getExtension(protobuf_unittest.my_extension_string))
}
