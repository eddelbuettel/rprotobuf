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

test.bool <- function() {
    if (!exists("protobuf_unittest.TestAllTypes",
                "RProtoBuf:DescriptorPool")) {
        unittest.proto.file <- system.file("unitTests", "data",
                                           "unittest.proto",
                                           package="RProtoBuf")
        readProtoFiles(file=unittest.proto.file)
    }
 
    a <- new(protobuf_unittest.TestAllTypes)
    a$optional_bool <- TRUE
    a$optional_bool <- FALSE
    # Verify we can not set a protocol buffer bool to NA.
    checkException(a$optional_bool <- NA)
    
    # Verify we can set character strings
    a$repeated_bool <- c(TRUE, FALSE, TRUE)
    checkEquals(length(unique(a$repeated_bool)), 2)

    # Verify we can't set any garbage string to a bool.
    checkException(a$optional_bool <- "100")
    checkException(a$optional_bool <- "invalid")

    # Verify we can't set any garbage string to a repeated bool.
    checkException(a$repeated_bool <-c("invalid", "invalid"))
    checkException(a$repeated_bool <-c("33-"))

    # Verify we can set NA
    checkException(a$repeated_bool <- c(TRUE, FALSE, TRUE, NA))
}
