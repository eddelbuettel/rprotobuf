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
	email = "francoisromain@free.fr", 
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
	
# with/within style
saptarshi <- within( new(tutorial.Person), {
	id <- 3
	name <- "Saptarshi Guha"
	email <- "saptarshi.guha@gmail.com" 
} )

# build the address book
rprotobuf.developpers <- new( tutorial.AddressBook, 
	person = list( romain, dirk, saptarshi ) )

# debug 
writeLines( as.character( rprotobuf.developpers ) )

# TODO: serialize and parse back

