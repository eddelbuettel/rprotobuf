\name{clear-methods}
\docType{methods}
\alias{clear}
\alias{clear-methods}
\alias{clear,protobufMessage-method}
\title{Clear all fields of the message and set them to their default values}
\description{
Clear all fields of the message and set them to their default values
}
\section{Methods}{
\describe{
\item{\code{signature(object = "protobufMessage")}}{ Clear all fields of the message and set them to their default values }
}}
\keyword{methods}
\examples{
	message <- new( tutorial.Person, name = "dddd", email = "eeeeeee", id = 1 )
	writeLines( as.character( message ) )
	clear( message )
	# clear works also as a pseudo method :
	message$clear() 
	
	writeLines( as.character( message ) )
	
}

