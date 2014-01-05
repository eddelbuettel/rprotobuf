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
C++ library. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream_impl_lite.html#ArrayInputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyInputStream} for methods
}
\examples{
stream <- ArrayInputStream(as.raw(0:10))
stream$ReadRaw(5)

stringsstream <- ArrayInputStream(as.raw(c(0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67)))
stringsstream$ReadString(7)

intstream <- ArrayInputStream(as.raw(c(0x9e, 0xa7, 0x05)))
intstream$ReadVarint32()
}
% local({
% 	stream <- ArrayInputStream( as.raw(0:10) )
% 	stopifnot( identical( stream$Next(), as.raw(0:10) ) )
% 	stream$BackUp( 5 )
% 	stopifnot( identical( stream$Next(), as.raw(6:10) ) )
%
% 	# limiting the block size
% 	stream <- ArrayInputStream( as.raw(0:10), 5 )
% 	stopifnot( identical(length( stream$Next() ), 5L ) )
% })
\keyword{classes}
