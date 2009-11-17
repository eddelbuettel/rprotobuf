\name{protobufMethodDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufMethodDescriptor-class}
\alias{as.character,protobufMethodDescriptor-method}
\alias{toString,protobufMethodDescriptor-method}
\alias{$,protobufMethodDescriptor-method}
\alias{$<-,protobufMethodDescriptor-method}

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
  }
}
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
