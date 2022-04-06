setGeneric( "toTextFormat", function( x ) {
    standardGeneric( "toTextFormat" )
} )
setMethod( "toTextFormat", c( x = "Message"),
function(x) {
    .Call( "Message__print_text_format", x@pointer, PACKAGE = "RProtoBuf" )
} )
