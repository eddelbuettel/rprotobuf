
## created as
##   demo(addressbook)  ## creates 'book'
##   serialize(book, "/tmp/addressbook.pb")

# this is executed before each test function -- but somehow does not work
.setUp <- function() {
    file <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )
    book <- read( tutorial.AddressBook, file )
    assign("book", book, globalenv())
}

test.size <- function() {
    checkEquals(book$size("person"),        2,   msg="Number of persons")
    checkEquals(bytesize(book),             125, msg="Bytes in book")
    checkEquals(bytesize(book$person[[1]]), 60,  msg="Bytes of first person message")
}

test.fileDescriptor <- function() {
    checkEquals(name(book$fileDescriptor()), "addressbook.proto")
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

test.ascii <- function() {
    # Output in text format to a temporary file
    out.file <- tempfile()
    writeLines( as.character(book), file(out.file))

    # Verify that we can read back in the message from a text file.
    book2 <- readASCII( tutorial.AddressBook, file(out.file, "rb"))
    checkEquals(as.character(book), as.character(book2) )

    # Verify that we can read in messages from unopened connections.
    book3 <- readASCII( tutorial.AddressBook, file(out.file))
    checkEquals(as.character(book), as.character(book3) )

    # Verify that we get an exception if we try to read from a text connection.
    # (better than silently getting an empty proto.)
    book4 <- checkException( readASCII( tutorial.AddressBook, file(out.file, "rt")))

    # Test does not work on windows because of chmod
    if(!grepl("mingw", R.Version()$platform)){
        # Verify that we get an exception if the file is not readable.
        old.mode <- file.info(out.file)[["mode"]]
        Sys.chmod(out.file, "0000")
        book5 <- checkException( readASCII( tutorial.AddressBook, file(out.file, "rb")))
        # Set the permissions back to ensure the file is cleaned up properly.
        Sys.chmod(out.file, old.mode)
    }

    # Verify that we get an exception if the file is not parseable.
    out.file2 <- tempfile()
    writeLines("jibberish", file(out.file2))
    book6 <- checkException( readASCII( tutorial.AddressBook, file(out.file2)))

    # Verify that we get an exception if we forget the file() and thus treat the
    # path as a protobuf string.
    checkException( readASCII( tutorial.AddressBook, out.file2))

    incomplete.msg <- new(tutorial.Person, name="Murray", email="murray@stokely.org")
    tmp.file <- tempfile()
    writeLines(as.character(incomplete.msg), file(tmp.file))

    checkTrue(!incomplete.msg$isInitialized())
    # Verify we normally get an exception if we try to read an incomplete ASCII protocol buffer
    checkException( tutorial.Person$readASCII(file(tmp.file)))

    # Verify we can however read it if we set partial=TRUE.
    new.msg <- tutorial.Person$readASCII(file(tmp.file), TRUE)
    checkEquals(incomplete.msg$name, new.msg$name)
}
