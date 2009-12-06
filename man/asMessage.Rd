\name{asMessage}
\alias{asMessage}
\title{
coerce an object to a protobuf message
}
\description{
	coerce an object to the \linkS4class{Message} class. 
	This is a short-hand to the \link{as} method with the 
	\code{Class} argument set to "Message"
}
\usage{
asMessage(x, ...)
}
\arguments{
  \item{x}{object to coerce to a protobuf message}
  \item{\dots}{Passed to \code{\link{as}} }
}
\value{
	a \linkS4class{Message} object
}
\author{
Romain Francois <francoisromain@free.fr>
}
\examples{
# coerce a message type descriptor to a message
asMessage( tutorial.Person )

# coerce a enum descriptor
asMessage( tutorial.Person.PhoneType )

# coerce a field descriptor
asMessage( tutorial.Person$email )

# coerce a file descriptor 
asMessage( fileDescriptor( tutorial.Person ) )
}
\keyword{ programming }
