\name{RProtoBuf-package}
\alias{RProtoBuf-package}
\alias{RProtoBuf}
\docType{package}
\title{R Interface to the Protocol Buffers API}
\description{
Protocol Buffers are a way of encoding structured data in an
efficient yet extensible format. Google uses Protocol Buffers for almost all
of its internal RPC protocols and file formats.

This package provides R API to create, manipulate, parse and serialize
protocol buffer messages from R
}
\author{Romain Francois, Dirk Eddelbuettel, Murray Stokely and Jeroen Ooms.}
\references{\url{https://github.com/eddelbuettel/rprotobuf}}
\keyword{package}
\seealso{\linkS4class{Message} for some examples}

\examples{
\dontrun{
# an example proto file
system.file( "proto", "addressbook.proto", package = "RProtoBuf" )

# create a message of type AddressBook, defined in the example proto file
demo( "addressbook", package = "RProtoBuf" )

# using R binary connections and files to read and write messages
demo( "io", package = "RProtoBuf" )

# more documentation in the vignette
vignette( "RProtoBuf", package = "RProtoBuf" )
}
}

