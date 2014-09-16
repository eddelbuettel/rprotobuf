# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

# this has to be
IMPLEMENTATIONS <- new.env( parent = emptyenv() )

# invisible version of .Call
.icall <- function(...) invisible(.Call(...))

# {{{ class definitions
# we need to formalize connection so that the S4 methods
# ConnectionInputStream and ConnectionOutputStream can
# dispatch connections
setOldClass( "connection" )

# FIXME: there is probably another way
# TODO: include other subclasses of connections
setOldClass( c("file", "connection" ) )
setOldClass( c("url", "connection" ) )

setClass( "Descriptor", representation(
	pointer = "externalptr",   # pointer to a google::protobuf::Descriptor c++ object
	type = "character"         # message type
), prototype = list( pointer = NULL, type = character(0) ) )

setClass( "FieldDescriptor", representation(
	pointer = "externalptr" ,   # pointer to a google::protobuf::FieldDescriptor c++ object
	name    = "character",
	full_name  = "character",
	type    = "character"
), prototype = list( pointer = NULL, name = character(0),
	full_name = character(0), type = character(0) ) )

setClass( "EnumDescriptor", representation(
	pointer = "externalptr" ,  # pointer to a google::protobuf::EnumDescriptor c++ object
	name    = "character",
	full_name  = "character",
	type    = "character"   # TODO(mstokely): enums don't really have another type, remove?
), prototype = list( pointer = NULL, name = character(0),
	full_name = character(0), type = character(0) ) )

setClass( "ServiceDescriptor", representation(
	pointer = "externalptr",   # pointer to a google::protobuf::ServiceDescriptor c++ object
	name = "character"         # full name of the service
), prototype = list( pointer = NULL, name = character(0) ) )

setClass( "MethodDescriptor", representation(
	pointer = "externalptr",   # pointer to a google::protobuf::ServiceDescriptor c++ object
	name = "character"     ,   # full name of the service
	service = "character"      # full name of the service that defines this method
), prototype = list( pointer = NULL, name = character(0), service = character(0) ) )

setClass( "FileDescriptor", representation(
	pointer = "externalptr",  # pointer to a google::protobuf::FileDescriptor c++ object
	filename = "character",	  # filename
	package = "character"     # the package
), prototype = list( pointer = NULL, filename = character(0), package = character(0) ) )

setClass( "EnumValueDescriptor", representation(
	pointer = "externalptr",  # pointer to a google::protobuf::EnumValueDescriptor c++ object
	name    = "character",
	full_name  = "character"
), prototype = list( pointer = NULL, name = character(0), full_name = character(0) ) )

# actual objects

setClass( "Message",  representation(
   pointer = "externalptr",    # pointer to sa google::protobuf::Message object
   type    = "character"       # message type (fully qualified, with package path)
), prototype = list( pointer = NULL, type = character(0) ) )

# rpc

setClass( "RpcHTTP", representation( 
	host = "character", port = "integer", root = "character" 
), prototype = list( host = "127.0.0.1", port = 4444L, root = "" ) )

# streams
setClass( "ZeroCopyInputStream", representation(
	pointer = "externalptr"
), prototype = list( pointer = NULL ), contains = "VIRTUAL" )
setClass( "ArrayInputStream", contains = "ZeroCopyInputStream" )
setClass( "FileInputStream", contains = "ZeroCopyInputStream" )
setClass( "ConnectionInputStream", contains = "ZeroCopyInputStream" )

setClass( "ZeroCopyOutputStream", representation(
	pointer = "externalptr"
), prototype = list( pointer = NULL ), contains = "VIRTUAL" )
setClass( "ArrayOutputStream", contains = "ZeroCopyInputStream" )
setClass( "FileOutputStream", contains = "ZeroCopyInputStream" )
setClass( "ConnectionOutputStream", contains = "ZeroCopyOutputStream" )
# }}}

# {{{ new
newProto <- function( descriptor, ... ){
	message <- .Call( "newProtoMessage", descriptor, PACKAGE = "RProtoBuf" )
	update( message, ... )
	message
}
setGeneric("new")
setMethod("new", signature(Class="Descriptor"), function(Class, ...) newProto(Class, ...))
# }}}

# {{{ P
P <- function( type, file ){

	if( !missing(file) ){
		readProtoFiles( file )
	}
	if( missing( type ) ){
		stop( "'type' is required" )
	}
	if( !is.character(type) ){
		stop( "'type' is not a character vector" )
	}
	if( length(type) != 1L){
		stop( "'type' should have exactly one element" )
	}

	desc <- .Call( "getProtobufDescriptor", type,
		PACKAGE = "RProtoBuf" )
	if( is.null( desc ) ){
		# See if it is an extension
		desc <- .Call("getExtensionDescriptor", type, PACKAGE="RProtoBuf")
		if (is.null(desc)) {
			# See if it is an enum
			desc <- .Call("getEnumDescriptor", type, PACKAGE="RProtoBuf")
			if (is.null(desc)) {
				stop( sprintf( "could not find descriptor for message type '%s' ", type ) )
			}
		}
	}
	desc
}
# }}}

# {{{ show
setMethod( "show", c( "Message" ), function(object){
  tmp <- sprintf( "message of type '%s' with %d field%s set", object@type,
                 length(object), if (length(object) == 1) "" else "s" )
  nexts <- .Call("Message__num_extensions", object@pointer, PACKAGE="RProtoBuf")
  if (nexts > 0) {
    tmp <- paste(tmp, sprintf("and %d extension%s", nexts, if (nexts == 1) "" else "s"))
  }
  cat(tmp, fill=TRUE)
} )
setMethod( "show", c( "Descriptor" ), function(object){
	cat( sprintf( "descriptor for type '%s' ", object@type ) , fill=TRUE)
} )
setMethod( "show", c( "FieldDescriptor" ), function(object){
	cat( sprintf( "descriptor for field '%s' of type '%s' ",
                     object@name, object@type ), fill=TRUE)
} )
setMethod( "show", c( "EnumDescriptor" ), function(object){
	cat( sprintf( "descriptor for enum '%s' with %d values", object@name,
                      value_count(object) ) , fill=TRUE)
} )
setMethod( "show", c( "ServiceDescriptor" ), function(object){
	cat( sprintf( "service descriptor <%s>", object@name ) , fill=TRUE)
} )
setMethod( "show", c( "FileDescriptor" ), function(object){
	cat( sprintf( "file descriptor for package %s (%s)", object@package,
                      object@filename) , fill=TRUE)
} )
setMethod( "show", c( "EnumValueDescriptor" ), function(object){
	cat( sprintf( "enum value descriptor %s", object@full_name), fill=TRUE)
} )

# }}}

# {{{ dollar extractors
setMethod("$", "Message", function(x, name) {

	switch( name,
		"has" = function( ... ) has(x, ...),
		"clone" = function( ... )    .Call( "Message__clone"         , x@pointer, ..., PACKAGE = "RProtoBuf"),
		"isInitialized" = function() .Call( "Message__is_initialized", x@pointer,      PACKAGE = "RProtoBuf"),
		"descriptor" = function()    .Call( "Message__descriptor"     , x@pointer,      PACKAGE = "RProtoBuf" ),

		"size"  = function(field, ...) size(x, field, ... ),
		"bytesize" = function() bytesize(x),
		"swap" = function(...) swap(x,...),
		"update" = function(...) update(x, ...),
		"str" = function() str(x),
		"as.character" = function() as.character(x),
		"as.list" = function() as.list(x),
		"asMessage" = function() asMessage(x),
		"setExtension" = function(field, values, ...) setExtension(x, field, values, ...),
		"getExtension" = function(field, ...) getExtension(x, field, ...),
		"set" = function(...) set( x, ... ),
		"fetch" = function(...) fetch(x, ... ),
		"toString" = function(...) toString( x, ... ),
		"add" = function(...) add( x, ...),

		"serialize" = function(...) serialize( x, ... ),
		"clear" = function(...) clear( x, ... ),

		"fileDescriptor" = function() fileDescriptor(x ),

		# default
		.Call( "getMessageField", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
	} )
setMethod("$<-", "Message", function(x, name, value) {
	.Call( "setMessageField", x@pointer, name, value, PACKAGE = "RProtoBuf" )
	x
} )

setMethod("$", "Descriptor", function(x, name) {
	switch( name,
		"new" = function( ... ) newProto( x, ... ) ,
		"read" = function( input ) read( x, input ) ,
		"readASCII" = function(input, ...) readASCII(x, input, ...),
		"toString" = function(...) toString(x, ...) ,
		"as.character" = function(...) as.character(x, ...) ,
		"as.list" = function(...) as.list(x, ...) ,
		"asMessage" = function() asMessage(x),
		"fileDescriptor" = function() fileDescriptor(x ),
		"name" = function(...) name(x, ... ),

		"containing_type" = function() containing_type(x),
		"field_count" = function() field_count(x),
		"nested_type_count" = function() nested_type_count(x),
		"enum_type_count" = function() enum_type_count(x),
		"field" = function(...) field( x, ... ),
		"nested_type" = function(...) nested_type( x, ...),
		"enum_type" = function(...) enum_type( x, ...),


		# default
		.Call( "do_dollar_Descriptor", x@pointer, name )
	)
} )
setMethod( "$", "EnumDescriptor", function(x, name ){
	switch( name,
		"as.character" = function() as.character(x),
		"as.list"= function() as.list(x) ,
		"asMessage" = function() asMessage(x),
		"toString" = function(...) toString(x, ...) ,
		"name" = function(...) name(x, ...),
		"fileDescriptor" = function() fileDescriptor(x ),
		"containing_type" = function() containing_type(x),
		"length" = function() length(x),
		"value_count" = function() value_count(x),
		"value" = function(...) value(x, ...),
                "has" = function(name, ...) has(x, name, ...),
		# default
		.Call( "get_value_of_enum", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
} )
setMethod( "$", "FieldDescriptor", function(x, name ){
	switch( name,
		"as.character" = function() as.character(x),
		"asMessage" = function() asMessage(x),
		"toString" = function(...) toString(x, ...) ,
		"name" = function(...) name(x, ...),
		"fileDescriptor" = function() fileDescriptor(x ),
		"containing_type" = function() containing_type(x),

		"is_extension" = function() is_extension(x),
		"number" = function() number(x),
		"type" = function(...) type(x, ...),
		"cpp_type" = function(...) cpp_type(x, ...),
		"label" = function(...) label(x, ...),
		"is_repeated" = function() is_repeated(x),
		"is_required" = function() is_required(x),
		"is_optional" = function() is_optional(x),
		"has_default_value" = function() has_default_value(x),
		"default_value" = function() default_value(x),
		"enum_type" = function() enum_type(x),
		"message_type" = function() message_type(x),

		invisible(NULL)
		)
} )

setMethod( "$", "ServiceDescriptor", function(x, name ){
	switch( name,
		"as.character" = function() as.character(x),
		"asMessage" = function() asMessage(x),
		"toString" = function(...) toString(x, ...) ,
		"name" = function(...) name(x, ...),
		"fileDescriptor" = function() fileDescriptor(x ),
		"method_count" = function() method_count(x),
		"method" = function(...) method(x, ... ),

		.Call( "ServiceDescriptor__method", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
} )

setMethod( "$", "FileDescriptor", function(x, name ){

	switch( name,
		"as.character" = function() as.character(x),
		"toString" = function(...) toString(x, ...) ,
		"asMessage" = function() asMessage(x),
		"as.list" = function() as.list(x),
      		"name" = function(...) name(x, ... ),
       		"package" = function() x@package,
                as.list(x)[[name]]
		)
})

setMethod( "$", "EnumValueDescriptor", function(x, name ){

	switch( name,
		"as.character" = function() as.character(x),
		"toString" = function(...) toString(x, ...) ,
		"asMessage" = function() asMessage(x),
		"name" = function(...) name(x, ... ),
		"number" = function() number(x),
		"enum_type" = function(...) enum_type( x, ...),
               invisible(NULL)
		)

})


setMethod( "$", "MethodDescriptor", function(x, name ){
	switch( name,
		"invoke" = function(...) invoke(x, ...),
		"implementation" = if( x@name %in% names(IMPLEMENTATIONS) ){
			get( x@name, IMPLEMENTATIONS )
		},
		"name" = function(...) name(x, ...),
		"toString"  = function() toString(x) ,
		"as.character" = function() as.character(x),
		"fileDescriptor" = function() fileDescriptor(x ),
		"input_type" = function() input_type(x),
		"output_type" = function() output_type(x),

		invisible( NULL)
	)
} )

setMethod( "$<-", "MethodDescriptor", function(x, name, value ){

	if( identical( name, "implementation" ) ){
		check_valid_implementation( x, value )
		assign( x@name, value, envir = IMPLEMENTATIONS )
	}
	x
} )

setMethod( "$", "ZeroCopyInputStream", function(x, name ){
	switch( name,
		# ZeroCopyInputStream C++ methods
		"Next" = function(...) Next(x, ...),
		"ByteCount" = function(...) ByteCount(x, ...),
		"Skip" = function(...) Skip(x, ...),
		"BackUp" = function(...) BackUp(x, ...),

		# CodedInputStream related
		"ReadRaw" = function(...) ReadRaw(x, ...),
		"ReadString" = function(...) ReadString(x, ...),
		"ReadVarint32"= function() ReadVarint32(x),
		"ReadVarint64" = function() ReadVarint64(x),
		"ReadLittleEndian32" = function() ReadLittleEndian32(x),
		"ReadLittleEndian64" = function() ReadLittleEndian64(x),

		# default
		invisible(NULL)
		)
} )

setMethod( "$", "ZeroCopyOutputStream", function(x, name ){
	switch( name,
		# ZeroCopyInputStream C++ methods
		"Next" = function(...) Next(x, ...),
		"ByteCount" = function(...) ByteCount(x, ...),
		"BackUp" = function(...) BackUp(x, ...),

		# CodedOutputStream related
		"WriteRaw" = function(...) WriteRaw(x, ...),
		"WriteString" = function(...) WriteString(x, ...),
		"WriteLittleEndian32" = function(...) WriteLittleEndian32(x,...),
		"WriteLittleEndian64" = function(...) WriteLittleEndian64(x,...),
		"WriteVarint32" = function(...) WriteVarint32(x, ...),
		"WriteVarint64" = function(...) WriteVarint64(x, ...),

		# default
		invisible(NULL)
		)
} )


# }}}

# {{{ [[
setMethod( "[[", "Message", function(x, i, j, ..., exact = TRUE){
	if( missing( i ) ){
		stop( "`i` is required" )
	}
	if( !missing(j) ){
		warning( "`j` is ignored" )
	}

        ## This works correctly by number or name. e.g. p[[1]] or p[["name"]]
	if( is.character( i ) || is.numeric( i ) ){
		.Call( "getMessageField", x@pointer, i, PACKAGE = "RProtoBuf" )
	} else {
		stop( "wrong type, `i` should be a character or a number" )
	}

} )

setMethod( "[[", "Descriptor", function(x, i, j, ..., exact = TRUE){
	if( missing( i ) ){
          stop( "`i` is required" )
	}
	if( !missing(j) ){
          warning( "`j` is ignored" )
	}

	if( is.character( i ) ) {
          # gets a named field, nested type, or enum.
          .Call("Descriptor_getField", x@pointer, i, package="RProtoBuf")
        } else if (is.numeric( i ) ) {
          return(as.list(x)[[i]])
	} else {
          stop( "wrong type, `i` should be a character or a number" )
	}
} )

setMethod( "[[", "EnumDescriptor", function(x, i, j, ..., exact = TRUE){
	if( missing( i ) ){
                stop( "`i` is required" )
	}
	if( !missing(j) ){
                warning( "`j` is ignored" )
	}
        if (is.character(i) || is.numeric(i)) {
          return(as.list(x)[[i]])
        } else {
          stop( "wrong type, `i` should be a character or a number" )
	}
} )

setMethod("[[", "ServiceDescriptor", function(x, i, j, ..., exact = TRUE){
	if( missing( i ) ){
		stop( "`i` is required" )
	}
	if( !missing(j) ){
		warning( "`j` is ignored" )
	}
	if( is.character( i ) || is.numeric( i ) ){
		.Call( "ServiceDescriptor__method", x@pointer, name, PACKAGE = "RProtoBuf" )
	} else{
		stop( "wrong type, `i` should be a character or a number" )
	}
} )

# }}}

# {{{ [[<-
setReplaceMethod( "[[", "Message",
function(x, i, j, ..., exact = TRUE, value ){

	# TODO: we might want to relax this later, i.e
	# allow to mutate repeated fields like this:
	# x[[ "field", 1:2 ]] <- 1:2

	if( missing( i ) ){
		stop( "`i` is required" )
	}
	if( !missing(j) ){
		warning( "`j` is ignored" )
	}

	if( is.character( i ) || is.numeric( i ) ){
		.Call( "setMessageField", x@pointer, i, value, PACKAGE = "RProtoBuf" )
	} else {
		stop( "wrong type, `i` should be a character or a number" )
	}
	x

} )

# }}}

# {{{ update
setGeneric( "update" )
setMethod( "update", "Message", function( object, ... ){

	dots <- list( ... )
	if( !length( dots ) ){
		return( object )
	}
	names <- names( dots )
	named <- dots[ names != "" ]
	if( !length( named ) ){
		return( object )
	}
	.Call( "update_message", object@pointer, named )
	object

} )
# }}}

# {{{ length
setGeneric( "length" )
setMethod( "length", "Message", function( x ){
	.Call( "Message__length", x@pointer, PACKAGE = "RProtoBuf" )
} )
# Returns number of fields, enums, types in message descriptor.
# May be more than field_count which is only fields.
# e.g. length(tutorial.Person) > field_count(tutorial.Person)
setMethod( "length", "Descriptor", function( x ){
        length(as.list(x))
} )
setMethod( "length", "EnumDescriptor", function( x ){
	.Call( "EnumDescriptor__length", x@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "length", "ServiceDescriptor", function( x ){
	.Call( "ServiceDescriptor_method_count", x@pointer, PACKAGE = "RProtoBuf" )
} )
# }}}

# {{{ str
# we need to do this otherwise it gets messed up by the length method
setGeneric( "str" )
setMethod( "str", "Message", function( object, ...){
txt <- sprintf( '	Formal class \'Message\' [package "RProtoBuf"] with 2 slots
  ..@ pointer:<externalptr>
  ..@ type   : chr "%s"
', object@type )
writeLines( txt )
} )
# }}}

# {{{ name
setGeneric( "name", function(object, full = FALSE){
	standardGeneric( "name" )
})
setMethod( "name", c( object = "Descriptor" ) ,
function(object, full = FALSE){
	.Call( "Descriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "FieldDescriptor" ) ,
function(object, full = FALSE){
	.Call( "FieldDescriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "EnumDescriptor" ) ,
function(object, full = FALSE){
	.Call( "EnumDescriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "EnumValueDescriptor" ) ,
function(object, full = FALSE){
	.Call( "EnumDescriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "ServiceDescriptor" ) ,
function(object, full = FALSE){
	.Call( "ServiceDescriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "MethodDescriptor" ) ,
function(object, full = FALSE){
	.Call( "MethodDescriptor__name", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "FileDescriptor" ) ,
function(object, full = FALSE){
	filename <- .Call( "FileDescriptor__name", object@pointer, PACKAGE = "RProtoBuf" )
	if( full ) filename else basename( filename )
})
# }}}

# {{{ names
# as.list() and names() don't make as much sense for FieldDescriptors,
# EnumValueDescriptors, etc.
setMethod( "names", c( x = "Message" ) ,
function(x){
        names(as.list(x))
})
setMethod( "names", c( x = "Descriptor" ) ,
function(x){
        names(as.list(x))
})
setMethod( "names", c( x = "EnumDescriptor" ) ,
function(x){
        names(as.list(x))
})
# }}}

# {{{ as
setAs("Descriptor", "Message", function(from){
	.Call( "Descriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("FieldDescriptor", "Message", function(from){
	.Call( "FieldDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("EnumDescriptor", "Message", function(from){
	.Call( "EnumDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("ServiceDescriptor", "Message", function(from){
	.Call( "ServiceDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("MethodDescriptor", "Message", function(from){
	.Call( "MethodDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("FileDescriptor", "Message", function(from){
	.Call( "FileDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("EnumValueDescriptor", "Message", function(from){
	.Call( "EnumValueDescriptor__as_Message", from@pointer, PACKAGE = "RProtoBuf" )
})
asMessage <- function( x, ... ){
	as( x, "Message", ... )
}
# }}}

# {{{ enum_type
setGeneric( "enum_type", function( object, index, name ){
	standardGeneric( "enum_type" )
})
# }}}
