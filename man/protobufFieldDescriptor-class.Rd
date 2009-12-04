\name{protobufFieldDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufFieldDescriptor-class}
\alias{show,protobufFieldDescriptor-method}
\alias{$,protobufFieldDescriptor-method}
\alias{as.character,protobufFieldDescriptor-method}
\alias{toString,protobufFieldDescriptor-method}
\alias{containing_type,protobufFieldDescriptor-method}
\alias{is_extension,protobufFieldDescriptor-method}
\alias{number,protobufFieldDescriptor-method}
\alias{type,protobufFieldDescriptor-method}
\alias{cpp_type,protobufFieldDescriptor-method}
\alias{label,protobufFieldDescriptor-method}

\alias{is_required}
\alias{is_optional}
\alias{is_repeated}
\alias{is_required-methods}
\alias{is_optional-methods}
\alias{is_repeated-methods}
\alias{is_required,protobufFieldDescriptor-method}
\alias{is_optional,protobufFieldDescriptor-method}
\alias{is_repeated,protobufFieldDescriptor-method}

\alias{has_default_value}
\alias{has_default_value-methods}
\alias{has_default_value,protobufFieldDescriptor-method}

\alias{default_value}
\alias{default_value-methods}
\alias{default_value,protobufFieldDescriptor-method}

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
    \item{as.character}{\code{signature(x = "protobufFieldDescriptor")}: 
  	  	  returns the debug string of the field descriptor. 
  	  	  This is retrieved by a call to the \code{DebugString}
  	      method of the FieldDescriptor object.  }
  	\item{toString}{\code{signature(x = "protobufFieldDescriptor")}: same as \code{as.character} }
  	\item{$}{\code{signature(x = "protobufFieldDescriptor")}: used to invoke pseudo methods }
    \item{containing_type}{\code{signature(object = "protobufFieldDescriptor")} : returns a \linkS4class{protobufDescriptor} of the message type that contains this field descriptor.}
    \item{is_extension}{\code{signature(object = "protobufFieldDescriptor")} : indicates if this is an extension.}
    \item{number}{\code{signature(object = "protobufFieldDescriptor")} : gets the declared tag number of this field.}
	\item{type}{\code{signature(object = "protobufFieldDescriptor")} : type of this field.}
	\item{cpp_type}{\code{signature(object = "protobufFieldDescriptor")} : c++ type of this field.}
	\item{label}{\code{signature(object = "protobufFieldDescriptor")} : label of this field.}
	\item{is_required}{\code{signature(object = "protobufFieldDescriptor")} : is this field required.}
	\item{is_optional}{\code{signature(object = "protobufFieldDescriptor")} : is this field optional.}
	\item{is_repeated}{\code{signature(object = "protobufFieldDescriptor")} : is this field repeated.}
	\item{has_default_value}{\code{signature(object = "protobufFieldDescriptor")} : indicates if this field has a default value.}
	\item{default_value}{\code{signature(object = "protobufFieldDescriptor")} : the default value of this field.}
  	}
}
\references{ The \code{FieldDescriptor} C++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{protobufDescriptor}
}
\examples{
# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )

# field descriptor object
Person$email

# debug string
as.character( Person$email )

# or as a pseudo method
Person$email$as.character()

}
\keyword{classes}
