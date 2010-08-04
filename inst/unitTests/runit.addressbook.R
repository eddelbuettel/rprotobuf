
## created as
##   demo(addressbook)  ## creates 'book'
##   con <- file("/tmp/addressbook.pb", open="wb")
##   serialize(book, con)
##   close(con)

# this is executed before each test function
.setUp <- function() {
    file <- system.file( "examples", "AddressBookFile", package = "RProtoBuf" )
    book <- read( tutorial.AddressBook, file )
}

test.size <- function() {
	checkTrue(book$size("person"), 4, msg="Number of persons")
}

test.personOne <- function() {
	checkTrue(book$person[[1]]$name, "Humpty Dumpty", msg="First person name")
	checkTrue(length(book$person[[1]]$phone), 2,      msg="First person phones")
	checkTrue(book$person[[1]]$phone[[1]]$number, "123.456.789", msg="First person phone number")
	checkTrue(book$person[[1]]$phone[[1]]$number, "0",           msg="First person phone type")
}
