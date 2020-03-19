\name{readJSON-methods}
\docType{methods}
\alias{readJSON}
\alias{readJSON-methods}
\alias{readJSON,Descriptor,ANY-method}
\alias{readJSON,Descriptor,character-method}
\title{read a message in JSON format}
\description{
 Method to read a Message in JSON format
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
\dontrun{
# example file that contains a "tutorial.AddressBook" message
book <- system.file( "examples", "addressbook.pb", package = "RProtoBuf" )

# read the message
message <- read( tutorial.AddressBook, book )

# Output in text format to a temporary file
out.file <- tempfile()
writeLines( message$toJSON(), file(out.file))

# Verify that we can read back in the message from a text file.
message2 <- readJSON( tutorial.AddressBook, file(out.file, "rb"))

# Verify that we can read back in the message from an unopened file.
message3 <- readJSON( tutorial.AddressBook, file(out.file))

\dontshow{
stopifnot( identical( message, message2) )
}
}
}
