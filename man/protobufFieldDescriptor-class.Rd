\name{protobufFieldDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufFieldDescriptor-class}
\alias{show,protobufFieldDescriptor-method}

\title{Class "protobufFieldDescriptor"}
\description{R representation of message type field descriptor. 
This is a thin wrapper around the C++ class \code{FieldDescriptor} }
\section{Objects from the Class}{
Objects typically are retrieved from \linkS4class{protobufFieldDescriptor}
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{FieldDescriptor} c++ object }
  	  \item{\code{name}:}{ name of the field within the message type }
  	  \item{\code{full_name}:}{Fully qualified name of the field}
  	  \item{\code{type}:}{Fully qualified name of the type that contains this field }
  }
}
\section{Methods}{
  \describe{
    \item{show}{\code{signature(object = "protobufFieldDescriptor")}: small description }
	 }
}
\references{ The \code{FieldDescriptor} C++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{protobufDescriptor}
}
\examples{
# example proto file supplied with this package
proto.file <- system.file( "examples", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )

# field
Person$email

}
\keyword{classes}
