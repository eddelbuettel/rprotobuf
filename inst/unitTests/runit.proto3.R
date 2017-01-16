## rprotobuf.h: R/C++ interface class library
##
## Copyright (C) 2017 -       Dirk Eddelbuettel
##
## This file is part of RProtoBuf.
##
## RProtoBuf is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## RProtoBuf is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.


## The Travis CI tests use both proto2 and proto3, so we need to condition against
## running this one with proto2 where it cannot pass we impose a proto3 file
isNotProto2Test <- Sys.getenv("PROTOBUF") != "v2"    

if (isNotProto2Test) {

    .setUp <- function(){
        if( !exists("SearchRequest", "RProtoBuf:DescriptorPool")) {
            unitest.proto.file <- system.file("unitTests", "data", "proto3.proto", package="RProtoBuf")
            readProtoFiles(file = unitest.proto.file)
        }
    }
    
    test.proto3 <- function() {
        q <- new(SearchRequest, query="abc", page_number=42L, result_per_page=77L)
        checkEquals(q$query, "abc", msg="proto3 string")
        checkEquals(q$page_number, 42L, msg="proto3 int")
        checkEquals(q$result_per_page, 77L, msg="proto3 int again")
    }
}
