\name{FileOutputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{FileOutputStream-class}
\alias{close,FileOutputStream-method}
\alias{flush,FileOutputStream-method}
\alias{GetErrno,FileOutputStream-method}
\alias{SetCloseOnDelete,FileOutputStream-method}

\title{Class "FileOutputStream"  }
\description{A \linkS4class{ZeroCopyOutputStream} reading from a file}
\section{Objects from the Class}{
Objects can be created by the \link{FileOutputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{google::protobuf::io::FileOutputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyOutputStream}"}, directly.
}
\section{Methods}{
	\describe{
		\item{close}{\code{signature(con="FileOutputStream")}: 
			Flushes any buffers and closes the underlying file. 
			Returns false if an error occurs during the process; use \code{GetErrno} to examine the error
		}
		\item{flush}{\code{signature(con="FileOutputStream")}:
			Flushes FileOutputStream's buffers but does not close the underlying file
		}
		\item{GetErrno}{\code{signature(object="FileInputStream")}: 
			If an I/O error has occurred on this file descriptor, this is the errno from that error.
			Otherwise, this is zero. Once an error occurs, the stream is broken and all subsequent operations will fail.
		}
		\item{SetCloseOnDelete}{\code{signature(object="FileOutputStream")}: 
			set the close on delete behavior.
		}
	}
	See \linkS4class{ZeroCopyOutputStream} for inherited methods
}
\references{ The \code{FileOutputStream} class from the protobuf 
C++ library. \url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.io.zero_copy_stream_impl_lite.html#FileOutputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyOutputStream} for methods
}
\keyword{classes}
