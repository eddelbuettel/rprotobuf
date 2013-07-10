\name{FieldDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{FieldDescriptor-class}
\alias{show,FieldDescriptor-method}
\alias{$,FieldDescriptor-method}
\alias{as.character,FieldDescriptor-method}
\alias{toString,FieldDescriptor-method}
\alias{containing_type,FieldDescriptor-method}
\alias{is_extension,FieldDescriptor-method}
\alias{number,FieldDescriptor-method}
\alias{type,FieldDescriptor-method}
\alias{cpp_type,FieldDescriptor-method}
\alias{label,FieldDescriptor-method}

\alias{is_required}
\alias{is_optional}
\alias{is_repeated}
\alias{is_required-methods}
\alias{is_optional-methods}
\alias{is_repeated-methods}
\alias{is_required,FieldDescriptor-method}
\alias{is_optional,FieldDescriptor-method}
\alias{is_repeated,FieldDescriptor-method}

\alias{has_default_value}
\alias{has_default_value-methods}
\alias{has_default_value,FieldDescriptor-method}

\alias{default_value}
\alias{default_value-methods}
\alias{default_value,FieldDescriptor-method}

\alias{message_type}
\alias{message_type-methods}
\alias{message_type,FieldDescriptor-method}

\alias{enum_type,FieldDescriptor,missing,missing-method}


\title{Class "FieldDescriptor"}
\description{R representation of message type field descriptor. 
This is a thin wrapper around the C++ class \code{FieldDescriptor} }
\section{Objects from the Class}{
Objects typically are retrieved from \linkS4class{FieldDescriptor}
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
    \item{show}{\code{signature(object = "FieldDescriptor")}: small description }
    \item{as.character}{\code{signature(x = "FieldDescriptor")}: 
  	  	  returns the debug string of the field descriptor. 
  	  	  This is retrieved by a call to the \code{DebugString}
  	      method of the FieldDescriptor object.  }
  	\item{toString}{\code{signature(x = "FieldDescriptor")}: same as \code{as.character} }
  	\item{$}{\code{signature(x = "FieldDescriptor")}: used to invoke pseudo methods }
    \item{containing_type}{\code{signature(object = "FieldDescriptor")} : returns a \linkS4class{Descriptor} of the message type that contains this field descriptor.}
    \item{is_extension}{\code{signature(object = "FieldDescriptor")} : indicates if this is an extension.}
    \item{number}{\code{signature(object = "FieldDescriptor")} : gets the declared tag number of this field.}
	\item{type}{\code{signature(object = "FieldDescriptor")} : type of this field.}
	\item{cpp_type}{\code{signature(object = "FieldDescriptor")} : c++ type of this field.}
	\item{label}{\code{signature(object = "FieldDescriptor")} : label of this field.}
	\item{is_required}{\code{signature(object = "FieldDescriptor")} : is this field required.}
	\item{is_optional}{\code{signature(object = "FieldDescriptor")} : is this field optional.}
	\item{is_repeated}{\code{signature(object = "FieldDescriptor")} : is this field repeated.}
	\item{has_default_value}{\code{signature(object = "FieldDescriptor")} : indicates if this field has a default value.}
	\item{default_value}{\code{signature(object = "FieldDescriptor")} : the default value of this field.}
	\item{message_type}{\code{signature(object = "FieldDescriptor")} : the \linkS4class{Descriptor} for the associated message type. Generates an error if this field is not a message type field.}
	\item{enum_type}{\code{signature(object = "FieldDescriptor")} : the \linkS4class{EnumDescriptor} for the associated enum type.Generates an error if this field is not an enum type field }
  	}
}
\references{ The \code{FieldDescriptor} C++ class }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{Descriptor}
}
\examples{
\dontrun{
# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )
}
\dontshow{Person <- P("tutorial.Person") }

# field descriptor object
Person$email

# debug string
as.character( Person$email )

# or as a pseudo method
Person$email$as.character()

Person$email$is_required()
Person$email$is_optional()
Person$email$is_repeated()

Person$email$has_default_value()
Person$email$default_value()

Person$email$is_extension()

# Get the default values
has_default_value(Person$id)
has_default_value(Person$email)
has_default_value(Person$phone)
default_value(Person$id)
default_value(Person$email)
default_value(Person$phone)

# Get the types of field descriptors
type(Person$id)
type(Person$id, as.string=TRUE)
cpp_type(Person$email)
cpp_type(Person$email, TRUE)

# Get the label of a field descriptor
label(Person$id)
label(Person$email)
label(Person$phone)
label(Person$id, TRUE)
label(Person$email, TRUE)
label(Person$phone, TRUE)
LABEL_OPTIONAL
LABEL_REQUIRED
LABEL_REPEATED

# Test if a field is optional
is_optional(Person$id)
is_optional(Person$email)
is_optional(Person$phone)

# Test if a field is repeated
is_repeated(Person$id)
is_repeated(Person$email)
is_repeated(Person$phone)

# Test if a field is required
is_required(Person$id)
is_required(Person$email)
is_required(Person$phone)

# Return the class of a message field
message_type(Person$phone)
}
\keyword{classes}
