\name{read-methods}
\docType{methods}
\alias{read}
\alias{read-methods}
\alias{read,protobufDescriptor,character-method}
\alias{read,protobufDescriptor,connection-method}
\title{Read a protocol buffer message from a connection}
\description{
	Read a \linkS4class{protobufMessage} from a 
	connection using its associated \linkS4class{protobufDescriptor}
}
\section{Methods}{
\describe{
	\item{\code{signature(descriptor = "protobufDescriptor", input = "character")}}{ Read the message from a file }
	\item{\code{signature(descriptor = "protobufDescriptor", input = "connection")}}{ Read from a binary connection.  }
}}
\keyword{methods}
\examples{
# example file that contains a "tutorial.AddressBook" message
book <- system.file( "examples", "AddressBookFile", package = "RProtoBuf" )

# read the message
message <- read( tutorial.AddressBook, book )

# write its debug string
writeLines( as.character( message ) )

# grab the name of each person
sapply( message$person, function(p) p$name )

}
