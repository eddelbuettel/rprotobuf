\name{protobufFileDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufFileDescriptor-class}
\alias{as.character,protobufFileDescriptor-method}
\alias{toString,protobufFileDescriptor-method}
\alias{$,protobufFileDescriptor-method}
\alias{show,protobufFileDescriptor-method}
\alias{name,protobufFileDescriptor-method}

\title{Class "protobufFileDescriptor"}
\description{Class "protobufFileDescriptor"}
\section{Objects from the Class}{
Objects are usually created using the \code{\link{fileDescriptor}} method
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to a \code{google::protobuf::FileDescriptor} C++ object }
  }
}
\section{Methods}{
	\describe{
		\item{$}{\code{signature(x = "protobufFileDescriptor")}: used to invoke a pseudo method of the 
		file descriptor or get a top level message, enum or service descriptor}
		\item{toString}{\code{signature(x = "protobufFileDescriptor" )} : gets the debug string}
		\item{as.character}{\code{signature(x = "protobufFileDescriptor" )} : gets the debug string}
		\item{show}{\code{signature(x = "protobufFileDescriptor" )} : prints small text}
		\item{name}{\code{signature(object = "protobufFileDescriptor" )} : name of the file}
	}
}
\references{ The \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.descriptor.html#FileDescriptor} }
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}

