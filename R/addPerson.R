
addPerson <- function(filename, id, name, emails, phones) {

    if (missing(filename))
        filename <- system.file("examples/AddressBookFile", package="RProtoBuf")

    ## call the addPerson function with required parameters
    resList <- .Call("addPerson",
                     list("filename"=filename, "id"=id, "name"=name),
                     emails,
                     phones,
                     names(phones),
                     package="RProtoBuf")

    invisible(resList[[1]])
}
