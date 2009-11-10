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

# actual objects

setClass( "protobufMessage",  representation( 
   pointer = "externalptr",    # pointer to sa google::protobuf::Message object
   type    = "character"       # message type (fully qualified, with package path)
), prototype = list( pointer = NULL, type = character(0) ) ) 

# setClass( "protobufEnum",  representation( 
#    pointer = "externalptr",    # pointer to some C++ variable
#    type    = "character"       # enum type (fully qualified, with package path)
# ), prototype = list( pointer = NULL, type = character(0) ) ) 

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

# }}}

# {{{ dollar extractors
setMethod("$", c(x="protobufMessage"), function(x, name) {
	if( identical( name, "has") ){
		function( what ) {
			.Call( "message_has_field", x@pointer, what, PACKAGE = "RProtoBuf" )
		}
	} else if( identical( name, "clone" ) ) {
		function( ... ){
			._clone.message( x, ... )
		}
	} else if( identical( name, "isInitialized" ) ) {
		function() isInitialized( x )
	} else if( identical( name, "serialize" ) ){
		function(...) serialize( x, ... ) 
	} else {
		.Call( "getMessageField", x@pointer, name, PACKAGE = "RProtoBuf" )
	}
} )
setMethod("$", c(x="protobufDescriptor"), function(x, name) {
	if( identical( name, "new") ){
		function( ... ){
			newProto( x, ... )
		}
	} else if( identical( name, "read" ) ) {
		function( input ){
			read( x, input )
		}
	} else{
		.Call( "do_dollar_Descriptor", x@pointer, name )
	}
} )
setMethod( "$", "protobufEnumDescriptor", function(x, name ){
	.Call( "get_value_of_enum", x@pointer, name, PACKAGE = "RProtoBuf" )
} )
setMethod("$<-", c(x="protobufMessage"), function(x, name, value) {
	.Call( "setMessageField", x@pointer, name, value, PACKAGE = "RProtoBuf" )
	x
} )
# }}}

# {{{ [[
setMethod( "[[", "protobufMessage", function(x, i, j, ...){
	
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
# }}}

# {{{ [[<-
setReplaceMethod( "[[", "protobufMessage", 
function(x, i, j, ..., value ){

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

