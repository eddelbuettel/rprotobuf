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
Version: \tab 0.1-0\cr
Date: \tab $Date$\cr
Depends: \tab Rcpp (>= 0.7.2), methods\cr
SystemRequirements: \tab ProtoBuf compiler (to create C++ header and source files
from .proto descriptions) and library\cr
License: \tab GPL-2\cr
URL: \tab http://code.google.com/p/protobuf/\cr
}
}

\author{
Romain Francois <francoisromain@free.fr> and Dirk Eddelbuettel <edd@debian.org>

Maintainer: Romain and Dirk <rprotobuf-yada@lists.r-forge.r-project.org>
}
\references{
\url{http://code.google.com/p/protobuf/}

The project is maintained in r-forge: \url{http://r-forge.r-project.org/projects/rprotobuf/}
and has a mailing list : \url{https://lists.r-forge.r-project.org/cgi-bin/mailman/listinfo/rprotobuf-yada}
}
\keyword{ package }
\seealso{
	\linkS4class{Message} for some examples
}

\examples{
\dontrun{
# an example proto file
system.file( "proto", "AddressBook.proto", package = "RProtoBuf" )

# create a message of type AddressBook, defined in the example proto file
demo( "addressbook", package = "RProtoBuf" )

# using R binary connections and files to read and write messages
demo( "io", package = "RProtoBuf" )

# more documentation in the vignette
vignette( "RProtoBuf", package = "RProtoBuf" )

}
}

