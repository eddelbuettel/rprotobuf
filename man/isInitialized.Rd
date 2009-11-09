\name{isInitialized-methods}
\docType{methods}
\alias{isInitialized}
\alias{isInitialized-methods}
\alias{isInitialized,protobufMessage-method}
\title{Indicates if a protocol buffer message is initialized}
\description{
	Indicates if a \linkS4class{protobufMessage} is 
	initialized. A message is initialized if all its 
	required fields are set.
}
\section{Methods}{
\describe{
\item{\code{ signature(object = "protobufMessage")}}{ is the message initialized}
}}
\examples{
message <- new( tutorial.Person, name = "" )
isInitialized( message ) # FALSE (id is not set)
message$isInitialized()  # FALSE

message <- new( tutorial.Person, name = "", id = 2 )
isInitialized( message ) # TRUE
message$isInitialized()  # TRUE

}
\keyword{methods}

