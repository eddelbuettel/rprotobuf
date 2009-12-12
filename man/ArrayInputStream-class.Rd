\name{ArrayInputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ArrayInputStream-class}

\title{Class "ArrayInputStream"  }
\description{A \linkS4class{ZeroCopyInputStream} backed by an in-memory array of bytes}
\section{Objects from the Class}{
Objects can be created by the \link{ArrayInputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{google::protobuf::io::ArrayInputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyInputStream}"}, directly.
}
\section{Methods}{
See \linkS4class{ZeroCopyInputStream}
}
\references{ The \code{ArrayInputStream} class from the protobuf 
C++ librray. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream_impl_lite.html#ArrayInputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyInputStream} for methods
}
\examples{
local({
	stream <- ArrayInputStream( as.raw(0:10) )
	stopifnot( identical( stream$Next(), as.raw(0:10) ) )
	stream$BackUp( 5 )
	stopifnot( identical( stream$Next(), as.raw(6:10) ) )
})

}
\keyword{classes}
