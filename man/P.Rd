\name{P}
\alias{P}
\title{Protocol Buffer descriptor importer}
\description{
The \code{P} function searches for a protocol message
descriptor in the descriptor pool.
}
\usage{
P(type, file)
}
\arguments{
  \item{type}{Fully qualified type name of the protocol buffer}
  \item{file}{optional proto file. If given, the definition
  contained in the file is first registered with the 
  pool of message descriptors}
}
\value{
An object of class \linkS4class{protobufDescriptor}. 
An error is generated otherwise.
}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 
Person <- P( "tutorial.Person", file = proto.file )
as.character( Person )
}
\keyword{ interface }
