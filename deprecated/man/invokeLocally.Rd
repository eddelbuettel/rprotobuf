\name{invoke-methods}
\docType{methods}
\alias{invoke}
\alias{invoke-methods}
\alias{invoke,MethodDescriptor,Message,missing-method}
\alias{invoke,MethodDescriptor,Message,RpcHTTP-method}
\title{invoke a protobuf rpc method}
\description{
invoke a protobuf rpc method
}
\section{Methods}{
\describe{
\item{\code{signature(method = "MethodDescriptor", message = "Message")}}{invoke a protobuf rpc method locally.}
\item{\code{signature(method = "MethodDescriptor", message = "Message", protocol = "RpcHTTP" )}}{invoke a protobuf rpc method over http.}
}}
\keyword{methods}
