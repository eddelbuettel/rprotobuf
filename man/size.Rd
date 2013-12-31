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

For repeated fields, the size can also be assigned to in order to shrink
or grow the vector.  Numeric types are given a default value of 0 when
the new size is greater than the existing size.  Character types are
given a default value of "".  Growing a repeated field in this way is
not supported for message, group, and enum types.
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
test$repeated_int32

size(test, "repeated_int32") <- 5
test$repeated_int32

size(test, "repeated_int32") <- 15
test$repeated_int32
}
\keyword{methods}
