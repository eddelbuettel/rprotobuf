\name{FileInputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{FileInputStream-class}
\alias{close,FileInputStream-method}
\alias{GetErrno,FileInputStream-method}
\alias{SetCloseOnDelete,FileInputStream-method}

\title{Class "FileInputStream"  }
\description{A \linkS4class{ZeroCopyInputStream} reading from a file}
\section{Objects from the Class}{
Objects can be created by the \link{FileInputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{google::protobuf::io::FileInputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyInputStream}"}, directly.
}
\section{Methods}{
	\describe{
		\item{close}{\code{signature(con="FileInputStream")}: 
			Flushes any buffers and closes the underlying file. 
			Returns false if an error occurs during the process; use \code{GetErrno} to examine the error
		}
		\item{GetErrno}{\code{signature(object="FileInputStream")}: 
			If an I/O error has occurred on this file descriptor, this is the errno from that error.
			Otherwise, this is zero. Once an error occurs, the stream is broken and all subsequent operations will fail.
		}
		\item{SetCloseOnDelete}{\code{signature(object="FileInputStream")}: 
			set the close on delete behavior.
		}
	}
	See \linkS4class{ZeroCopyInputStream} for inherited methods
}
\references{ The \code{FileInputStream} class from the protobuf 
C++ library. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream_impl_lite.html#FileInputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyInputStream} for methods
}
\keyword{classes}
