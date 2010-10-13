
## created as
##   demo(addressbook)  ## creates 'book'
##   serialize(book, "/tmp/addressbook.pb")

# this is executed before each test function
.setUp <- function() {
    #addressbook.proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )
    #readProtoFiles( file = addressbook.proto.file )
    file <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )
    book <<- read( tutorial.AddressBook, file )
}

test.size <- function() {
    checkEquals(book$size("person"),        2,   msg="Number of persons")
    checkEquals(bytesize(book),             125, msg="Bytes in book")
    checkEquals(bytesize(book$person[[1]]), 60,  msg="Bytes of first person message")
}

test.personOne <- function() {
    checkEquals(book$person[[1]]$name,              "Romain Francois",   msg="First person name")
    checkEquals(book$person[[2]]$name,              "Dirk Eddelbuettel", msg="First person name")
    checkEquals(book$person[[1]]$id,                1,   		 msg="First person id")
    checkEquals(book$person[[2]]$id,                2,			 msg="First person id")
    checkEquals(book$person[[1]]$email,    "romain@r-enthusiasts.com",   msg="First person email")
    checkEquals(book$person[[2]]$email,             "edd@debian.org",    msg="Second person email")
    checkEquals(length(book$person[[1]]$phone),     1,                   msg="First person phones")
    checkEquals(length(book$person[[2]]$phone),     2,                   msg="Second person phones")
    checkEquals(book$person[[1]]$phone[[1]]$number, "+33(0)...",         msg="First person phone number")
    checkEquals(book$person[[2]]$phone[[1]]$number, "+01...",            msg="Second person phone number")
    checkEquals(book$person[[2]]$phone[[1]]$type,   0,                   msg="Second person phone number")
}
