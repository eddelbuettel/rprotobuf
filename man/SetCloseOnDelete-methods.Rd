\name{SetCloseOnDelete-methods}
\docType{methods}
\alias{SetCloseOnDelete}
\alias{SetCloseOnDelete-methods}
\title{set the close on delete behavior}
\description{
By default, the file descriptor is not closed when a stream is destroyed, 
use \code{SetCloseOnDelete( stream, TRUE ) } to change that.
}
\section{Methods}{
	See classes \linkS4class{FileInputStream} and 
	\linkS4class{FileOutputStream} for implementations.
}
\keyword{methods}

