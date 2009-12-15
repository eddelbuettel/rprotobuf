\name{ConnectionInputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ConnectionInputStream-class}

\title{Class "ConnectionInputStream"  }
\description{A \linkS4class{ZeroCopyInputStream} reading from a binary R connection}
\section{Objects from the Class}{
Objects can be created by the \link{ConnectionInputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{rprotobuf::ConnectionInputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyInputStream}"}, directly.
}
\section{Methods}{
See \linkS4class{ZeroCopyInputStream}
}
\references{ The internal C++ class \code{ConnectionInputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyInputStream} for methods
}
\keyword{classes}

