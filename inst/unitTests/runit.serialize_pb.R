#Jeroen Ooms

test.serialize_pb <- function() {
  #verify that rexp.proto is loaded
  RProtoBuf:::pb(rexp.REXP)
  
  #serialize a nested list
  x <- list(foo=cars, bar=Titanic)
  checkEquals(unserialize_pb(serialize_pb(x, NULL)), x)
  
  #a bit of everything, copied from jsonlite package
  set.seed('123')
  myobject <- list(
    mynull = NULL,
    mycomplex = lapply(eigen(matrix(-rnorm(9),3)), round, 3),
    mymatrix = round(matrix(rnorm(9), 3),3),
    myint = as.integer(c(1,2,3)),
    mydf = cars,
    mylist = list(foo='bar', 123, NA, NULL, list('test')),
    mylogical = c(TRUE,FALSE,NA),
    mychar = c('foo', NA, 'bar'),
    somemissings = c(1,2,NA,NaN,5, Inf, 7 -Inf, 9, NA),
    myrawvec = charToRaw('This is a test')
  );
  
  checkEquals(unserialize_pb(serialize_pb(myobject, NULL)), myobject)
}
