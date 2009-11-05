\name{merge-methods}
\alias{merge,protobufMessage,protobufMessage-method}
\title{Merge two messages of the same type}
\description{
	Merge two \linkS4class{protobufMessage} objects
	of the same type.
}
\section{Methods}{
\describe{
	\item{\code{signature(x = "protobufMessage", y = "protobufMessage")}}{ merge two messages of the same type }
}}
\section{Errors}{
	An error of class "IncompatibleType" is thrown if 
	the two messages are not of the same message type.
}
\keyword{methods}
\examples{

m1 <- new( tutorial.Person, email = "francoisromain@free.fr" )
m2 <- new( tutorial.Person, id = 5 )
m3 <- merge( m1, m2 )
writeLines( as.character( m1 ) )
writeLines( as.character( m2 ) )
writeLines( as.character( m3 ) )

}
