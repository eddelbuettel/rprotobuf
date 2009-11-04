\name{has-methods}
\docType{methods}
\alias{has}
\alias{has-methods}
\alias{has,protobufMessage-method}

\title{Indicates if a message has the given field set}
\description{
This generic method, currently only implemented
for \linkS4class{protobufMessage} indicates if the message
has the given field set. 

For non repeated fields, a call to the \code{HasField}
method of the corresponding \code{Message} is issued.

For repeated fields, a call to the \code{FieldSize}
method is issued, and the message is declared to have 
the field if the size is greater than 0.
}
\section{Methods}{
	\describe{
		\item{has}{\code{signature(object = "protobufMessage")}: Indicates if the message has a given field.}
	}
}
\keyword{methods}

