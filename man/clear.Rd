\name{clear-methods}
\docType{methods}
\alias{clear}
\alias{clear-methods}
\alias{clear,Message,character-method}
\alias{clear,Message,integer-method}
\alias{clear,Message,missing-method}
\alias{clear,Message,numeric-method}
\alias{clear,Message,raw-method}
\title{Clear a field or all fields of the message and set them to their default values}
\description{
Clear one field or all fields of the message and set them to their default values
}
\section{Methods}{
\describe{
\item{\code{signature(object = "Message", field = "missing")}}{Clear all fields of the message and set them to their default values }
\item{\code{signature(object = "Message", field = "character")}}{ Clear the field identified by its name }
\item{\code{signature(object = "Message", field = "integer")}}{ Clear the field identified by its tag number }
\item{\code{signature(object = "Message", field = "numeric")}}{ Clear the field identified by its tag number }
\item{\code{signature(object = "Message", field = "raw")}}{ Clear the field identified by its tag number}

}}
\keyword{methods}
\examples{
	message <- new( tutorial.Person, name = "dddd", email = "eeeeeee", id = 1 )
	writeLines( as.character( message ) )
	clear( message )
	# clear works also as a pseudo method :
	message$clear() 
	
	writeLines( as.character( message ) )
	
	# clear single fields
	message <- new( tutorial.Person, name = "dddd", email = "eeeeeee", id = 1 )
	message$clear( "name" )
	writeLines( as.character( message ) )
	
}

