
library(RProtoBuf)

## created as
##   demo(addressbook)  ## creates 'book'
##   serialize(book, "/tmp/addressbook.pb")

# this is executed before each test function -- but somehow does not work
#.setUp <- function() {
file <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )
book <- read( tutorial.AddressBook, file )
assign("book", book, globalenv())
#}

#test.size <- function() {
expect_equal(book$size("person"),        2,   info="Number of persons")
expect_equal(bytesize(book),             125, info="Bytes in book")
expect_equal(bytesize(book$person[[1]]), 60,  info="Bytes of first person message")
#}

#test.fileDescriptor <- function() {
expect_equal(name(book$fileDescriptor()), "addressbook.proto")
#}

#test.personOne <- function() {
expect_equal(book$person[[1]]$name,              "Romain Francois",   info="First person name")
expect_equal(book$person[[2]]$name,              "Dirk Eddelbuettel", info="First person name")
expect_equal(book$person[[1]]$id,                1,   		 info="First person id")
expect_equal(book$person[[2]]$id,                2,			 info="First person id")
expect_equal(book$person[[1]]$email,             "romain@r-enthusiasts.com",   info="First person email")
expect_equal(book$person[[2]]$email,             "edd@debian.org",    info="Second person email")
expect_equal(length(book$person[[1]]$phone),     1,                   info="First person phones")
expect_equal(length(book$person[[2]]$phone),     2,                   info="Second person phones")
expect_equal(book$person[[1]]$phone[[1]]$number, "+33(0)...",         info="First person phone number")
expect_equal(book$person[[2]]$phone[[1]]$number, "+01...",            info="Second person phone number")
expect_equal(book$person[[2]]$phone[[1]]$type,   0,                   info="Second person phone number")
#}

#test.ascii <- function() {
## Output in text format to a temporary file
out.file <- tempfile()
writeLines( as.character(book), file(out.file))

## Verify that we can read back in the message from a text file.
book2 <- readASCII( tutorial.AddressBook, file(out.file, "rb"))
expect_equal(as.character(book), as.character(book2) )

## Verify that we can read in messages from unopened connections.
book3 <- readASCII( tutorial.AddressBook, file(out.file))
expect_equal(as.character(book), as.character(book3) )

## Verify that we get an exception if we try to read from a text connection.
## (better than silently getting an empty proto.)
book4 <- expect_error( readASCII( tutorial.AddressBook, file(out.file, "rt")))

## # Test does not work on windows because of chmod
## if(!grepl("mingw", R.Version()$platform)){
##     # Verify that we get an exception if the file is not readable.
##     old.mode <- file.info(out.file)[["mode"]]
##     Sys.chmod(out.file, "0000")
##     book5 <- checkException( readASCII( tutorial.AddressBook, file(out.file, "rb")))
##     # Set the permissions back to ensure the file is cleaned up properly.
##     Sys.chmod(out.file, old.mode)
## }

## Verify that we get an exception if the file is not parseable.
out.file2 <- tempfile()
writeLines("jibberish", file(out.file2))
book6 <- expect_error( readASCII( tutorial.AddressBook, file(out.file2)))

## Verify that we get an exception if we forget the file() and thus treat the
## path as a protobuf string.
expect_error( readASCII( tutorial.AddressBook, out.file2))

incomplete.msg <- new(tutorial.Person, name="Murray", email="murray@stokely.org")
tmp.file <- tempfile()
writeLines(as.character(incomplete.msg), file(tmp.file))

expect_true(!incomplete.msg$isInitialized())
## Verify we normally get an exception if we try to read an incomplete ASCII protocol buffer
expect_error(tutorial.Person$readASCII(file(tmp.file)))

## Verify we can however read it if we set partial=TRUE.
new.msg <- tutorial.Person$readASCII(file(tmp.file), TRUE)
expect_equal(incomplete.msg$name, new.msg$name)
#}

## Ensure we do not try to run JSON tests on older ProtoBuf versions
## Support starts with version 3.

isProto2 <- (RProtoBuf:::getProtobufLibVersion() < 3000000)
if (isProto2) exit_file("Skipping JSON tests with ProtoBuf2")

# These tests are similar to the group of tests covered with test.ascii above.
#test.json <- function() {
## Output in JSON format to a temporary file
out.file <- tempfile()
writeLines( book$toJSON(), file(out.file))

## Verify that we can read back in the message from a text file.
book2 <- readJSON( tutorial.AddressBook, file(out.file, "rb"))
expect_equal(as.character(book), as.character(book2) )

## Verify that we can read in messages from unopened connections.
book3 <- readJSON( tutorial.AddressBook, file(out.file))
expect_equal(as.character(book), as.character(book3) )

## Verify that we get an exception if we try to read from a text connection.
## (better than silently getting an empty proto.)
book4 <- expect_error( readJSON( tutorial.AddressBook, file(out.file, "rt")))

## Verify that we get an exception if the file is not parseable.
out.file2 <- tempfile()
writeLines("jibberish", file(out.file2))
book6 <- expect_error( readJSON( tutorial.AddressBook, file(out.file2)))

## Verify that we get an exception if we forget the file() and thus treat the
## path as a protobuf string.
expect_error( readJSON( tutorial.AddressBook, out.file2))
#}
