\name{as.list.protobufMessage}
\alias{as.list.protobufMessage}
\alias{as.list.protobufDescriptor}
\alias{as.list.protobufEnumDescriptor}
\title{
Grab the protocol buffer message as an R list
}
\description{
Utility to grab the protocol buffer message as 
an R list, with one item per field. 
}
\usage{
\S3method{as.list}{protobufMessage}(x, ...)
\S3method{as.list}{protobufDescriptor}(x, ...)
\S3method{as.list}{protobufEnumDescriptor}(x, ...)
}
\arguments{
	\item{x}{A protocol buffer message, instance of \linkS4class{protobufMessage}, 
	or a protocol message descriptor, instance of \linkS4class{protobufDescriptor} }
	\item{\dots}{ignored}
}
\value{
For messages, a list of the content of the fields is 
returned.

For descriptors, a list containing 
nested type descriptors (\linkS4class{protobufDescriptor} objects), 
enum type descriptors (\linkS4class{protobufEnumDescriptor} objects), 
or field descriptors (\linkS4class{protobufFieldDescriptor} objects)
}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
\dontrun{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 
Person <- P( "tutorial.Person", file = proto.file )
romain <- new( Person, email = "francoisromain@free.fr", id = 1 )
as.list( romain )
as.list( Person )
as.list( Person$PhoneType)
}
}
\keyword{ programming }
