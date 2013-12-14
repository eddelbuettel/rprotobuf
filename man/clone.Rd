\name{clone-methods}
\docType{methods}
\alias{clone}
\alias{clone-methods}
\alias{clone,Message-method}
\title{Clone protocol buffer messages}
\description{
Generic "clone" function and associated 
method for \linkS4class{Message} objects 
}
\section{Methods}{
\describe{
	\item{\code{signature(object = "Message")}}{ clone the message }
}}
\examples{
\dontrun{
# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" )

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )
}
\dontshow{Person <- P("tutorial.Person")}

# creating a prototype message from the descriptor
sheep <- new( Person, email = "francoisromain@free.fr", id = 2 )

# cloning the sheep
newsheep <- clone( sheep )

# clone and update at once
newsheep <- clone( sheep, id = 3 )

# this can also be used as a pseudo method
sheep$clone()
sheep$clone( id = 3 )
}
\keyword{methods}

