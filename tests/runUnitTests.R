# This file is part of RProtoBuf.
#
# RProtoBuf is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 2 of the
# License, or (at your option) any later version.
#
# RProtoBuf is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.

## doRUnit.R --- Run RUnit tests
##
## with credits to package fUtilities in RMetrics
## which credits Gregor Gojanc's example in CRAN package  'gdata'
## as per the R Wiki http://wiki.r-project.org/rwiki/doku.php?id=developers:runit
## and changed further by Martin Maechler
## and more changes by Murray Stokely in HistogramTools
##
## Dirk Eddelbuettel, Dec 2013

if (requireNamespace("RUnit", quietly=TRUE) &&
    requireNamespace("RProtoBuf", quietly=TRUE)) {

    library(RUnit)
    library(RProtoBuf)

    ## Set a seed to make the test deterministic
    set.seed(42)

    ## Define tests
    testSuite <- defineTestSuite(name="RProtoBuf Unit Tests",
                                 dirs=system.file("unitTests", package = "RProtoBuf"),
                                 testFuncRegexp = "^[Tt]est.+")

    tests <- runTestSuite(testSuite)    # run tests
    printTextProtocol(tests)	    	# print results

    ## Return success or failure to R CMD CHECK
    if (getErrors(tests)$nFail > 0) stop("TEST FAILED!")
    if (getErrors(tests)$nErr > 0) stop("TEST HAD ERRORS!")
    if (getErrors(tests)$nTestFunc < 1) stop("NO TEST FUNCTIONS RUN!")
}
