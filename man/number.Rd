\name{number-methods}
\alias{number}
\alias{number-methods}
\title{Gets the declared tag number of a field}
\description{
Gets the declared tag number of a field
}
\seealso{
The method is implemented for the \linkS4class{FieldDescriptor} class
}
\keyword{methods}
\examples{
\dontrun{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )
Person <- P( "tutorial.Person", file = proto.file )
number(Person$id)
number(Person$email)
as.character(Person)
}
}