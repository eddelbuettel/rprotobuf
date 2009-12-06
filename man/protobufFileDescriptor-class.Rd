\name{FileDescriptor-class}
\Rdversion{1.1}
\docType{class}
\alias{FileDescriptor-class}
\alias{as.character,FileDescriptor-method}
\alias{toString,FileDescriptor-method}
\alias{$,FileDescriptor-method}
\alias{show,FileDescriptor-method}
\alias{name,FileDescriptor-method}

\title{Class "FileDescriptor"}
\description{Class "FileDescriptor"}
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
		\item{$}{\code{signature(x = "FileDescriptor")}: used to invoke a pseudo method of the 
		file descriptor or get a top level message, enum or service descriptor}
		\item{toString}{\code{signature(x = "FileDescriptor" )} : gets the debug string}
		\item{as.character}{\code{signature(x = "FileDescriptor" )} : gets the debug string}
		\item{show}{\code{signature(x = "FileDescriptor" )} : prints small text}
		\item{name}{\code{signature(object = "FileDescriptor" )} : name of the file}
	}
}
\references{ The \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.descriptor.html#FileDescriptor} }
\author{ Romain Francois <francoisromain@free.fr> }
\keyword{classes}

