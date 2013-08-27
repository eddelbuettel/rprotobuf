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

test.int64 <- function() {
    if (!exists("protobuf_unittest.TestAllTypes",
                "RProtoBuf:DescriptorPool")) {
        unittest.proto.file <- system.file("unitTests", "data",
                                           "unittest.proto",
                                           package="RProtoBuf")
        readProtoFiles(file=unittest.proto.file)
    }

    a <- new(protobuf_unittest.TestAllTypes)
    a$repeated_int64 <- 1
    # Verify we can set character strings of large 64-bit ints
    a$repeated_int64 <- c("9007199254740992", "9007199254740993")
    checkEquals(length(a$repeated_int64), 2)
    # Verify we can set any garbage string to an int64.
    checkException(a$repeated_int64 <-c("invalid", "invalid"))

    a <- protobuf_unittest.TestAllTypes$readASCII(
           file(system.file("unitTests", "data", "int64.ascii",
                            package="RProtoBuf")))
    # And can read them in OK from an ASCII file.
    checkEquals(length(a$repeated_int64), 2)

    # TODO(mstokely): But the accessors still silently cast to double
    # which removes uniqueness.  Fix this.
    # Uncomment when RProtoBuf / Rcpp are unbroken with respect to 64-bit ints.
    # checkEquals(length(unique(a$repeated_int64)), 2)
}
