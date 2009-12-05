\name{protobufEnumDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufEnumDescriptor-class}
\alias{show,protobufEnumDescriptor-method}
\alias{as.character,protobufEnumDescriptor-method}
\alias{toString,protobufEnumDescriptor-method}
\alias{$,protobufEnumDescriptor-method}
\alias{containing_type,protobufEnumDescriptor-method}
\alias{length,protobufEnumDescriptor-method}

\alias{value_count}
\alias{value_count-methods}
\alias{value_count,protobufEnumDescriptor-method}

\alias{value}
\alias{value-methods}
\alias{value,protobufEnumDescriptor-method}

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
    \item{as.character}{\code{signature(x = "protobufEnumDescriptor")}: 
  	  	  returns the debug string of the enum descriptor. 
  	  	  This is retrieved by a call to the \code{DebugString}
  	      method of the EnumDescriptor object.  }
  	\item{toString}{\code{signature(x = "protobufEnumDescriptor")}: same as \code{as.character} }
  	\item{$}{\code{signature(x = "protobufEnumDescriptor")}: get the 
  	number associated with the name}
  	\item{containing_type}{\code{signature(object = "protobufEnumDescriptor")} : returns a \linkS4class{protobufDescriptor} of the message type that contains this enum descriptor, or NULL if this is a top level enum descriptor.}
  	\item{length}{\code{signature(x = "protobufEnumDescriptor")} : number of constants in this enum.}
  	\item{value_count}{\code{signature(object = "protobufEnumDescriptor")} : number of constants in this enum.}
  	\item{value}{\code{signature(object = "protobufEnumDescriptor")} : extracts an \linkS4class{protobufEnumValueDescriptor}.
  		Exactly one argument of \code{index}, \code{number} or \code{name} has to be 
  		used. 
  		If \code{index} is used, the enum value descriptor is retrieved
  		by position, using the \code{value} method of the C++ class. 
  		If \code{number} is used, the enum value descripror is retrieved
  		using the value of the constant, using the \code{FindValueByNumber}
  		C++ method. 
  		If \code{name} is used, the enum value descriptor is retrieved
  		using the name of the constant, using the \code{FindValueByName}
  		C++ method.
  	}
  }
  	
}
\references{ The \code{EnumDescriptor} C++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{The \linkS4class{protobufDescriptor} class}
\examples{

# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )

# enum type
Person$PhoneType

}
\keyword{classes}
