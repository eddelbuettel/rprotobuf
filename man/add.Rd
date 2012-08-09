\name{add-methods}
\docType{methods}
\alias{add}
\alias{add-methods}
\alias{add,Message-method}
\title{add elements of a repeated field of a message}
\description{
Add elements to a repeated field of a message.
}
\section{Methods}{
\describe{
\item{\code{signature(object = "Message")}}{add elements to a repeated field of a message}
}}
\examples{
unitest.proto.file <- system.file("unitTests", "data", "unittest.proto",
				  package = "RProtoBuf" )
readProtoFiles(file = unitest.proto.file)

test <- new(protobuf_unittest.TestAllTypes)
test$add("repeated_int32", 1)
test$add("repeated_int32", 2:10)
test$repeated_int32
}
\keyword{methods}
