\name{serialize_pb}
\alias{can_serialize_pb}
\alias{serialize_pb}
\alias{unserialize_pb}
\title{Serialize R object to Protocol Buffer Message.}
\usage{
  serialize_pb(object, connection, ...)
}
\arguments{
  \item{object}{R object to serialize}

  \item{connection}{passed on to \code{\link{serialize}}}

  \item{...}{additional arguments passed on to
  \code{\link{serialize}}}
}
\description{
  This function serializes R objects to a general purpose
  protobuf message. It uses the same \code{rexp.proto}
  descriptor and mapping between R objects and protobuf
  messages as RHIPE.
}
\details{
  Third party clients need both the message and the
  \code{rexp.proto} descriptor to read serialized R
  objects. The latter is included in the the package
  installation \code{proto} directory:
  \code{system.file(package="RProtoBuf",
  "proto/rexp.proto")}

  Currently, the following storage types are supported:
  \code{character}, \code{raw}, \code{double},
  \code{complex}, \code{integer}, \code{list}, and
  \code{NULL}. Objects with other storage types, such as
  functions, environments, S4 classes, etc, will be skipped
  with a warning. Missing values, attributes and numeric
  precision will be preserved.
}
\examples{
msg <- tempfile();
serialize_pb(iris, msg);
obj <- unserialize_pb(msg);
identical(iris, obj);
}

