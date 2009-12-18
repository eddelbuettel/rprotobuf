\name{ZeroCopyOutputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ZeroCopyOutputStream-class}

\alias{ByteCount,ZeroCopyOutputStream-method}
\alias{BackUp,ZeroCopyOutputStream-method}
\alias{Next,ZeroCopyOutputStream,raw-method}
\alias{$,ZeroCopyOutputStream-method}

\alias{WriteRaw}
\alias{WriteRaw-methods}
\alias{WriteRaw,ZeroCopyOutputStream,raw-method}

\alias{WriteString}
\alias{WriteString-methods}
\alias{WriteString,ZeroCopyOutputStream,character-method}

\alias{WriteLittleEndian32}
\alias{WriteLittleEndian32-methods}
\alias{WriteLittleEndian32,ZeroCopyOutputStream,integer-method}
\alias{WriteLittleEndian32,ZeroCopyOutputStream,numeric-method}
\alias{WriteLittleEndian32,ZeroCopyOutputStream,raw-method}

\alias{WriteLittleEndian64}
\alias{WriteLittleEndian64-methods}
\alias{WriteLittleEndian64,ZeroCopyOutputStream,integer-method}
\alias{WriteLittleEndian64,ZeroCopyOutputStream,numeric-method}
\alias{WriteLittleEndian64,ZeroCopyOutputStream,raw-method}

\alias{WriteVarint32}
\alias{WriteVarint32-methods}
\alias{WriteVarint32,ZeroCopyOutputStream,integer-method}
\alias{WriteVarint32,ZeroCopyOutputStream,numeric-method}
\alias{WriteVarint32,ZeroCopyOutputStream,raw-method}

\alias{WriteVarint64}
\alias{WriteVarint64-methods}
\alias{WriteVarint64,ZeroCopyOutputStream,integer-method}
\alias{WriteVarint64,ZeroCopyOutputStream,numeric-method}
\alias{WriteVarint64,ZeroCopyOutputStream,raw-method}


\title{Virtual Class "ZeroCopyOutputStream" }
\description{R wrapper for the ZeroCopyOutputStream c++ class}
\section{Objects from the Class}{
This is a virtual class
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the \code{google::protobuf::io::ZeroCopyOutputStream} object}
  }
}
\section{Methods}{
\describe{
	\item{$}{\code{signature(x="ZeroCopyOutputStream")}: invokes a method}
	\item{Next}{\code{signature(object="ZeroCopyOutputStream", payload = "raw" )}: push the raw vector into the stream. Returns the number of bytes actually written.}
	\item{BackUp}{\code{signature(object="ZeroCopyOutputStream")}: Backs up a number of bytes, so that the end of the last buffer returned by \code{Next} is not actually written.}
	\item{ByteCount}{\code{signature(object="ZeroCopyOutputStream")}: Returns the total number of bytes written since this object was created. }
	\item{WriteRaw}{\code{signature(object="ZeroCopyOuputStream", payload = "raw"}: write the raw bytes to the stream}
}
}

\author{ Romain Francois <francoisromain@free.fr> }
\references{
	The \code{google::protobuf::io::ZeroCopyOutputStream} C++ class. 
	\url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream.html#ZeroCopyOutputStream}
}
\seealso{
	TODO: add classes that extend
}
\keyword{classes}

