\name{.DollarNames.protobufMessage}
\alias{.DollarNames.protobufMessage}
\alias{.DollarNames.protobufDescriptor}
\alias{.DollarNames.protobufEnumDescriptor}
\alias{.DollarNames.protobufFieldDescriptor}
\title{
Completion support for protocol buffer messages and descriptors
}
\description{
These functions support completion of protocol buffer
messages and descriptors.
}
\usage{
\S3method{.DollarNames}{protobufMessage}(x, pattern = "")
\S3method{.DollarNames}{protobufDescriptor}(x, pattern = "")
\S3method{.DollarNames}{protobufEnumDescriptor}(x, pattern = "")
\S3method{.DollarNames}{protobufFieldDescriptor}(x, pattern = "")
}
\arguments{
\item{x}{message (\linkS4class{protobufMessage}) or descriptor (\linkS4class{protobufDescriptor}) }
\item{pattern}{filter}
}
\value{
Character vector containing potential completions. 

For \linkS4class{protobufMessage} objects, completions are 
the fields of the message and a set of pseudo methods ("has")

For \linkS4class{protobufEnumDescriptor} objects, completions
are the names of the possible constants

For \linkS4class{protobufDescriptor} objects, completions
are the names of the fields, enum types and nested message types
defined in the associated message type. 

}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
# creating a prototype message from the descriptor
p <- new( tutorial.Person )

.DollarNames( p )
.DollarNames( tutorial.Person )
# but this is usually used with the <TAB> expansion on the command line
# <TAB> means "press the TAB key"
# p$<TAB>
# Person$<TAB>

}
\keyword{ programming }
