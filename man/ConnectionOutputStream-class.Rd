\name{ConnectionOutputStream-class}
\Rdversion{1.1}
\docType{class}
\alias{ConnectionOutputStream-class}

\title{Class "ConnectionOutputStream"  }
\description{A \linkS4class{ZeroCopyOutputStream} writing to a binary R connection}
\section{Objects from the Class}{
Objects can be created by the \link{ConnectionOutputStream} function 
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{ External pointer to the \code{rprotobuf::ConnectionOutputStream} C++ object}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ZeroCopyOutputStream}"}, directly.
}
\section{Methods}{
See \linkS4class{ZeroCopyOutputStream}
}
\references{ The internal C++ class \code{ConnectionOutputStream} }
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\linkS4class{ZeroCopyOutputStream} for methods
}
\keyword{classes}

