\name{throw}
\alias{throw}
\title{
protobuf errors
}
\description{
Errors that occur within the internal code of the 
RProtoBuf package are special conditions with at least 
classes "ProtobufError", "error", "condition" and possibly 
other sub classes. 

This allows for direct handlers in \code{tryCatch}
}
\usage{
throw(message = "protobuf error", class = NULL)
}
\arguments{
  \item{message}{message of the condition}
  \item{class}{optional set of sub classes}
}
\value{
This does not return. It creates a condition that eventually 
is sent to \code{stop}
}
\author{
Romain Francois <francoisromain@free.fr>
}
\keyword{ programming }
