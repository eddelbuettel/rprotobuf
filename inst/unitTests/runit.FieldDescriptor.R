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

# this is executed before each test function
.setUp <- function(){
    if( !exists("tutorial.Person", "RProtoBuf:DescriptorPool")) {
        protofile <- system.file("proto", "addressbook.proto", package = "RProtoBuf" )
        readProtoFiles(file = protofile)
    }
}
        

test.FieldDescriptor.class <- function() {

    Person <- P( "tutorial.Person") 

    ## field descriptor object
    checkTrue(!is.null(Person$email), msg="non-null email")

    ## debug string
    checkTrue(nchar(as.character( Person$email )) > 1, msg="non-empty email")

    ## default values
    checkTrue(!has_default_value(Person$id), msg="no default for id")
    checkTrue(has_default_value(Person$PhoneNumber$type), msg="default for phone")
    checkEquals(default_value(Person$PhoneNumber$type), 1, msg="check default for phone type")
    checkEquals(default_value(Person$id), 0, msg="check default for person id")

    ## Get the types of field descriptors
    checkEquals(type(Person$id), TYPE_INT32, msg="type int32")
    checkEquals(type(Person$id, TRUE), "TYPE_INT32", msg="type int32 as char")
    checkEquals(cpp_type(Person$email), CPPTYPE_STRING, msg="cpptype string")
    checkEquals(cpp_type(Person$email, TRUE), "CPPTYPE_STRING", msg="cpptype string as char")

    ## Get the label of a field descriptor
    checkEquals(label(Person$id), LABEL_REQUIRED, msg="label required")
    checkEquals(label(Person$id, TRUE), "LABEL_REQUIRED", msg="label required as char")
    checkEquals(label(Person$email), LABEL_OPTIONAL, msg="label optional")
    checkEquals(label(Person$email, TRUE), "LABEL_OPTIONAL", msg="label optional as char")

    ## Test if a field is optional
    checkTrue(is_required(Person$id), msg="id is required")
    checkTrue(!is_optional(Person$id), msg="id is not optional")
    checkTrue(!is_repeated(Person$id), msg="id is not repeated")

    checkTrue(!is_required(Person$email), msg="email is not required")
    checkTrue(is_optional(Person$email), msg="email is optional")
    checkTrue(!is_repeated(Person$email), msg="email is not repeated")

    ## Return the class of a message field
    checkTrue(inherits(message_type(Person$phone), "Descriptor"), msg="inherits Descriptor")

    ## Containing type of a field is the message descriptor
    checkTrue(inherits(Person$id$containing_type(), "Descriptor"),
              msg="inherits containing type Descriptor")

    ## No containing type for the top-level message descriptor.
    checkTrue(is.null(Person$containing_type()), msg="no containing typw")

}
