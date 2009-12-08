
listPeopleAsList <- function(filename, verbose=FALSE) {

    if (missing(filename))
        filename <- system.file("examples/AddressBookFile", package="RProtoBuf")

    ## call the listPeople function, with a sole parameter for the AddressBook
    resList <- .Call("listPeopleAsList",
                     list("filename"=filename), package="RProtoBuf")
    if (verbose) {
        print(str(resList))
    }
    invisible(resList)
}

listPeopleAsDataFrame <- function(filename, verbose=FALSE) {

    if (missing(filename))
        filename <- system.file("examples/AddressBookFile", package="RProtoBuf")

    ## call the listPeople function, with a sole parameter for the AddressBook
    resList <- .Call("listPeopleAsDataFrame",
                     list("filename"=filename), package="RProtoBuf")
    people <- data.frame(resList[[1]])
    numbers <- data.frame(resList[[2]])
    nr <- data.frame(resList[[3]])
    if (nr == 0) {
        return(invisible(NULL))
    }

    numbers$Type <- as.factor(numbers$Type)

    alldata <- merge(people, numbers)

    if (verbose) {
        cat("\nFirst data.frame: People\n")
        print(people)

        cat("\nSecond data.frame: Numbers\n")
        print(numbers)

        cat("\nMerged data.frame: People and Numbers\n")
        print(alldata)
    }
    invisible(alldata)
}









