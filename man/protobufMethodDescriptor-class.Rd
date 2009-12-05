\name{protobufMethodDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufMethodDescriptor-class}
\alias{as.character,protobufMethodDescriptor-method}
\alias{toString,protobufMethodDescriptor-method}
\alias{$,protobufMethodDescriptor-method}
\alias{$<-,protobufMethodDescriptor-method}

\alias{input_type}
\alias{input_type-methods}
\alias{input_type,protobufMethodDescriptor-method}

\alias{output_type}
\alias{output_type-methods}
\alias{output_type,protobufMethodDescriptor-method}

\title{Class "protobufMethodDescriptor"}
\description{R representation of Service Descriptors}
\section{Objects from the Class}{
TODO
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{External pointer to a \code{google::protobuf::MethodDescriptor} C++ object }
  	  \item{\code{name}:}{fully qualified name of the method}
  	  \item{\code{service}:}{fully qualified name of the servive that defines this method}
  }
}
\section{Methods}{
  \describe{
    \item{as.character}{\code{signature(x = "protobufMethodDescriptor")}: debug string of the method }
    \item{toString}{\code{signature(x = "protobufMethodDescriptor")}: debug string of the method}
	\item{$}{\code{signature(x = "protobufMethodDescriptor")}: ... }
	\item{$<-}{\code{signature(x = "protobufMethodDescriptor")}: ... }
	\item{input_type}{\code{signature(object = "protobufMethodDescriptor")}: the \linkS4class{protobufDescriptor} of the input type of the method}
	\item{output_type}{\code{signature(object = "protobufMethodDescriptor")}: the \linkS4class{protobufDescriptor} of the output type of the method }
  }
}
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
