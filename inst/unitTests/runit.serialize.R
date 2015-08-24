# -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
# Copyright 2012 Google Inc. All Rights Reserved.
# Author: Murray Stokely
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

# this is executed before each test function
.setUp <- function() {
	if (!exists("tutorial.Person", "RProtoBuf:DescriptorPool")) {
		protofile <- system.file("proto", "addressbook.proto", package = "RProtoBuf")
		readProtoFiles(file = protofile)
	}
}

test.arrayinputstream <- function() {
    # Note: This class is experimental, and some parts of the design
    # may need to change, but this works now.
    stream <- ArrayInputStream(as.raw(0:10))
    checkEquals(stream$ReadRaw(5), as.raw(0:4))

    stringstream <- ArrayInputStream(as.raw(c(0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67)))
    checkEquals(stringstream$ReadString(as.integer(7)), "testing")

    intstream <- ArrayInputStream(as.raw(c(0x9e, 0xa7, 0x05)))
    checkEquals(intstream$ReadVarint32(), 86942)
}

test.encoding <- function() {
        if (!exists("protobuf_encoding_test.Test1",
                    "RProtoBuf:DescriptorPool")) {
          unittest.proto.file <- system.file("unitTests", "data",
                                             "encoding.proto",
                                             package="RProtoBuf")
          readProtoFiles(file=unittest.proto.file)
        }

        # Encoding examples from:
        # https://developers.google.com/protocol-buffers/docs/encoding
        test1 <- new(protobuf_encoding_test.Test1)
        test1$a <- 150
        checkIdentical(test1$serialize(NULL), as.raw(c(0x08,0x96,0x01)))

        test2 <- new(protobuf_encoding_test.Test2)
        test2$b <- "testing"
        checkIdentical(test2$serialize(NULL),
                       as.raw(c(0x12, 0x07, 0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67)))

        test3 <- new(protobuf_encoding_test.Test3)
        test3$c$a <- 150
        checkIdentical(test3$serialize(NULL),
                       as.raw(c(0x1a, 0x03, 0x08, 0x96, 0x01)))

        test4 <- new(protobuf_encoding_test.Test4)
        test4$d <- c(3, 270, 86942)
        checkIdentical(test4$serialize(NULL),
                       as.raw(c(0x22, 0x06, 0x03, 0x8e, 0x02, 0x9e, 0xa7, 0x05)))
}

test.serialize <- function() {
        person <- new(tutorial.Person)

        checkTrue(!person$isInitialized())
        checkException(serialize(person, NULL),
                "Uninitialized object should fail to serialize.")
        person$id <- 1
        checkException(serialize(person, NULL),
                "Uninitialized object should fail to serialize.")
        person$name <- "Murray"

        checkTrue(person$isInitialized())
        checkTrue(length(serialize(person, NULL)) > 1)
}
