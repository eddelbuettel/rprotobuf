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

library(RProtoBuf)

#.setUp <- function() {
    resetDescriptorPool()
#}

#test.import.reset <- function() {
## Verify that the common setup is resetting the descriptor pool.
## Only the messages defined in the proto directory should be present.
expect_true(all(grepl("^(rexp|tutorial|rprotobuf)\\.", objects("RProtoBuf:DescriptorPool"))))
#}

#test.import.error <- function() {
## Verify that we get a graceful error rather than a segfault.
expect_error(readProtoFiles(system.file("DESCRIPTION", package="RProtoBuf"), syntax="proto3"))
#}

#test.import <- function() {
#unit.test.data.dir <- system.file("unitTests", "data", package="RProtoBuf")
unit.test.data.dir <- file.path("data", "cyclical")
expect_true(!exists("protobuf_unittest_import.ImportMessage", "RProtoBuf:DescriptorPool"))

resetDescriptorPool()
readProtoFiles2(recursive = FALSE, protoPath=unit.test.data.dir)
#expect_true(exists("protobuf_unittest_import.ImportMessage", "RProtoBuf:DescriptorPool"))
# The following is imported by unittest.proto and hence, should have been imported implicitly.
#expect_true(exists("protobuf_unittest_subdir.SubdirMessage", "RProtoBuf:DescriptorPool"))
# The following is not imported by any of the top level files.
expect_true(!exists("protobuf_unittest_recursive_subdir.SubdirMessage", "RProtoBuf:DescriptorPool"))


#test.import.subdir <- function() {
unit.test.data.dir <- system.file("tinytest", "data", package="RProtoBuf")

# Any of these two will work.
readProtoFiles2(file="subdir/subdir_message.proto", protoPath=unit.test.data.dir)
readProtoFiles2(dir="subdir", protoPath=unit.test.data.dir)
expect_true(exists("protobuf_unittest_subdir.SubdirMessage", "RProtoBuf:DescriptorPool"))

readProtoFiles2(dir="recursive", recursive=TRUE, protoPath=unit.test.data.dir)
expect_true(exists("protobuf_unittest_recursive_subdir.SubdirMessage", "RProtoBuf:DescriptorPool"))
#}

#test.import.cyclical <- function() {
unit.test.cyclical.dir <- system.file("tinytest", "data", "cyclical", package="RProtoBuf")
proj1.dir <- file.path(unit.test.cyclical.dir, "proj1")
proj2.dir <- file.path(unit.test.cyclical.dir, "proj2")

# The following files should be loaded in order as C depends on B depends on A.

readProtoFiles2(file="proto/a.proto", protoPath=proj1.dir)
expect_true(exists("A", "RProtoBuf:DescriptorPool"))
expect_true(!exists("C", "RProtoBuf:DescriptorPool"))

readProtoFiles2(file="proto/b.proto", protoPath=proj2.dir)
expect_true(exists("B", "RProtoBuf:DescriptorPool"))

readProtoFiles2(file="proto/c.proto", protoPath=proj1.dir)
expect_true(exists("C", "RProtoBuf:DescriptorPool"))
#}

#test.assign.in.global <- function() {
xx.undef <<- 3
expect_equal(xx.undef, 3)
#}
