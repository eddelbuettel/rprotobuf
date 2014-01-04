#simple R script to serialize some R objects
library(RProtoBuf)

#some vectors
serialize_pb(c(1,2,pi, NA,NaN,Inf,-Inf), "double.msg")
serialize_pb(c(1L, 2L, NA), "integer.msg")
serialize_pb(c(TRUE, FALSE, NA), "logical.msg")
serialize_pb(c("foo", "bar", NA), "character.msg")
serialize_pb(charToRaw("This is a test"), "raw.msg")

#lists
serialize_pb(list(foo=c(1,2,pi), bar=TRUE, baz="blabla", zoo=NULL), "list.msg")
serialize_pb(iris[1:3,], "dataframe.msg")
