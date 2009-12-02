\name{fileDescriptor-methods}
\docType{methods}
\alias{fileDescriptor}
\alias{fileDescriptor-methods}
\alias{fileDescriptor,protobufDescriptor-method}
\alias{fileDescriptor,protobufMessage-method}
\alias{fileDescriptor,protobufEnumDescriptor-method}
\alias{fileDescriptor,protobufFieldDescriptor-method}
\alias{fileDescriptor,protobufServiceDescriptor-method}
\alias{fileDescriptor,protobufMethodDescriptor-method}

\title{gets the file descriptor of an object}
\description{
Gets the file descriptor of an object
}
\section{Methods}{
\describe{
\item{\code{signature(object = "protobufDescriptor")}}{ retrieves the file descriptor associated with this descriptor}
\item{\code{signature(object = "protobufMessage")}}{ retrieves the file descriptor associated with the descriptor of this message }
\item{\code{signature(object = "protobufEnumDescriptor")}}{ retrieves the file descriptor associated with the enum descriptor }
\item{\code{signature(object = "protobufFieldDescriptor")}}{ retrieves the file descriptor associated with the field descriptor }
\item{\code{signature(object = "protobufServiceDescriptor")}}{ retrieves the file descriptor associated with the service descriptor }
\item{\code{signature(object = "protobufMethodDescriptor")}}{ retrieves the file descriptor associated with the method descriptor }
}}
\keyword{methods}

