\name{RProtoBuf-package}
\alias{RProtoBuf-package}
\alias{RProtoBuf}
\docType{package}
\title{
R Interface to the Protocol Buffers API
}
\description{
Protocol Buffers are a way of encoding structured data in an
efficient yet extensible format. Google uses Protocol Buffers for almost all
of its internal RPC protocols and file formats.

This package provides R API to create, manipulate, parse and serialize
protocol buffer messages from R
}
\details{
\tabular{ll}{
Package: \tab RProtoBuf\cr
Version: \tab 0.0-4\cr
Date: \tab $Date$\cr
Depends: \tab Rcpp (>= 0.6.4), methods\cr
SystemRequirements: \tab ProtoBuf compiler (to create C++ header and source files
from .proto descriptions) and library\cr
License: \tab GPL-2\cr
URL: \tab http://code.google.com/p/protobuf/\cr
Packaged: \tab 2009-11-02 20:55:25 UTC; romain\cr
Built: \tab R 2.11.0; i686-pc-linux-gnu; 2009-11-02 20:55:29 UTC; unix\cr
}
}

\author{
Dirk Eddelbuettel <edd@debian.org>, Romain Francois <francoisromain@free.fr>, Saptarshi Guha <saptarshi.guha@gmail.com>

Maintainer: Dirk Eddelbuettel <edd@debian.org>
}
\references{
\url{http://code.google.com/p/protobuf/}
}
\keyword{ package }
\seealso{
	\linkS4class{protobufMessage} for some examples
}

\examples{
\dontrun{
# an example proto file
system.file( "proto", "AddressBook.proto", package = "RProtoBuf" )

# create a message of type AddressBook, defined in the example proto file
demo( "addressbook", package = "RProtoBuf" )

# using R binary connections and files to read and write messages
demo( "io", package = "RProtoBuf" )

}
}

