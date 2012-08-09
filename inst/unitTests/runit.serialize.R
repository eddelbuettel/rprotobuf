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
.setUp <- function(){
	if( !exists("tutorial.Person", "RProtoBuf:DescriptorPool") ) {
		unitest.proto.file <- system.file("proto", "addressbook.proto",
                                                  package = "RProtoBuf" )
		readProtoFiles(file = unitest.proto.file)
	}
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
