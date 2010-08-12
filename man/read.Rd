\name{read-methods}
\docType{methods}
\alias{read}
\alias{read-methods}
\alias{read,Descriptor,character-method}
\alias{read,Descriptor,raw-method}
\alias{read,Descriptor,ANY-method}
\title{Read a protocol buffer message from a connection}
\description{
	Read a \linkS4class{Message} from a 
	connection using its associated \linkS4class{Descriptor}
}
\section{Methods}{
\describe{
	\item{\code{signature(descriptor = "Descriptor", input = "character")}}{ Read the message from a file }
	\item{\code{signature(descriptor = "Descriptor")}}{ Read from a binary connection.  }
	\item{\code{signature(descriptor = "Descriptor", input = "raw")}}{ Read the message from a raw vector }
}}
\keyword{methods}
\examples{
# example file that contains a "tutorial.AddressBook" message
book <- system.file( "examples", "AddressBookFile", package = "RProtoBuf" )

# read the message
message <- read( tutorial.AddressBook, book )

# or using the pseudo method 
message <- tutorial.AddressBook$read( book )

# write its debug string
writeLines( as.character( message ) )

# grab the name of each person
sapply( message$person, function(p) p$name )

# read from a binary file connection
f <- file( book, open = "rb" )
message2 <- read( tutorial.AddressBook, f )
close( f )

# read from a message payload (raw vector)
payload <- readBin( book, raw(0), 5000 )
message3 <- tutorial.AddressBook$read( payload )

\dontshow{
stopifnot( identical( message, message2) )
stopifnot( identical( message, message3) )
}

}
