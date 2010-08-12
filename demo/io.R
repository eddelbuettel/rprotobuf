require( RProtoBuf )

### read messages from files and binary connections

# read a message from a file name
f <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )
m1 <- read( tutorial.AddressBook, f )
writeLines( as.character( m1 ) )

# read the same message from a (binary) file connection
con <- file( f, open = "rb" )
m2 <- read( tutorial.AddressBook, con )
# this also works:
# m2 <- tutorial.AddressBook$read( con )
writeLines( as.character( m2 ) )
close( con )

# TODO: we need another example from a more fancy connection (pipe, ...)

stopifnot( identical( as.character(m1), as.character(m2) ) )

### write messages to files and binary connections

tf1 <- tempfile()
serialize( m1, tf1 )

tf2 <- tempfile()
con <- file( tf2, open = "wb" )
serialize( m2, con )
close( con )

# test that the two binary files are identical
stopifnot( identical(
	readBin( tf1, raw(0), 1000), readBin( tf2, raw(0), 1000)
	) )

