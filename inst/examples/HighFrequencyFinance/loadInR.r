#!/usr/bin/r -t


basicUse <- function(verbose=TRUE) {
    readProtoFiles("TradeData.proto")
    x <- read( TradeData.Trades, "trades.pb")
    xl <- as.list(x)
    df <- do.call(rbind, lapply(as.list(xl$fill), function(.) as.data.frame(as.list(.))))
    df[,1] <- as.POSIXct(df[,1], origin="1970-01-01")
    if (verbose) print(summary(df))
    invisible(df)
}

timedUse <- function() {
    a1 <- system.time(readProtoFiles("TradeData.proto"))
    a2 <- system.time(x <- read( TradeData.Trades, "trades.pb"))
    a3 <- system.time(xl <- as.list(x))
    a4 <- system.time(df <- do.call(rbind, lapply(as.list(xl$fill), function(.) as.data.frame(as.list(.)))))
    print(summary(df))

    print(rbind(a1, a2, a3, a4))
    invisible(df)
}

profiledUse <- function() {
    Rprof(filename = "loadIt-Rprof.out", interval = 0.01)
    readProtoFiles("TradeData.proto")
    x <- read( TradeData.Trades, "trades.pb")
    xl <- as.list(x)
    df <- do.call(rbind, lapply(as.list(xl$fill), function(.) as.data.frame(as.list(.))))
    print(summary(df))
    Rprof(NULL)
    invisible(df)
}

betterUse <- function(verbose=TRUE, file = "trades.pb") {
    readProtoFiles("TradeData.proto")
    x <- read( TradeData.Trades, "trades.pb")
    xl <- lapply( x$fill, as.list )

    df <- data.frame(timestamp = as.POSIXct( sapply( xl, "[[", "timestamp" ), origin="1970-01-01"),
                     symbol    = sapply( xl, "[[", "symbol" ),
                     price     = sapply( xl, "[[", "price" ),
                     size      = sapply( xl, "[[", "size" )
                     )
    if (verbose) print(summary(df))
    invisible(df)
}

preAlloc <- function(verbose=TRUE) {
    readProtoFiles("TradeData.proto")
    x <- read( TradeData.Trades, "trades.pb")
    x1 <- as.list(x)									# 36 sec
    xl <- as.list(x1$fill)
    n <- length(xl)
    df <- data.frame(ts    = rep(NA, n),
                     sym   = rep("", n),
                     price = rep(NA, n),
                     size  = rep(NA, n),
                     stringsAsFactors=FALSE)
    for (i in 1:n) {
         df[i, ] <- as.list(xl[[i]])
    }
    df[,1] <- as.POSIXct(df[,1], origin="1970-01-01")
    if (verbose) print(summary(df))
    invisible(df)
}

compiled <- function(verbose=FALSE, file="trades.pb") {

    stopifnot(file.exists(file))

    df <- .Call("pbload", file);

    if (verbose) print(summary(df))

    invisible(df)
}

moduled <- function(verbose=FALSE, file="trades.pb", dll) {

    stopifnot(file.exists(file))

    trds <- Module("trades", dll)
    td <- new( trds$Trades )
    td$init(file)
    #print(n <- td$numberOfFills())
    df <- td$getData()

    if (verbose) print(summary(df))

    invisible(df)
}

suppressMessages(library(stats))
suppressMessages(library(RProtoBuf))
suppressMessages(library(utils))
suppressMessages(library(Rcpp))
suppressMessages(library(rbenchmark))

dll <- dyn.load("protoModule.so")

## uncomment next line to see a crash when running twice !
#moduled(TRUE); moduled(TRUE); q()




print(benchmark(compiled  = compiled(FALSE),
                #moduled   = moduled(FALSE),   ## uncomment and crash
                basicUse  = basicUse(FALSE),
                betterUs  = betterUse(FALSE),
                preAlloc  = preAlloc(FALSE),
                order = "elapsed",
                columns = c("test", "replications", "elapsed", "relative", "user.self", "sys.self"),
                replications  = 3))


