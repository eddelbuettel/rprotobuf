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
	if (!inherits(field, "FieldDescriptor")) {
		stop("setExtension requires a FieldDescriptor")
	}
	if (!is_extension(field)) {
		stop(paste(name(field), "is not an extension FieldDescriptor."))
	}
	.Call( "setMessageField", object@pointer, field, values,
	      PACKAGE = "RProtoBuf" )
	invisible( object )
} )


setGeneric( "getExtension", function(object, field){
	standardGeneric( "getExtension" )
} )
setMethod( "getExtension", "Message", function( object, field){
	if (!inherits(field, "FieldDescriptor")) {
		stop("getExtension requires a FieldDescriptor")
	}
	if (!is_extension(field)) {
		stop(paste(name(field), "is not an extension FieldDescriptor."))
	}
	# This check causes a CHECK failure in the C++ code, so give
	# a more user-friendly error here.
	if (containing_type(field)@type != object@type) {
		stop(paste("Field", name(field),
			   "does not match message type (",
			   containing_type(field)@type, "!=",
			   object@type, ")"))
	}
        .Call( "getExtension", object@pointer, field,
              PACKAGE = "RProtoBuf" )
} )
