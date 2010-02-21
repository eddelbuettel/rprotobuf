# load the package
require( RProtoBuf )

# read all the proto files in the proto directory
# of the package "RProtoBuf"
# (this is also done in the startup of the package, so this call is 
#  actually redundant)
readProtoFiles( package = "RProtoBuf" ) 


# creating three Person messages

# create a prototype with a simple call to new on the 
# descriptor for the Person message type, and then update the message
# with fields
romain <- update( new( tutorial.Person ), 
	email = "romain@r-enthusiasts.com", 
	id = 1, 
	name = "Romain Francois", 
	phone = new( tutorial.Person.PhoneNumber , number = "+33(0)...", type = "MOBILE" )
	)

# directly supply parameters to the constructor
dirk <- new( tutorial.Person, 
	email = "edd@debian.org", 
	id = 2, 
	name = "Dirk Eddelbuettel" ) 

# update the phone repeated field with a list of PhoneNumber messages
dirk$phone <- list( 
	new( tutorial.Person.PhoneNumber , number = "+01...", type = "MOBILE" ), 
	new( tutorial.Person.PhoneNumber , number = "+01...", type = "HOME" ) )

# build the address book
book <- new( tutorial.AddressBook, person = list( romain, dirk ) )

# debug string. This is not what is transferred in the wire
writeLines( as.character( book ) )

# the serialized message
# see also the io demo to see how to serialize messages to connections 
# and files
serialize( book, NULL )

# number of bytes taken by the message on the wire
bytesize( book )
length( serialize( book, NULL ) )

# swap two persons in the address book
# (1-based indexing)
book$swap( "person", 1L , 2L )
writeLines( as.character( book ) )

# number of "person" in the book
book$size( "person" )

# clear the message
book$clear( )
writeLines( as.character( book ) )


