\name{type-methods}

\alias{type}
\alias{type-methods}

\alias{cpp_type}
\alias{cpp_type-methods}

\alias{TYPE_DOUBLE}
\alias{TYPE_FLOAT}
\alias{TYPE_INT64}
\alias{TYPE_UINT64}
\alias{TYPE_INT32}
\alias{TYPE_FIXED64}
\alias{TYPE_FIXED32}
\alias{TYPE_BOOL}
\alias{TYPE_STRING}
\alias{TYPE_GROUP}
\alias{TYPE_MESSAGE}
\alias{TYPE_BYTES}
\alias{TYPE_UINT32}
\alias{TYPE_ENUM}
\alias{TYPE_SFIXED32}
\alias{TYPE_SFIXED64}
\alias{TYPE_SINT32}
\alias{TYPE_SINT64}

\alias{CPPTYPE_INT32}
\alias{CPPTYPE_INT64}
\alias{CPPTYPE_UINT32}
\alias{CPPTYPE_UINT64}
\alias{CPPTYPE_DOUBLE}
\alias{CPPTYPE_FLOAT}
\alias{CPPTYPE_BOOL}
\alias{CPPTYPE_ENUM}
\alias{CPPTYPE_STRING}
\alias{CPPTYPE_MESSAGE}

\title{Gets the type or the C++ type of a field}
\description{
Gets the type or the C++ type of a field
}
\arguments{
  \item{object}{A \linkS4class{FieldDescriptor} object.}
  \item{as.string}{If true, print a string representation of the type.}
}
\seealso{
The method is implemented for the \linkS4class{FieldDescriptor} class
}
\keyword{methods}
\examples{
\dontrun{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )
Person <- P( "tutorial.Person", file = proto.file )
type(Person$id)
type(Person$id, as.string=TRUE)
cpp_type(Person$email)
cpp_type(Person$email, TRUE)
}
}