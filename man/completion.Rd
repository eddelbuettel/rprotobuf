\name{completion}
\alias{.DollarNames.Message}
\alias{.DollarNames.Descriptor}
\alias{.DollarNames.EnumDescriptor}
\alias{.DollarNames.FieldDescriptor}
\alias{.DollarNames.FileDescriptor}
\alias{.DollarNames.ServiceDescriptor}
\alias{.DollarNames.MethodDescriptor}
\title{
Completion support for protocol buffer messages and descriptors
}
\description{
These functions support completion of protocol buffer
messages and descriptors.
}
\usage{
\S3method{.DollarNames}{Message}(x, pattern = "")
\S3method{.DollarNames}{Descriptor}(x, pattern = "")
\S3method{.DollarNames}{EnumDescriptor}(x, pattern = "")
\S3method{.DollarNames}{FieldDescriptor}(x, pattern = "")
\S3method{.DollarNames}{FileDescriptor}(x, pattern = "")
\S3method{.DollarNames}{ServiceDescriptor}(x, pattern = "")
\S3method{.DollarNames}{MethodDescriptor}(x, pattern = "")
}
\arguments{
\item{x}{message (\linkS4class{Message}) or descriptor (\linkS4class{Descriptor}) }
\item{pattern}{filter}
}
\value{
Character vector containing potential completions. 

For \linkS4class{Message} objects, completions are 
the fields of the message and a set of pseudo methods ("has")

For \linkS4class{EnumDescriptor} objects, completions
are the names of the possible constants

For \linkS4class{Descriptor} objects, completions
are the names of the fields, enum types and nested message types
defined in the associated message type. 

For \linkS4class{FileDescriptor} objects, completions
are the names of the top-level descriptors (message, enum or service)
contained in the associated file, or pseudo methods.

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
