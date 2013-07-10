\name{as.list.Message}
\alias{as.list.Message}
\alias{as.list.Descriptor}
\alias{as.list.EnumDescriptor}
\alias{as.list.FileDescriptor}
\alias{as.list.ServiceDescriptor}
\title{
Grab the protocol buffer message as an R list
}
\description{
Utility to grab the protocol buffer message as 
an R list, with one item per field. 
}
\usage{
\S3method{as.list}{Message}(x, ...)
\S3method{as.list}{Descriptor}(x, ...)
\S3method{as.list}{EnumDescriptor}(x, ...)
\S3method{as.list}{FileDescriptor}(x, ...)
\S3method{as.list}{ServiceDescriptor}(x, ...)
}
\arguments{
	\item{x}{A protocol buffer message, instance of \linkS4class{Message}, 
	or a protocol message descriptor, instance of \linkS4class{Descriptor} }
	\item{\dots}{ignored}
}
\value{
For messages, a list of the content of the fields is 
returned.

For message type descriptors, a list containing 
nested type descriptors (\linkS4class{Descriptor} objects), 
enum type descriptors (\linkS4class{EnumDescriptor} objects), 
or field descriptors (\linkS4class{FieldDescriptor} objects)

For enum descriptors, a named list of the enumerated values.

For file descriptors, a named list of descriptors defined in the
specified file descriptor.

For service descriptors, ...

}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
Person <- P( "tutorial.Person" )
romain <- new( Person, email = "francoisromain@free.fr", id = 1 )
as.list( romain )
as.list( Person )
as.list( Person$PhoneType)
}
\keyword{ programming }
