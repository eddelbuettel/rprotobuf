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

library(RProtoBuf)

#test.message <- function() {
if (!exists("protobuf_unittest.TestAllTypes",
            "RProtoBuf:DescriptorPool")) {
    unittest.proto.file <- system.file("tinytest", "data", "unittest.proto",
                                       package="RProtoBuf")
    readProtoFiles(file=unittest.proto.file)
}
a <- new(protobuf_unittest.TestAllTypes)
a$optionalgroup$a <- 3
expect_equal(a$optionalgroup$a, 3)

a$repeated_nested_message <- list(
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=3),
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=4))
expect_equal(a$repeated_nested_message[[1]]$bb, 3)
expect_equal(a$repeated_nested_message[[2]]$bb, 4)

expect_error(a$repeated_nested_message <- list(
    new(protobuf_unittest.ForeignMessage, c=1),
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=4)))

expect_error(a$repeated_nested_message <- list(
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=4),
    new(protobuf_unittest.ForeignMessage, c=1)))

expect_error(a$repeated_nested_message <- list(
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=4),
    3))

expect_error(a$repeated_nested_message <- list(
    new(protobuf_unittest.TestAllTypes.NestedMessage, bb=4),
    "foo"))
#}
