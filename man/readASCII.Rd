\name{readASCII-methods}
\docType{methods}
\alias{readASCII}
\alias{readASCII-methods}
\alias{readASCII,Descriptor,ANY-method}
\alias{readASCII,Descriptor,character-method}
\title{read a message in ASCII format}
\description{
 Method to read a Message in ASCII format
}
\section{Methods}{
\describe{

\item{\code{signature(descriptor = "Descriptor", input = "ANY")}}{
Read the message from a connection (file, etc ...)
}

\item{\code{signature(descriptor = "Descriptor", input = "character")}}{
Read the message directly from the character string
}
}}
\keyword{methods}
\examples{
# example file that contains a "tutorial.AddressBook" message
book <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )

# read the message
message <- read( tutorial.AddressBook, book )

# Output in text format to a temporary file
out.file <- tempfile()
writeLines( as.character(message), file(out.file))

# Verify that we can read back in the message from a text file.
message2 <- readASCII( tutorial.AddressBook, file(out.file, "rb"))

# Verify that we can read back in the message from an unopened file.
message3 <- readASCII( tutorial.AddressBook, file(out.file))

\dontshow{
stopifnot( identical( message, message2) )
}
}
