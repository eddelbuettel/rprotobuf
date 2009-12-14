\name{ArrayOutputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ArrayOutputStream-class}

\title{Class "ArrayOutputStream"  }
\description{A \linkS4class{ZeroCopyOutputStream} backed by an in-memory array of bytes}
\section{Objects from the Class}{
Objects can be created by the \link{ArrayOutputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{google::protobuf::io::ArrayOutputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyOutputStream}"}, directly.
}
\section{Methods}{
See \linkS4class{ZeroCopyOutputStream}
}
\references{ The \code{ArrayOutputStream} class from the protobuf 
C++ library. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream_impl_lite.html#ArrayOutputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyOutputStream} for methods
}
\keyword{classes}
