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

test.int32 <- function() {
    if (!exists("protobuf_unittest.TestAllTypes",
                "RProtoBuf:DescriptorPool")) {
        unittest.proto.file <- system.file("unitTests", "data",
                                           "unittest.proto",
                                           package="RProtoBuf")
        readProtoFiles(file=unittest.proto.file)
    }

    a <- new(protobuf_unittest.TestAllTypes)
    a$repeated_int32 <- 1
    # Verify we can set character strings
    a$repeated_int32 <- c("9007", "9008")
    checkEquals(length(a$repeated_int32), 2)
    # Verify we can't set any garbage string to a repeated int32.
    checkException(a$repeated_int32 <-c("invalid", "invalid"))
    checkException(a$repeated_int32 <-c("33-"))

    a$optional_int32 <- 1
    a$optional_int32 <- "2"
    checkEquals(a$optional_int32, 2)
    # Verify we can't set any garbage string to an optional int32.
    checkException(a$optional_int32 <- "invalid")

    a$optional_uint32 <- 10000
    a$optional_uint32 <- "200000"
    checkEquals(a$optional_uint32, 200000)
    # Verify we can't set any garbage string to an optional uint32.
    checkException(a$optional_uint32 <- "invalid")

    a$repeated_uint32 <- c("9007", "9008")
    checkEquals(length(a$repeated_uint32), 2)
}
