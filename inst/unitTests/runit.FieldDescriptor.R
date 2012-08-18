# Copyright 2012 Google Inc.
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

test.FieldDescriptor.class <- function() {
  proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )
  Person <- P( "tutorial.Person", file = proto.file )

  # field descriptor object
  checkTrue(!is.null(Person$email))

  # debug string
  checkTrue(nchar(as.character( Person$email )) > 1)

  # default values
  checkTrue(!has_default_value(Person$id))
  checkTrue(has_default_value(Person$PhoneNumber$type))

  checkEquals(default_value(Person$PhoneNumber$type), 1)
  checkEquals(default_value(Person$id), 0)

  # Get the types of field descriptors
  checkEquals(type(Person$id), TYPE_INT32)
  checkEquals(type(Person$id, TRUE), "TYPE_INT32")
  checkEquals(cpp_type(Person$email), CPPTYPE_STRING)
  checkEquals(cpp_type(Person$email, TRUE), "CPPTYPE_STRING")

  # Get the label of a field descriptor
  checkEquals(label(Person$id), LABEL_REQUIRED)
  checkEquals(label(Person$id, TRUE), "LABEL_REQUIRED")
  checkEquals(label(Person$email), LABEL_OPTIONAL)
  checkEquals(label(Person$email, TRUE), "LABEL_OPTIONAL")

  # Test if a field is optional
  checkTrue(is_required(Person$id))
  checkTrue(!is_optional(Person$id))
  checkTrue(!is_repeated(Person$id))

  checkTrue(!is_required(Person$email))
  checkTrue(is_optional(Person$email))
  checkTrue(!is_repeated(Person$email))

  # Return the class of a message field
  checkTrue(inherits(message_type(Person$phone), "Descriptor"))
}
