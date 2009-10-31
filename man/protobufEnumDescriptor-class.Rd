\name{protobufEnumDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufEnumDescriptor-class}
\alias{show,protobufEnumDescriptor-method}

\title{Class "protobufEnumDescriptor"  }
\description{ R representation of an enum descriptor. This 
is a thin wrapper around the \code{EnumDescriptor} c++ class. }
\section{Objects from the Class}{
Objects of this class are typically retrieved as members of 
\linkS4class{protobufDescriptor} objects
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{EnumDescriptor} instance}
  	  \item{\code{name}:}{ simple name of the enum }
  	  \item{\code{full_name}:}{fully qualified name }
  	  \item{\code{type}:}{fully qualified name of the type that contains this enumeration}
  }
}
\section{Methods}{
  \describe{
    \item{show}{\code{signature(object = "protobufEnumDescriptor")}: small information }
	 }
}
\references{ The \code{EnumDescriptor} C++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{The \linkS4class{protobufDescriptor} class}
\examples{

# example proto file supplied with this package
proto.file <- system.file( "examples", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )

# enum type
Person$PhoneType

}
\keyword{classes}
