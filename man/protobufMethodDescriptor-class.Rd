\name{MethodDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{MethodDescriptor-class}
\alias{as.character,MethodDescriptor-method}
\alias{toString,MethodDescriptor-method}
\alias{$,MethodDescriptor-method}
\alias{$<-,MethodDescriptor-method}

\alias{input_type}
\alias{input_type-methods}
\alias{input_type,MethodDescriptor-method}

\alias{output_type}
\alias{output_type-methods}
\alias{output_type,MethodDescriptor-method}

\title{Class "MethodDescriptor"}
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
    \item{as.character}{\code{signature(x = "MethodDescriptor")}: debug string of the method }
    \item{toString}{\code{signature(x = "MethodDescriptor")}: debug string of the method}
	\item{$}{\code{signature(x = "MethodDescriptor")}: ... }
	\item{$<-}{\code{signature(x = "MethodDescriptor")}: ... }
	\item{input_type}{\code{signature(object = "MethodDescriptor")}: the \linkS4class{Descriptor} of the input type of the method}
	\item{output_type}{\code{signature(object = "MethodDescriptor")}: the \linkS4class{Descriptor} of the output type of the method }
  }
}
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
