#' Serialize R object to Protocol Buffer Message.
#'
#' Serializes R objects to a general purpose protobuf message using the same
#' \code{rexp.proto} descriptor and mapping between R objects and protobuf
#' mesages as RHIPE.
#'
#' Clients need both the message and the \code{rexp.proto} descriptor to parse
#' serialized R objects. The latter is included in the the package installation
#' \code{proto} directory: \code{system.file(package="RProtoBuf", "proto/rexp.proto")}
#'
#' The following storage types are natively supported by the descriptor:
#' \code{character}, \code{raw}, \code{double}, \code{complex}, \code{integer},
#' \code{list}, and \code{NULL}. Objects with other storage types, such as
#' functions, environments, S4 classes, etc, are serialized using base R
#' \code{\link{serialize}} and stored in the proto \code{native} type.
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
