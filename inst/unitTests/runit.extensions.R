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

}
