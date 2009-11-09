\name{bytesize-methods}
\docType{methods}
\alias{bytesize}
\alias{bytesize-methods}
\alias{bytesize,protobufMessage-method}
\title{The number of bytes taken by a message }
\description{
The number of bytes taken by a \linkS4class{protobufMessage}
}
\section{Methods}{
\describe{
\item{\code{signature(object = "protobufMessage")}}{ The number of bytes the message would take when serialized }
}}
\keyword{methods}
\examples{
	message <- new( tutorial.Person, name = "dddd", email = "eeeeeee", id = 1 )
	bytesize( message )
	\dontshow{
		stopifnot( identical( bytesize(message), length(serialize(message, NULL ) ) ) )
	}
}

