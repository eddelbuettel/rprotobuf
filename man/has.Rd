\name{has-methods}
\docType{methods}
\alias{has}
\alias{has-methods}
\alias{has,Message-method}

\title{Indicates if an object has the given field set}
\description{
This generic method, currently implemented
for \linkS4class{Message} and \linkS4class{EnumDescriptor} indicates if the
message or enum descriptor has the given field set. 

For messages and non-repeated fields, a call to the \code{HasField}
method of the corresponding \code{Message} is issued.

For messages and repeated fields, a call to the \code{FieldSize}
method is issued, and the message is declared to have 
the field if the size is greater than 0.

\code{NULL} is returned if the descriptor for the message does not
contain the given field at all.

For EnumDescriptors, a boolean value indicates if the given name is
present in the enum definition.
}
\section{Methods}{
	\describe{
		\item{has}{\code{signature(object = "Message")}:
		  Indicates if the message has a given field.}
                \item{has}{\code{signature(object = "EnumDescriptor")}:
		  Indicates if the EnumDescriptor has a given named element.}
	}
}
\examples{
unitest.proto.file <- system.file("unitTests", "data", "unittest.proto",
				  package = "RProtoBuf" )
readProtoFiles(file = unitest.proto.file)

test <- new(protobuf_unittest.TestAllTypes)
test$has("optional_int32")
# FALSE
test$add("repeated_int32", 1:10)
test$has("repeated_int32")
# TRUE
test$has("nonexistant")
# NULL

has(protobuf_unittest.TestAllTypes$NestedEnum, "FOO")
has(protobuf_unittest.TestAllTypes$NestedEnum, "BAR")
has(protobuf_unittest.TestAllTypes$NestedEnum, "XXX")
}
\keyword{methods}
