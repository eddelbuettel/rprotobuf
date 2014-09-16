# Copyright 2011 Google Inc.
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

test.enums <- function() {
  ProtoFormat <- P("tutorial.Person")

  # value(..) returns an EnumValueDescriptor object

  checkEquals(name(value(ProtoFormat$PhoneType, index=1)), "MOBILE")
  checkEquals(name(value(ProtoFormat$PhoneType, index=1), TRUE),
              "tutorial.Person.MOBILE")
  checkEquals(number(value(ProtoFormat$PhoneType, index=1)), 0)
  checkTrue(inherits(enum_type(value(ProtoFormat$PhoneType, index=1)),
                     "EnumDescriptor"))
  checkTrue(inherits(asMessage(value(ProtoFormat$PhoneType, index=1)),
                     "Message"))
  
  # Now check the '$' interfaces
  checkEquals(name(value(ProtoFormat$PhoneType, index=1)),
              value(ProtoFormat$PhoneType, index=1)$name())
  checkEquals(number(value(ProtoFormat$PhoneType, index=1)),
              value(ProtoFormat$PhoneType, index=1)$number())
  
  checkEquals(name(value(ProtoFormat$PhoneType, index=2)), "HOME")


  checkEquals(length(ProtoFormat$PhoneType), 3)
  checkTrue(has(ProtoFormat$PhoneType, "WORK"))
  checkTrue(!has(ProtoFormat$PhoneType, "NONEXISTANT"))

  # Verify we can subset the EnumDescriptor class
  checkEquals(ProtoFormat$PhoneType[["WORK"]], 2)
  checkEquals(ProtoFormat$PhoneType[["MOBILE"]], 0)

  # Verify that invalid indices are returned as NULL.
  checkTrue(is.null(value(ProtoFormat$PhoneType, index=900)))

  # Verify that we import top-level enums from .proto files.
  if (!exists("protobuf_unittest.TestAllTypes",
              "RProtoBuf:DescriptorPool")) {
    unittest.proto.file <- system.file("unitTests", "data",
                                       "unittest.proto",
                                       package="RProtoBuf")
    readProtoFiles(file=unittest.proto.file)
  }
  checkTrue(inherits(P("protobuf_unittest.ForeignEnum"), "EnumDescriptor"))
}
