\name{readProtoFiles}
\alias{readProtoFiles}
\alias{readProtoFiles2}
\alias{resetDescriptorPool}
\title{protocol buffer descriptor importer}
\description{
  Imports proto files into the descriptor pool that 
  is then used by the \code{P} function to resolve
  message type names.
}
\usage{
  readProtoFiles(files, dir, package="RProtoBuf", pattern="\\\\.proto$", lib.loc=NULL)
  readProtoFiles2(files, dir=".", pattern="\\\\.proto$", recursive=FALSE, protoPath=getwd())
  resetDescriptorPool()
}
\arguments{
  \item{files}{Proto files}
  \item{dir}{Directory. If \code{files} is not specified, files
  with the "proto" extension in the \code{dir} directory 
  are imported}
  \item{package}{R package name. If \code{files} and \code{dir} are
  missing, "proto" files in the "proto" directory of the 
  package tree are imported.}
  \item{pattern}{A filename pattern to match proto files when using \code{dir}.}
  \item{recursive}{Whether to descend recursively into \code{dir}.}
  \item{lib.loc}{Library location.}
  \item{protoPath}{Search path for proto file imports.}
}
\details{
  \code{readProtoFiles2} is different from \code{readProtoFiles} to be
  consistent with the behavior of \code{protoc} command line tool in
  being explicit about the search path for proto import statements. In addition,
  we also require that both \code{files} and \code{dir} arguments are
  interpreted relative to \code{protoPath}, so that there is consistency in
  future imports of the same files through import statements of other proto
  files.

  \code{resetDescriptorPool} clears all imported proto definitions.
}
\value{\code{NULL}, invisibly.}
\author{Romain Francois <francoisromain@free.fr>}
\seealso{\code{\link{P}}}
\examples{
\dontrun{
# from a package
readProtoFiles(package = "RProtoBuf")

# from a directory
proto.dir <- system.file("proto", package = "RProtoBuf")
readProtoFiles(dir = proto.dir)

# set of files
proto.files <- list.files(proto.dir, full.names = TRUE)
readProtoFiles(proto.files)
}
}
\keyword{programming}

