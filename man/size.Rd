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
\examples{
unitest.proto.file <- system.file("unitTests", "data", "unittest.proto",
				  package = "RProtoBuf" )
readProtoFiles(file = unitest.proto.file)

test <- new(protobuf_unittest.TestAllTypes)
test$size("optional_int32")

test$add("repeated_int32", 1:10)
test$size("repeated_int32")
}
\keyword{methods}
