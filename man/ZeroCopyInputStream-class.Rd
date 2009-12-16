\name{ZeroCopyInputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ZeroCopyInputStream-class}

\alias{Skip,ZeroCopyInputStream-method}
\alias{ByteCount,ZeroCopyInputStream-method}
\alias{BackUp,ZeroCopyInputStream-method}
\alias{Next,ZeroCopyInputStream,missing-method}
\alias{$,ZeroCopyInputStream-method}

\alias{ReadRaw}
\alias{ReadRaw-methods}
\alias{ReadRaw,ZeroCopyInputStream,integer-method}

\alias{ReadString}
\alias{ReadString-methods}
\alias{ReadString,ZeroCopyInputStream,integer-method}

\alias{ReadVarint32}
\alias{ReadVarint32-methods}
\alias{ReadVarint32,ZeroCopyInputStream-method}

\alias{ReadLittleEndian32}
\alias{ReadLittleEndian32-methods}
\alias{ReadLittleEndian32,ZeroCopyInputStream-method}
\alias{ReadLittleEndian64}
\alias{ReadLittleEndian64-methods}
\alias{ReadLittleEndian64,ZeroCopyInputStream-method}


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
	\item{$}{\code{signature(x="ZeroCopyInputStream")}: invokes a method}
	\item{Next}{\code{signature(object="ZeroCopyInputStream")}: Get a number of bytes from the stream as a raw vector. }
	\item{Skip}{\code{signature(object="ZeroCopyInputStream")}: skip a number of bytes}
	\item{BackUp}{\code{signature(object="ZeroCopyInputStream")}: Backs up a number of bytes, so that the next call to \code{Next} returns data again that was already returned by the last call to \code{Next}.}
	\item{ByteCount}{\code{signature(object="ZeroCopyInputStream")}: Returns the total number of bytes read since this object was created. }
	\item{ReadRaw}{\code{signature(object="ZeroCopyInputStream", size = "integer")}: read raw bytes from the stream}
	\item{ReadString}{\code{signature(object="ZeroCopyInputStream", size = "integer")}: same as \code{ReadRaw} but formats the result as a string}
	\item{ReadVarint32}{\code{signature(object="ZeroCopyInputStream")}: Read an unsigned integer with Varint encoding, truncating to 32 bits. }
	\item{ReadLittleEndian32}{\code{signature(object="ZeroCopyInputStream")}: Read a 32-bit little-endian integer.  }
	\item{ReadLittleEndian64}{\code{signature(object="ZeroCopyInputStream")}: Read a 64-bit little-endian integer. In R the value is stored as a \code{double} which looses some precision (no other way) }
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

