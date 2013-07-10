\name{with.Message}
\alias{with.Message}
\alias{within.Message}
\title{
with and within methods for protocol buffer messages
}
\description{
Convenience wrapper that allow getting and setting 
fields of protocol buffer messages from within the object
}
\usage{
\S3method{with}{Message}(data, expr, ...)
\S3method{within}{Message}(data, expr, ...)
}
\arguments{
	\item{data}{A protocol buffer message, instance of \linkS4class{Message} }
	\item{expr}{R expression to evaluate}
	\item{\dots}{ignored}
}
\details{
The expression is evaluated in an environment 
that allows to set and get fields of the message

The fields of the message are mapped to active bindings
(see \link{makeActiveBinding}) so that they can be accessed
and modified from within the environment. 
}
\value{
	\code{with} returns the value of the expression and 
	\code{within} returns the \code{data} argument.
}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
\dontrun{
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 
Person <- P( "tutorial.Person", file = proto.file )
}
\dontshow{Person <- P( "tutorial.Person") }
romain <- within( new( Person ), {
	email <- "francoisromain@free.fr"
	id <- 10L
} )
}
\keyword{ classes }
