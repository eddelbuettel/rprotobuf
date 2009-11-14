\name{protobufMessage-class}
\Rdversion{1.1}
\docType{class}
\alias{protobufMessage-class}
\alias{as.character,protobufMessage-method}
\alias{$<-,protobufMessage-method}
\alias{$,protobufMessage-method}
\alias{[[,protobufMessage-method}
\alias{[[<-,protobufMessage-method}
\alias{serialize,protobufMessage-method}
\alias{show,protobufMessage-method}
\alias{update,protobufMessage-method}
\alias{length,protobufMessage-method}
\alias{str,protobufMessage-method}
\alias{toString,protobufMessage-method}
\alias{identical,protobufMessage,protobufMessage-method}
\alias{==,protobufMessage,protobufMessage-method}
\alias{!=,protobufMessage,protobufMessage-method}
\alias{all.equal,protobufMessage,protobufMessage-method}

\title{Class "protobufMessage" }
\description{
R representation of protocol buffer messages. This is a thin wrapper
around the \code{Message} c++ class that holds the actual message
as an external pointer.
}
\section{Objects from the Class}{
	Objects are typically created by the \code{new} function invoked 
	on a \linkS4class{protobufDescriptor} object.
}
\section{Slots}{
  \describe{
  	  \item{\code{pointer}:}{external pointer to the c++ \code{Message} object}
  	  \item{\code{type}:}{fully qualified name of the message type}
  }
}
\section{Methods}{
  \describe{
    \item{as.character}{\code{signature(x = "protobufMessage")}: returns the debug string of the message. 
    	This is built from a call to the \code{DebugString} message of the \code{Message} object}
    \item{toString}{\code{signature(x = "protobufMessage")}: same as \code{as.character} }
    \item{$<-}{\code{signature(x = "protobufMessage")}: set the value of a field of the message. }
    \item{$}{\code{signature(x = "protobufMessage")}: gets the value of a field. 
    Primitive types are brough back to R as R objects of the closest matching R type. 
    Messages are brought back as instances of the \code{protobufMessage} class.}
    \item{[[}{\code{signature(x = "protobufMessage")}: extracts a field identified by its name or declared tag number }
    \item{[[<-}{\code{signature(x = "protobufMessage")}: replace the value of a field identified by its name or declared tag number }
	\item{serialize}{\code{signature(object = "protobufMessage")}: serialize a message. If the 
    	"connection" argument is \code{NULL}, the payload of the message is returned as a raw vector, 
    	if the "connection" argument is a binary writable connection, the payload is written into the 
       connection. If "connection" is a character vector, the message is sent to 
       the file (in binary format). }
    \item{show}{\code{signature(object = "protobufMessage")}: displays a short text about the message }
    \item{update}{\code{signature(object = "protobufMessage")}: set several fields of the message at once }
    \item{length}{\code{signature(x = "protobufMessage")}: The number of fields actually contained in the message. 
    A field counts in these two situations: the field is repeated and the field size is greater than 0, 
    the field is not repeated and the message has the field.}
    \item{str}{\code{signature(object = "protobufMessage")}: displays the structure of the message }
    \item{identical}{\code{signature(x = "protobufMessage", y = "protobufMessage")}: Test if two messages are exactly identical }
    \item{==}{\code{signature(e1 = "protobufMessage", e2 = "protobufMessage")}: Same as \code{identical} }
    \item{!=}{\code{signature(e1 = "protobufMessage", e2 = "protobufMessage")}: Negation of \code{identical} }
    \item{all.equal}{\code{signature(e1 = "protobufMessage", e2 = "protobufMessage")}: Test near equality }
     }
}
\references{ 
	The \code{Message} class from the C++ proto library.
	\url{http://code.google.com/apis/protocolbuffers/docs/reference/cpp/google.protobuf.message.html}
}
\author{ Romain Francois <francoisromain@free.fr> }
\seealso{
	\code{\link{P}} creates objects of class \linkS4class{protobufDescriptor} that 
	can be used to create messages. 
}
\examples{

# example proto file supplied with this package
proto.file <- system.file( "proto", "addressbook.proto", package = "RProtoBuf" ) 

# reading a proto file and creating the descriptor
Person <- P( "tutorial.Person", file = proto.file )
PhoneNumber <- P( "tutorial.Person.PhoneNumber" )

# creating a prototype message from the descriptor
p <- new( Person )
p$email # not set, returns default value
p$id    # not set, returns default value
as.character( p ) # empty
has( p, "email" ) # is the "email" field set
has( p, "phone" ) # is the "email" field set
length( p )       # number of fields actually set

# update several fields at once
romain <- update( new( Person ), 
	email = "francoisromain@free.fr", 
	id = 1, 
	name = "Romain Francois", 
	phone = new( PhoneNumber , number = "+33(0)...", type = "MOBILE" )
	)

# supply parameters to the constructor
dirk <- new( Person, 
	email = "edd@debian.org", 
	id = 2, 
	name = "Dirk Eddelbuettel" ) 
# update the phone repeated field with a list of PhoneNumber messages
dirk$phone <- list( 
	new( PhoneNumber , number = "+01...", type = "MOBILE" ), 
	new( PhoneNumber , number = "+01...", type = "HOME" ) )
	
# with/within style
saptarshi <- within( new(Person), {
	id <- 3
	name <- "Saptarshi Guha"
	email <- "saptarshi.guha@gmail.com" 
} )

# make an addressbook
book <- new( tutorial.AddressBook, person = list( romain, dirk, saptarshi ) )

# serialize the message to a file
tf <- tempfile( )
serialize( book, tf )

# the payload of the message
serialize( book, NULL )

# read the file into a new message
m <- tutorial.AddressBook$read( tf )
writeLines( as.character( m ) )
sapply( m$person, function(p) p$name )

}
\keyword{classes}
