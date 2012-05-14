\name{EnumValueDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{EnumValueDescriptor-class}
\alias{show,EnumValueDescriptor-method}
\alias{as.character,EnumValueDescriptor-method}
\alias{toString,EnumValueDescriptor-method}
\alias{$,EnumValueDescriptor-method}
\alias{name,EnumValueDescriptor-method}
\alias{enum_type,EnumValueDescriptor,missing,missing-method}

\title{Class "EnumValueDescriptor"  }
\description{ R representation of an enum value descriptor. This 
  is a thin wrapper around the \code{EnumValueDescriptor} c++ class. }
\section{Objects from the Class}{
  Objects of this class are typically retrieved with the 
  \code{value} method of the \linkS4class{EnumDescriptor} class
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{EnumValueDescriptor} instance}
  	  \item{\code{name}:}{ simple name of the enum }
  	  \item{\code{full_name}:}{fully qualified name }
  }
}
\section{Methods}{
  \describe{
    \item{show}{\code{signature(object = "EnumValueDescriptor")}: small information }
    \item{as.character}{\code{signature(x = "EnumValueDescriptor")}: 
      returns the debug string of the enum descriptor. 
      This is retrieved by a call to the \code{DebugString}
      method of the EnumDescriptor object.  }
    \item{toString}{\code{signature(x = "EnumValueDescriptor")}: same as \code{as.character} }
    \item{$}{\code{signature(x = "EnumValueDescriptor")}: invoke pseudo methods }
    \item{enum_type}{\code{signature(object = "EnumDescriptor")} : retrieves the \linkS4class{EnumDescriptor} related to this value descriptor.}
  }
  	
}
\references{ The \code{EnumValueDescriptor} C++ class. 
  \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.descriptor.html#EnumValueDescriptor} }
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
