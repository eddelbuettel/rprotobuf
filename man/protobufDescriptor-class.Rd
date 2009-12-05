\name{protobufDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufDescriptor-class}
\alias{as.character,protobufDescriptor-method}
\alias{$<-,protobufDescriptor-method}
\alias{$,protobufDescriptor-method}
\alias{new,protobufDescriptor-method}
\alias{show,protobufDescriptor-method}
\alias{toString,protobufDescriptor-method}
\alias{containing_type,protobufDescriptor-method}
\alias{field_count,protobufDescriptor-method}
\alias{nested_type_count,protobufDescriptor-method}
\alias{enum_type_count,protobufDescriptor-method}
\alias{field,protobufDescriptor-method}
\alias{nested_type,protobufDescriptor-method}
\alias{enum_type,protobufDescriptor,ANY,ANY-method}

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
  	\item{toString}{\code{signature(x = "protobufDescriptor")}: same as \code{as.character} }
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
    \item{containing_type}{\code{signature(object = "protobufDescriptor")} : returns a descriptor of the message type that contains this message descriptor, or \code{NULL} if this is a top-level message type.}
	\item{field_count}{\code{signature(object = "protobufDescriptor")} : The number of fields of this message type. }
	\item{nested_type_count}{\code{signature(object = "protobufDescriptor")} : The number of nested types of this message type. }
	\item{enum_type_count}{\code{signature(object = "protobufDescriptor")} : The number of enum types of this message type. }
	\item{field}{\code{signature(object = "protobufDescriptor")} : extract a field descriptor from a descriptor. 
		Exactly one argument of \code{index}, \code{number} or \code{name} has to be used. 
		If \code{index} is used, the field descriptor is retrieved by 
		position, using the \code{field} method of the \code{google::protobuf::Descriptor} C++ class. 
		If \code{number} is used, the field descriptor is retrieved using 
		the tag number, with the \code{FindFieldByNumber} C++ method. 
		If \code{name} is used, the field descriptor is retrieved by name
		using the \code{FindFieldByName}
	}
	\item{nested_type}{\code{signature(object = "protobufDescriptor")} : 
			extracts a message type descriptor that is nested
			in this descriptor. 
			Exactly one argument of \code{index} of \code{name} has to be used. 
			If \code{index} is used, the nested type will be retrieved
			using its position with the \code{nested_type} method
			of the \code{google::protobuf::Descriptor} C++ class. 
			If \code{name} is used, the nested type will be retrieved
			using its name, with the \code{FindNestedTypeByName} C++ method
	}
	\item{enum_type}{\code{signature(object = "protobufDescriptor")} : 
			extracts an enum type descriptor that is contained
			in this descriptor. 
			Exactly one argument of \code{index} of \code{name} has to be used. 
			If \code{index} is used, the enum type will be retrieved
			using its position with the \code{enum_type} method
			of the \code{google::protobuf::Descriptor} C++ class. 
			If \code{name} is used, the enum type will be retrieved
			using its name, with the \code{FindEnumTypeByName} C++ method
	}

  }
}
\references{ The \code{Descriptor} c++ class. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.descriptor.html#Descriptor} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	the \code{\link{P}} function creates "protobufDescriptor" messages. 
}
\examples{

# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 

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
