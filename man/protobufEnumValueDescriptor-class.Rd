\name{protobufEnumValueDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufEnumValueDescriptor-class}
\alias{show,protobufEnumValueDescriptor-method}
\alias{as.character,protobufEnumValueDescriptor-method}
\alias{toString,protobufEnumValueDescriptor-method}
\alias{$,protobufEnumValueDescriptor-method}

\title{Class "protobufEnumValueDescriptor"  }
\description{ R representation of an enum value descriptor. This 
is a thin wrapper around the \code{EnumValueDescriptor} c++ class. }
\section{Objects from the Class}{
Objects of this class are typically retrieved with the 
\code{value} method of the \linkS4class{protobufEnumDescriptor} class
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{EnumValueDescriptor} instance}
  }
}
\section{Methods}{
  \describe{
    \item{show}{\code{signature(object = "protobufEnumValueDescriptor")}: small information }
    \item{as.character}{\code{signature(x = "protobufEnumValueDescriptor")}: 
  	  	  returns the debug string of the enum descriptor. 
  	  	  This is retrieved by a call to the \code{DebugString}
  	      method of the EnumDescriptor object.  }
  	\item{toString}{\code{signature(x = "protobufEnumValueDescriptor")}: same as \code{as.character} }
  	\item{$}{\code{signature(x = "protobufEnumValueDescriptor")}: invoke pseudo methods }
  }
  	
}
\references{ The \code{EnumValueDescriptor} C++ class. 
	\url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.descriptor.html#EnumValueDescriptor} }
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
