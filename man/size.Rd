\name{size-methods}
\docType{methods}
\alias{size}
\alias{size-methods}
\alias{size,Message-method}
\title{Size of a message field}
\description{
The number of object currently in a given field of a protocol buffer
message. 

For non repeated fields, the size is 1 if the message has the field, 0 otherwise. 

For repeated fields, the size is the number of objects in the array.
}
\section{Methods}{
\describe{
\item{\code{signature(object = "Message")}}{Number of objects in a message field}
}}
\keyword{methods}

