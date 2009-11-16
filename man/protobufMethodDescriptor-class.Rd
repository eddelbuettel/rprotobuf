\name{protobufServiceDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufServiceDescriptor-class}
\alias{as.character,protobufServiceDescriptor-method}
\alias{toString,protobufServiceDescriptor-method}

\title{Class "protobufServiceDescriptor"}
\description{R representation of Service Descriptors}
\section{Objects from the Class}{
TODO 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{External pointer to a \code{google::protobuf::ServiceDescriptor} C++ object }
  	  \item{\code{name}:}{fully qualified name of the service }
  }
}
\section{Methods}{
  \describe{
    \item{as.character}{\code{signature(x = "protobufServiceDescriptor")}: debug string of the service }
    \item{toString}{\code{signature(x = "protobufServiceDescriptor")}: debug string of the service}
	 }
}
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
