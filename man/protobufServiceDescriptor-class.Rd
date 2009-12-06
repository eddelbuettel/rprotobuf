\name{ServiceDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{ServiceDescriptor-class}
\alias{as.character,ServiceDescriptor-method}
\alias{toString,ServiceDescriptor-method}
\alias{show,ServiceDescriptor-method}
\alias{$,ServiceDescriptor-method}
\alias{[[,ServiceDescriptor-method}
\alias{length,ServiceDescriptor-method}

\alias{method_count}
\alias{method_count-methods}
\alias{method_count,ServiceDescriptor-method}

\alias{method}
\alias{method-methods}
\alias{method,ServiceDescriptor-method}

\title{Class "ServiceDescriptor"}
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
    \item{as.character}{\code{signature(x = "ServiceDescriptor")}: debug string of the service }
    \item{toString}{\code{signature(x = "ServiceDescriptor")}: debug string of the service}
    \item{show}{\code{signature(x = "ServiceDescriptor")}: ... }
    \item{$}{\code{signature(x = "ServiceDescriptor")}: invoke pseudo methods or retrieve
    	method descriptors contained in this service descriptor. }
	\item{[[}{\code{signature(x = "ServiceDescriptor")}: extracts methods
	descriptors contained in this service descriptor}
	\item{length}{\code{signature(x = "ServiceDescriptor")}: number of \linkS4class{MethodDescriptor} }
	\item{method_count}{\code{signature(x = "ServiceDescriptor")}: number of \linkS4class{MethodDescriptor} }
	\item{method}{\code{signature(x = "ServiceDescriptor")}: retrieveds a \linkS4class{MethodDescriptor} }
	}
}
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}
