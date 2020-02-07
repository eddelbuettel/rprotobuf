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

library(RProtoBuf)

# this is executed before each test function
#.setUp <- function(){
if( !exists("tutorial.Person", "RProtoBuf:DescriptorPool")) {
    protofile <- system.file("proto", "addressbook.proto", package = "RProtoBuf" )
    readProtoFiles(file = protofile)
}
#}


#test.FieldDescriptor.class <- function() {

Person <- P( "tutorial.Person")

## field descriptor object
expect_true(!is.null(Person$email), info="non-null email")

## debug string
expect_true(nchar(as.character( Person$email )) > 1, info="non-empty email")

## default values
expect_true(!has_default_value(Person$id), info="no default for id")
expect_true(has_default_value(Person$PhoneNumber$type), info="default for phone")
expect_equal(default_value(Person$PhoneNumber$type), 1, info="check default for phone type")
expect_equal(default_value(Person$id), 0, info="check default for person id")

## Get the types of field descriptors
expect_equal(type(Person$id), TYPE_INT32, info="type int32")
expect_equal(type(Person$id, TRUE), "TYPE_INT32", info="type int32 as char")
expect_equal(cpp_type(Person$email), CPPTYPE_STRING, info="cpptype string")
expect_equal(cpp_type(Person$email, TRUE), "CPPTYPE_STRING", info="cpptype string as char")

## Get the label of a field descriptor
expect_equal(label(Person$id), LABEL_REQUIRED, info="label required")
expect_equal(label(Person$id, TRUE), "LABEL_REQUIRED", info="label required as char")
expect_equal(label(Person$email), LABEL_OPTIONAL, info="label optional")
expect_equal(label(Person$email, TRUE), "LABEL_OPTIONAL", info="label optional as char")

## Test if a field is optional
expect_true(is_required(Person$id), info="id is required")
expect_true(!is_optional(Person$id), info="id is not optional")
expect_true(!is_repeated(Person$id), info="id is not repeated")

expect_true(!is_required(Person$email), info="email is not required")
expect_true(is_optional(Person$email), info="email is optional")
expect_true(!is_repeated(Person$email), info="email is not repeated")

## Return the class of a message field
expect_true(inherits(message_type(Person$phone), "Descriptor"), info="inherits Descriptor")

## Containing type of a field is the message descriptor
expect_true(inherits(Person$id$containing_type(), "Descriptor"),
            info="inherits containing type Descriptor")

## No containing type for the top-level message descriptor.
expect_true(is.null(Person$containing_type()), info="no containing typw")

#}
