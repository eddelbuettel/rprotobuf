# Copyright 2012 Google Inc. All Rights Reserved.
# Author: mstokely@google.com (Murray Stokely)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

setGeneric( "setExtension", function(object, field, values){
        standardGeneric( "setExtension" )
} )

setMethod( "setExtension", "Message", function( object, field, values ){
	stopifnot(is_extension(field))

        .Call( "setMessageField", object@pointer, field, values,
              PACKAGE = "RProtoBuf" )
	invisible( object )
} )


setGeneric( "getExtension", function(object, field){
	standardGeneric( "getExtension" )
} )
setMethod( "getExtension", "Message", function( object, field){
        .Call( "getExtension", object@pointer, field,
              PACKAGE = "RProtoBuf" )
} )
