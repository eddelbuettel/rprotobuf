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

test.uint32 <- function() {
    if (!exists("protobuf_unittest.TestAllTypes",
                "RProtoBuf:DescriptorPool")) {
        unittest.proto.file <- system.file("unitTests", "data",
                                           "unittest.proto",
                                           package="RProtoBuf")
        readProtoFiles(file=unittest.proto.file)
    }

    foo <- new(protobuf_unittest.TestAllTypes)
    foo$optional_uint32 <- 2^32 - 1
    foo$repeated_uint32 <- c(foo$optional_uint32, foo$optional_uint32)
    checkEquals(as.character(foo$optional_uint32),
                "4294967295")
    checkEquals(foo$optional_uint32,
                foo$repeated_uint32[[1]])
    foo$add("repeated_uint32", c(2^32 - 1, 2^32 - 1))
    checkEquals(length(unique(foo$repeated_uint32)), 1)
    
    # fixed32 are a more efficient representation of uint32
    foo$optional_fixed32 <- 2^32 - 1
    foo$repeated_fixed32 <- c(foo$optional_fixed32, foo$optional_fixed32)
    checkEquals(as.character(foo$optional_fixed32),
                "4294967295")
    checkEquals(foo$optional_fixed32,
                foo$repeated_fixed32[[1]])
}
