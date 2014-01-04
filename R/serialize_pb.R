#' Serialize R object to Protocol Buffer Message.
#' 
#' This function serializes R objects to a general purpose protobuf message. It 
#' uses the same \code{rexp.proto} descriptor and mapping between R objects and
#' protobuf messages as RHIPE.
#' 
#' Third party clients need both the message and the \code{rexp.proto} descriptor
#' to read serialized R objects. The latter is included in the the package 
#' installation \code{proto} directory:
#' \code{system.file(package="RProtoBuf", "proto/rexp.proto")}
#' 
#' Currently, the following storage types are supported: 
#' \code{character}, \code{raw}, \code{double}, \code{complex}, \code{integer},
#' \code{list}, and \code{NULL}. Objects with other storage types, such as 
#' functions, environments, S4 classes, etc, will be skipped with a warning. 
#' Missing values, attributes and numeric precision will be preserved. 
#'  
#' @param object R object to serialize
#' @param connection passed on to  \code{\link{serialize}}
#' @param ... additional arguments passed on to  \code{\link{serialize}}
#' @aliases unserialize_pb can_serialize_pb
#' @export unserialize_pb
#' @export can_serialize_pb
#' @export
#' @examples msg <- tempfile();
#' serialize_pb(iris, msg);
#' obj <- unserialize_pb(msg);
#' identical(iris, obj);
#'
serialize_pb <- function(object, connection, ...){

  #convert object to protobuf message
  msg <- rexp_obj(object);

  #serialize the message
  serialize(msg, connection = connection, ...);
}

unserialize_pb <- function(connection){

  #convert object to protobuf message
  unrexp(read(pb(rexp.REXP), connection));
}
