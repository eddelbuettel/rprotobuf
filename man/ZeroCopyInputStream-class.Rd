\name{ZeroCopyInputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ZeroCopyInputStream-class}

\alias{Skip,ZeroCopyInputStream-method}
\alias{ByteCount,ZeroCopyInputStream-method}
\alias{BackUp,ZeroCopyInputStream-method}
\alias{Next,ZeroCopyInputStream,missing-method}
\alias{$,ZeroCopyInputStream-method}

\title{Virtual Class "ZeroCopyInputStream" }
\description{R wrapper for the ZeroCopyInputStream c++ class}
\section{Objects from the Class}{
This is a virtual class
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{google::protobuf::io::ZeroCopyInputStream} object}
  }
}
\section{Methods}{
\describe{
	\item{Next}{\code{signature(object="ZeroCopyInputStream")}: Get a number of bytes from the stream as a raw vector. }
	\item{Skip}{\code{signature(object="ZeroCopyInputStream")}: skip a number of bytes}
	\item{BackUp}{\code{signature(object="ZeroCopyInputStream")}: Backs up a number of bytes, so that the next call to \code{Next} returns data again that was already returned by the last call to \code{Next}.}
	\item{ByteCount}{\code{signature(object="ZeroCopyInputStream")}: Returns the total number of bytes read since this object was created. }
	\item{$}{\code{signature(x="ZeroCopyInputStream")}: invokes a method}
}
}

\author{ Romain Francois <francoisromain@free.fr> }
\references{
	The \code{google::protobuf::io::ZeroCopyInputStream} C++ class. 
	\url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream.html#ZeroCopyInputStream}
}
\seealso{
	TODO: add classes that extend
}
\keyword{classes}

