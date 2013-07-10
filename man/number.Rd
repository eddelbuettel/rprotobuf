\name{number-methods}
\alias{number}
\alias{number-methods}
\title{Gets the declared tag number of a field}
\description{
Gets the declared tag number of a field
}
\seealso{
The method is implemented for \linkS4class{FieldDescriptor} and
\linkS4class{EnumValueDescriptor} classes.
}
\keyword{methods}
\examples{
\dontrun{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )
Person <- P( "tutorial.Person", file = proto.file )
}
\dontshow{ Person <- P("tutorial.Person") }

number(Person$id)
number(Person$email)
as.character(Person)

number(value(tutorial.Person$PhoneType, name="HOME"))
}