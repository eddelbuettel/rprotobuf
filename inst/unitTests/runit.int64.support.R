# Copyright 2011 Google Inc.
# Copyright 2011 Dirk Eddelbuettel and Romain Francois 
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

.setUp <- function(){
    if( ! exists( "TestInt64", "RProtoBuf:DescriptorPool" ) ){
        unitest.proto.file <- system.file( "unitTests", "data", "int64.proto", package = "RProtoBuf" )
        readProtoFiles(file = unitest.proto.file)
    }
}

test.int64 <- function() {
  msg <- new( TestInt64, a = 1, b = 2, c = seq(1,4,by=1), d = seq(1,4,by=1) )
  checkEquals( msg$a, as.int64(1) )
  checkEquals( msg$b, as.uint64(2) )
  checkEquals( msg$c, as.int64(1:4) )
  checkEquals( msg$d, as.uint64(1:4) )
  msg$a <- 11
  msg$b <- 12
  msg$c <- seq(1,15, by = 1 )
  msg$d <- seq(1,15, by = 1 )
  checkEquals( msg$a, as.int64(11) )
  checkEquals( msg$b, as.uint64(12) )
  checkEquals( msg$c, as.int64(1:15) )
  checkEquals( msg$d, as.uint64(1:15) )
  
  msg <- new( TestInt64, a = 1L, b = 2L, c = 1:4, d = 1:4 )
  checkEquals( msg$a, as.int64(1) )
  checkEquals( msg$b, as.uint64(2) )
  checkEquals( msg$c, as.int64(1:4) )
  checkEquals( msg$d, as.uint64(1:4) )
  msg$a <- 11L
  msg$b <- 12L
  msg$c <- 1:15
  msg$d <- 1:15
  checkEquals( msg$a, as.int64(11) )
  checkEquals( msg$b, as.uint64(12) )
  checkEquals( msg$c, as.int64(1:15) )
  checkEquals( msg$d, as.uint64(1:15) )
  
  msg <- new( TestInt64, a = as.int64(1), b = as.int64(2), c = as.int64(1:4), d = as.int64(1:4) )
  checkEquals( msg$a, as.int64(1) )
  checkEquals( msg$b, as.uint64(2) )
  checkEquals( msg$c, as.int64(1:4) )
  checkEquals( msg$d, as.uint64(1:4) )
  msg$a <- as.int64(11)
  msg$b <- as.uint64(12)
  msg$c <- as.int64( 1:15 )
  msg$d <- as.uint64( 1:15 )
  checkEquals( msg$a, as.int64(11) )
  checkEquals( msg$b, as.uint64(12) )
  checkEquals( msg$c, as.int64(1:15) )
  checkEquals( msg$d, as.uint64(1:15) )
  
}
