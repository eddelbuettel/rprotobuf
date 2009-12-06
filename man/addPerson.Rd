\name{addPerson}
\alias{addPerson}
\alias{clearPerson}
\title{Add or remove another person to the the address book example for ProtoBuf}
\description{
  This function provides another simple example for using
  ProtoBuf generated accessor functions to store ProtoBuf data from R in
  the \code{addPerson} function. For completeness, \code{clearPerson}
  also allows to remove a person given an id.
}
\usage{
  addPerson(filename, id, name, emails, phones)
  clearPerson(filename, id)
}
\arguments{
  \item{filename}{complete path to a binary addressbook written in
    function built from the addressbook.proto description; an example
    file is used is no argument is supplied}
  \item{id}{numeric id of the person record}
  \item{name}{first and last name as a character string}
  \item{emails}{character vector of emails addressess, can be zero}
  \item{phones}{named character vector of phone numbers, can be zero;
    with names one of 'work', 'home' or 'mobile'}
}
\value{A status code of zero is returned on completion..
}
\details{
  This function provides an implementation of the \code{add_person.cc} example
  provided with the ProtoBuf compiler.

  Protocol Buffers is a serialization format with an interface
  description language developed by Google. The original Google implementation
  for C++, Java and Python is available under the BSD license at
  \url{http://code.google.com/p/protobuf/}. A good description of
  Protocol Buffers is available at
  \url{http://en.wikipedia.org/wiki/Protocol_Buffers}. 

  This function is a first attempt of exporting binary data R into 
  ProtoBuf files.
}
\author{Romain Francois and Dirk Eddelbuettel for the R package; Google for Protocal Buffers.}
\examples{
\dontrun{
  addPerson(system.file("examples/AddressBookFile", package="RProtoBuf"),
            7, "James Bond", "james@bond.com", c("home"="(123) 456-7890", "work"="(222) 333-4455"))
  clearPerson(system.file("examples/AddressBookFile", package="RProtoBuf"), 3)
}
}

