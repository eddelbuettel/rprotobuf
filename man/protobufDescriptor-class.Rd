\name{protobufDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufDescriptor-class}
\alias{as.character,protobufDescriptor-method}
\alias{$<-,protobufDescriptor-method}
\alias{$,protobufDescriptor-method}
\alias{new,protobufDescriptor-method}
\alias{show,protobufDescriptor-method}

\title{Class "protobufDescriptor" }
\description{ full descriptive information about a protocol buffer 
message type. This is a thin wrapper around the 
C++ class \code{Descriptor}}
\section{Objects from the Class}{
	Objects are usually created by calls to the \code{\link{P}}
	function.
}
\section{Slots}{
  \describe{
  	\item{\code{pointer}:}{external pointer holding a \code{Descriptor} object }
    \item{\code{type}:}{full name of the corresponding message type}
  }
}
\section{Methods}{
  \describe{
  	  \item{as.character}{\code{signature(x = "protobufDescriptor")}: 
  	  	  returns the debug string of the descriptor. 
  	  	  This is retrieved by a call to the \code{DebugString}
  	      method of the Descriptor object.  }
    \item{$}{\code{signature(x = "protobufDescriptor")}: retrieves a
    descriptor for a member of the message type. This can 
    either be another "protobufDescriptor" instance describing 
    a nested type, or a \linkS4class{protobufEnumDescriptor} object
    describing an enum type, or a \linkS4class{protobufFieldDescriptor}
    object describing a field of the message}
    \item{new}{\code{signature(Class = "protobufDescriptor")}: creates 
    a prototype message (\linkS4class{protobufMessage}) of this 
    descriptor}
    \item{show}{\code{signature(object = "protobufDescriptor")}: 
    simple information}
	 }
}
\references{ The \code{Descriptor} c++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	the \code{\link{P}} function creates "protobufDescriptor" messages. 
}
\examples{

# example proto file supplied with this package
proto.file <- system.file( "examples", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )

# enum type
Person$PhoneType

# nested type
Person$PhoneNumber

# field
Person$email

# use this descriptor to create a message
new( Person )

}
\keyword{classes}
