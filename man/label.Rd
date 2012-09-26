\name{label-methods}

\alias{label}
\alias{label-methods}

\alias{LABEL_OPTIONAL}
\alias{LABEL_REQUIRED}
\alias{LABEL_REPEATED}

\title{Gets the label of a field}
\description{
Gets the label of a field (optional, required, or repeated).
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
label(Person$id)
label(Person$email)
label(Person$phone)
label(Person$id, TRUE)
label(Person$email, TRUE)
label(Person$phone, TRUE)
LABEL_OPTIONAL
LABEL_REQUIRED
LABEL_REPEATED
}
}