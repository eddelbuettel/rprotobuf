\name{containing_type-methods}
\alias{containing_type}
\alias{containing_type-methods}
\title{Gets the message type descriptor that contains a descriptor}
\description{
Gets a \linkS4class{Descriptor} describing the message type 
that contains the descriptor. 
}
\seealso{
The method is implemented for these classes : 
\linkS4class{Descriptor}, \linkS4class{EnumDescriptor}, 
\linkS4class{FieldDescriptor}
}
\examples{
# Containing type of a field is the message descriptor
tutorial.Person$id$containing_type()

# No containing type for the top-level message descriptor.
tutorial.Person$containing_type()
}
\keyword{methods}
