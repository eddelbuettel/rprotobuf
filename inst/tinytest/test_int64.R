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

#test.int64 <- function() {
## Preserve option.
old.optval <- options("RProtoBuf.int64AsString")
on.exit(options(old.optval))

if (!exists("protobuf_unittest.TestAllTypes",
            "RProtoBuf:DescriptorPool")) {
    unittest.proto.file <- system.file("tinytest", "data", "unittest.proto",
                                       package="RProtoBuf")
    readProtoFiles(file=unittest.proto.file)
}

if (.Machine$sizeof.longlong < 8) {
    exit_file("Can't test 64-bit int type on platform with sizeof(long long) < 8")
}
if (is.na(Rcpp:::capabilities()["long long"]) || Rcpp:::capabilities()["long long"] != TRUE) {
    exit_file("Can't test 64-bit int type without RCPP_LONG_LONG support.")
}

a <- new(protobuf_unittest.TestAllTypes)
a$repeated_int64 <- 1
# Now just test that we can use add to set int64 fields.
a$add("repeated_int64", 2:10)
expect_equal(length(a$repeated_int64), 10)

# Verify we can set character strings of large 64-bit ints
a$repeated_int64 <- c("9007199254740992", "9007199254740993")
expect_equal(length(a$repeated_int64), 2)

# Verify we can't set any garbage string to a repeated int64.
expect_error(a$repeated_int64 <-c("invalid", "invalid"))

a$optional_int64 <- 1
a$optional_int64 <- "2"
expect_equal(a$optional_int64, 2)
# Verify we can't set any garbage string to an optional int64.
expect_error(a$optional_int64 <- "invalid")

a <- protobuf_unittest.TestAllTypes$readASCII(file(system.file("tinytest", "data", "int64.ascii",
                                                               package="RProtoBuf")))
# And can read them in OK from an ASCII file.
expect_equal(length(a$repeated_int64), 2)

# By default, when they are read as numerics, only 1 unique value
expect_equal(length(unique(a$repeated_int64)), 1)

options("RProtoBuf.int64AsString" = TRUE)
# But we can see they are different if we treat them as strings.
expect_equal(length(unique(a$repeated_int64)), 2)
#}
