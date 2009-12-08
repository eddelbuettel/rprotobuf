\name{RpcHTTP-class}
\Rdversion{1.1}
\docType{class}
\alias{RpcHTTP-class}

\title{Class "RpcHTTP" }
\description{Support for protobuf rpc over HTTP}
\section{Objects from the Class}{
Objects can be created by calls of the form 
\code{new("RpcHTTP", host = "somehost", port = port.number)}
}
\section{Slots}{
  \describe{
    \item{\code{host}:}{Host name}
    \item{\code{port}:}{port number}
  }
}
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\link{invoke} uses objects of this class to perform a
	method invocation over http.
}
\keyword{classes}

