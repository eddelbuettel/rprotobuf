\name{readProtoFiles}
\alias{readProtoFiles}
\title{
protocol buffer descriptor importer
}
\description{
Imports proto files into the descriptor pool that 
is then used by the \code{P} function to resolve
message type names.
}
\usage{
readProtoFiles(files, dir, package="RProtoBuf", pattern="\\\\.proto$", lib.loc=NULL)
}
\arguments{
  \item{files}{Proto files}
  \item{dir}{Directory. If \code{files} is not specified, files
  with the "proto" extension in the \code{dir} directory 
  are imported}
  \item{package}{R package name. If \code{files} and \code{dir} are
  missing, "proto" files in the "proto" directory of the 
  package tree are imported.}
  \item{pattern}{A filename pattern to match proto files.}
  \item{lib.loc}{Library location.}
}
\value{
\code{NULL}, invisibly. 
}
\author{
Romain Francois <francoisromain@free.fr>
}
\seealso{
	\code{\link{P}}
}
\examples{
\dontrun{
# from a package
readProtoFiles( package = "RProtoBuf" )

# from a directory
proto.dir <- system.file( "proto", package = "RProtoBuf" )
readProtoFiles( dir = proto.dir )

# set of files
proto.files <- list.files( proto.dir, full.names = TRUE )
readProtoFiles( proto.files )
}
}
\keyword{ programming }

