
## doRUnit.R --- Run RUnit tests
##
## with credits to package fUtilities in RMetrics
## which credits Gregor Gojanc's example in CRAN package  'gdata'
## as per the R Wiki http://wiki.r-project.org/rwiki/doku.php?id=developers:runit
## and changed further by Martin Maechler
## and more changes by Murray Stokely in HistogramTools
##
## Dirk Eddelbuettel, Dec 2013

stopifnot(require("RUnit", quietly=TRUE))
stopifnot(require("RProtoBuf", quietly=TRUE))

#  path <- system.file("unitTests", package = pkg)
#  stopifnot(file.exists(path), file.info(path.expand(path))$isdir)
#  source(file.path(path, "runTests.R"), echo = TRUE)

## Set a seed to make the test deterministic
set.seed(42)

## Define tests
testSuite <- defineTestSuite(name="RProtoBuf Unit Tests",
                             dirs=system.file("unitTests", package = "RProtoBuf"),
                             testFuncRegexp = "^[Tt]est.+")

## Run tests
tests <- runTestSuite(testSuite)

## Print results
printTextProtocol(tests)

## Return success or failure to R CMD CHECK
if (getErrors(tests)$nFail > 0) {
   stop("TEST FAILED!")
}
if (getErrors(tests)$nErr > 0) {
   stop("TEST HAD ERRORS!")
}
if (getErrors(tests)$nTestFunc < 1) {
   stop("NO TEST FUNCTIONS RUN!")
}
