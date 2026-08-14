# Copyright 2026 Troy Hernandez
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

readProtoFiles2("helloworld.proto",
                protoPath = system.file("proto", package = "RProtoBuf"))

fd <- fileDescriptor(P("rprotobuf.HelloWorldRequest"))
svc <- fd$HelloWorldService
expect_true(inherits(svc, "ServiceDescriptor"))

# method_count and length (issue #116: the .Call target was misnamed)
expect_equal(method_count(svc), 1L)
expect_equal(length(svc), 1L)

# method by index, 1-based as elsewhere (issue #116: routine compiled
# but unregistered)
m <- method(svc, index = 1L)
expect_true(inherits(m, "MethodDescriptor"))
expect_equal(name(m), "HelloWorld")

# method by name
m2 <- method(svc, name = "HelloWorld")
expect_true(inherits(m2, "MethodDescriptor"))
expect_equal(name(m2, full = TRUE), "rprotobuf.HelloWorldService.HelloWorld")

# downstream MethodDescriptor accessors work from either path
expect_equal(name(input_type(m)), "HelloWorldRequest")
expect_equal(name(output_type(m)), "HelloWorldResponse")

# out of range / unknown name give NULL, as the EnumDescriptor
# accessors do
expect_null(method(svc, index = 2L))
expect_null(method(svc, index = 0L))
expect_null(method(svc, name = "NoSuchMethod"))

# exactly one of index or name
expect_error(method(svc))
expect_error(method(svc, index = 1L, name = "HelloWorld"))
