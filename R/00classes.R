# :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1:

# {{{ class definitions 

setClass( "protobufDescriptor", representation( 
	pointer = "externalptr",   # pointer to a google::protobuf::Descriptor c++ object
	type = "character"         # message type
), prototype = list( pointer = NULL, type = character(0) ) )

setClass( "protobufFieldDescriptor", representation( 
	pointer = "externalptr" ,   # pointer to a google::protobuf::FieldDescriptor c++ object
	name    = "character", 
	full_name  = "character", 
	type    = "character"
), prototype = list( pointer = NULL, name = character(0), 
	full_name = character(0), type = character(0) ) ) 	

setClass( "protobufEnumDescriptor", representation( 
	pointer = "externalptr" ,  # pointer to a google::protobuf::EnumDescriptor c++ object
	name    = "character", 
	full_name  = "character", 
	type    = "character"
), prototype = list( pointer = NULL, name = character(0), 
	full_name = character(0), type = character(0) ) )

setClass( "protobufServiceDescriptor", representation( 
	pointer = "externalptr",   # pointer to a google::protobuf::ServiceDescriptor c++ object
	name = "character"         # full name of the service
), prototype = list( pointer = NULL, name = character(0) ) )

setClass( "protobufMethodDescriptor", representation( 
	pointer = "externalptr",   # pointer to a google::protobuf::ServiceDescriptor c++ object
	name = "character"     ,   # full name of the service
	service = "character"      # full name of the service that defines this method
), prototype = list( pointer = NULL, name = character(0), service = character(0) ) )

setClass( "protobufFileDescriptor", representation( 
	pointer = "externalptr"  # pointer to a google::protobuf::FileDescriptor c++ object
), prototype = list( pointer = NULL ) )

setClass( "protobufEnumValueDescriptor", representation( 
	pointer = "externalptr"  # pointer to a google::protobuf::EnumValueDescriptor c++ object
), prototype = list( pointer = NULL ) )

# actual objects

setClass( "protobufMessage",  representation( 
   pointer = "externalptr",    # pointer to sa google::protobuf::Message object
   type    = "character"       # message type (fully qualified, with package path)
), prototype = list( pointer = NULL, type = character(0) ) ) 

# rpc 

# setClass( "RpcChannel", representation(
# 	pointer = "externalptr", 
# 	host    = "character", 
# 	port    = "integer"
# ), prototype = list( pointer = NULL, host = character(0), port = integer(0) ) )

# }}}

# {{{ new
setGeneric("new")
setMethod("new", signature(Class="protobufDescriptor"), function(Class, ...) newProto(Class, ...))
newProto <- function( descriptor, ... ){
	message <- .Call( "newProtoMessage", descriptor, PACKAGE = "RProtoBuf" )
	update( message, ... )
	message
}
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
		stop( sprintf( "could not find descriptor for message type '%s' ", type ) )
	}
	desc 
}
# }}}

# {{{ show
setMethod( "show", c( "protobufMessage" ), function(object){
	show( sprintf( "protobuf message of type '%s' ", object@type ) ) 
} )
setMethod( "show", c( "protobufDescriptor" ), function(object){
	show( sprintf( "descriptor for type '%s' ", object@type ) ) 
} )
setMethod( "show", c( "protobufFieldDescriptor" ), function(object){
	show( sprintf( "descriptor for field '%s' of type '%s' ", object@name, object@type ) ) 
} )
setMethod( "show", c( "protobufEnumDescriptor" ), function(object){
	show( sprintf( "descriptor for enum '%s' of type '%s' ", object@name, object@type ) ) 
} )
setMethod( "show", c( "protobufServiceDescriptor" ), function(object){
	show( sprintf( "service descriptor <%s>", object@name ) ) 
} )
setMethod( "show", c( "protobufFileDescriptor" ), function(object){
	show( sprintf( "file descriptor" ) ) 
} )
setMethod( "show", c( "protobufEnumValueDescriptor" ), function(object){
	show( sprintf( "enum value descriptor" ) ) 
} )

# }}}

# {{{ dollar extractors
setMethod("$", "protobufMessage", function(x, name) {
	
	switch( name, 
		"has" = function( what ) .Call( "message_has_field", x@pointer, what, PACKAGE = "RProtoBuf" ), 
		"clone" = function( ... ) ._clone.message( x, ... ), 
		"isInitialized" = function() isInitialized( x ), 
		"serialize" = function(...) serialize( x, ... ),
		"clear" = function(...) clear( x, ... ), 
		"size"  = function(field, ...) size(x, field, ... ),
		"bytesize" = function() bytesize(x), 
		"swap" = function(...) swap(x,...),
		"update" = function(...) update(x, ...),
		"str" = function() str(x), 
		"as.character" = function() as.character(x), 
		"as.list" = function() as.list(x),
		"asMessage" = function() asMessage(x), 
		"set" = function(...) set( x, ... ), 
		"fetch" = function(...) fetch(x, ... ), 
		"toString" = function(...) toString( x, ... ),
		"add" = function(...) add( x, ...), 
		
		"descriptor" = function() descriptor(x), 
		"fileDescriptor" = function() fileDescriptor(x ), 
		
		# default
		.Call( "getMessageField", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
	} )
setMethod("$", "protobufDescriptor", function(x, name) {
	switch( name, 
		"new" = function( ... ) newProto( x, ... ) , 
		"read" = function( input ) read( x, input ) ,
		"toString" = function(...) toString(x, ...) ,
		"as.character" = function(...) as.character(x, ...) ,
		"as.list" = function(...) as.character(x, ...) ,
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
setMethod( "$", "protobufEnumDescriptor", function(x, name ){
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
		"value" = function(...) value(x, ...) , 
		
		# default
		.Call( "get_value_of_enum", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
} )
setMethod( "$", "protobufFieldDescriptor", function(x, name ){
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

setMethod( "$", "protobufServiceDescriptor", function(x, name ){
	switch( name, 
		"as.character" = function() as.character(x),
		"asMessage" = function() asMessage(x), 
		"toString" = function(...) toString(x, ...) ,
		"name" = function(...) name(x, ...), 
		"fileDescriptor" = function() fileDescriptor(x ),
		"method_count" = function() method_count(x), 
		"method" = function(...) method(x, ... ), 
		
		.Call( "get_service_method", x@pointer, name, PACKAGE = "RProtoBuf" )
		)
} )

setMethod( "$", "protobufFileDescriptor", function(x, name ){
	
	switch( name, 
		"as.character" = function() as.character(x),
		"toString" = function(...) toString(x, ...) ,
		"asMessage" = function() asMessage(x), 
		"as.list" = function() as.list(x), 
		
		invisible(NULL)
		)

})

setMethod( "$", "protobufEnumValueDescriptor", function(x, name ){
	
	switch( name, 
		"as.character" = function() as.character(x),
		"toString" = function(...) toString(x, ...) ,
		"asMessage" = function() asMessage(x), 
		
		invisible(NULL)
		)

})

setMethod("$<-", "protobufMessage", function(x, name, value) {
	.Call( "setMessageField", x@pointer, name, value, PACKAGE = "RProtoBuf" )
	x
} )
# }}}

# {{{ [[
setMethod( "[[", "protobufMessage", function(x, i, j, ..., exact = TRUE){
	
	if( missing( i ) ){
		stop( "`i` is required" )
	}
	if( !missing(j) ){
		warning( "`j` is ignored" )
	}
	
	if( is.character( i ) || is.numeric( i ) ){
		.Call( "getMessageField", x@pointer, i, PACKAGE = "RProtoBuf" )
	} else {
		stop( "wrong type, `i` should be a character or a number" )
	}
	
} )

setMethod("[[", "protobufServiceDescriptor", function(x, i, j, ..., exact = TRUE){
	if( missing( i ) ){
		stop( "`i` is required" )
	}
	if( !missing(j) ){
		warning( "`j` is ignored" )
	}
	if( is.character( i ) || is.numeric( i ) ){
		.Call( "get_service_method", x@pointer, name, PACKAGE = "RProtoBuf" )
	} else{
		stop( "wrong type, `i` should be a character or a number" )
	}
} )

# }}}

# {{{ [[<-
setReplaceMethod( "[[", "protobufMessage", 
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
setMethod( "update", "protobufMessage", function( object, ... ){
	
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
setMethod( "length", "protobufMessage", function( x ){
	.Call( "get_message_length", x@pointer, PACKAGE = "RProtoBuf" )
} )
setMethod( "length", "protobufEnumDescriptor", function( x ){
	.Call( "EnumDescriptor_length", x@pointer, PACKAGE = "RProtoBuf" )
} ) 
setMethod( "length", "protobufServiceDescriptor", function( x ){
	.Call( "ServiceDescriptor_method_count", x@pointer, PACKAGE = "RProtoBuf" )
} ) 
# }}}

# {{{ str
# we need to do this otherwise it gets messed up by the length method
setGeneric( "str" )
setMethod( "str", "protobufMessage", function( object, ...){
txt <- sprintf( '	Formal class \'protobufMessage\' [package "RProtoBuf"] with 2 slots
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
setMethod( "name", c( object = "protobufDescriptor" ) , 
function(object, full = FALSE){
	.Call( "name_descriptor", object@pointer, full, PACKAGE = "RProtoBuf" )
}) 
setMethod( "name", c( object = "protobufFieldDescriptor" ) , 
function(object, full = FALSE){
	.Call( "name_descriptor", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "protobufEnumDescriptor" ) , 
function(object, full = FALSE){
	.Call( "name_enum_descriptor", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "protobufServiceDescriptor" ) , 
function(object, full = FALSE){
	.Call( "name_service_descriptor", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "protobufMethodDescriptor" ) , 
function(object, full = FALSE){
	.Call( "name_method_descriptor", object@pointer, full, PACKAGE = "RProtoBuf" )
})
setMethod( "name", c( object = "protobufFileDescriptor" ) , 
function(object, full = FALSE){
	filename <- .Call( "name_file_descriptor", object@pointer, PACKAGE = "RProtoBuf" )
	if( full ) filename else basename( filename )
})
# }}}

# {{{ as
setAs("protobufDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_Descriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufFieldDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_FieldDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufEnumDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_EnumDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufServiceDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_ServiceDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufMethodDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_MethodDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufFileDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_FileDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
setAs("protobufEnumValueDescriptor", "protobufMessage", function(from){
	.Call( "asMessage_EnumValueDescriptor", from@pointer, PACKAGE = "RProtoBuf" )
})
asMessage <- function( x, ... ){
	as( x, "protobufMessage", ... )
}
# }}}

# {{{ enum_type
setGeneric( "enum_type", function( object, index, name ){
	standardGeneric( "enum_type" )
})
# }}}
