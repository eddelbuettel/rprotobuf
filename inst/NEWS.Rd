\name{NEWS}
\title{News for Package \pkg{RProtoBuf}}
\newcommand{\cpkg}{\href{http://CRAN.R-project.org/package=#1}{\pkg{#1}}}

\section{Changes in RProtoBuf version 0.3 (2013-07-13)}{
  \itemize{
    \item Added support for Protocol Buffer extensions through the new
      getExtension and setExtension methods for Message objects, and added
      top-level extensions to the descriptor pool.
    \item Added more user-friendly \code{show()} methods for Messages,
      Descriptors, and other RProtoBuf objects.  A common source of
      confusion on the mailing lists is to confuse Messages and
      Descriptors.  The new \code{show()} methods succinctly display more
      information about e.g. the number of set fields in a message to
      make it a little clearer to users what type of object they are
      working with.
   \item Added has method for EnumDescriptor objects to test existance
     of a named constant in an enumeration, and fix a bug in the length
     method for these objects.
   \item Added a number method for EnumValueDescriptor objects to
     return the number of a named enumeration constant directly.
   \item Improved documentation and unit tests.
  }
}

\section{Changes in RProtoBuf version 0.2.6 (2012-10-04)}{
  \itemize{
    \item Applied several more patches by Murray to
    \itemize{
      \item correct '_' and '__' mismatches in wrapper calls
      \item update a few manual pages for style, and add examples
      \item fix a bug where NAs were silently treated as TRUE for logical/bool types
      \item fix a bug that caused crashes when adding vectors to optional fields
      \item fix bugs in readASCII that returned empty protocol buffers when the file or connection could not be opened
      \item distinguish between non-existant and not-set fieldswith
      has() by returning NULL in the former case.
      \item fix a bug that caused non-deterministic behavior when setting a repeated message field in a protobuf to a single Message.
      \item add unit tests for all of the above.
    }
    \item Added Murray to Authors: field in DESCRIPTION
    \item Removed old and unconvincing example on RProtoBuf for storage
    and serialization in an imagined HighFrequencyFinance context 
  }
}

\section{Changes in RProtoBuf version 0.2.5 (2012-08-08)}{
  \itemize{
    \item Applied patches by Murray to
    \itemize{
      \item correctly deal with nested Protocol Buffer definitions, and
      also add new unit test for this
      \item test a a protocol buffer for missing required fields before
      serializing it, also add a unit test
      \item add a small stylistic fix and examples to the 'add.Rd'
      manual page 
    }
    \item Moved inst/doc/ to vignettes/ per newer CRAN Policy
  }
}
\section{Changes in RProtoBuf version 0.2.4 (2012-05-15)}{
  \itemize{
    \item Applied several patches kindly supplied by Murray Stokely to
    \itemize{
      \item properly work with repeated strings 
      \item correct C++ function naming in a few instances
      \item add an example of ascii export/import of messages
    }
    \item Suppport g++-4.7 and stricter #include file checking by adding unistd
    \item Made small improvements to the startup code
  }
}
\section{Changes in RProtoBuf version 0.2.3 (2011-04-12)}{
  \itemize{
    \item Protect UINT64 and INT64 with '#ifdef RCPP_HAS_LONG_LONG' which
    itself is valid with either g++ <= 4.4, or newer versions if the 
    -std=c++0x is used
    \item The documentation Makefile now uses the $R_HOME environment variable
    \item The documentation Makefile no longer calls clean in the all
    target
  }
}
\section{Changes in RProtoBuf version 0.2.2 (2011-01-11)}{
  \itemize{
    \item Applied two patches by Murray Stokely which
    \itemize{
      \item correct a typo preventing some functions from being called, 
      \item add bounds checking in call to google protobuf library, 
      \item add a new name method 
      \item add a tiny unit test for the above
      \item add more graceful error handling
      \item add support for import patterns other than .proto$, 
      \item add simple reading file that does not exist (exception) test
      \item add simple repeated field unit test
    }
  }
}
\section{Changes in RProtoBuf version 0.2.1 (2010-10-18)}{
  \itemize{
    \item Support for raw bytes added thanks to a patch by Koert Kuipers
  }
}
\section{Changes in RProtoBuf version 0.2.0 (2010-09-10)}{
  \itemize{
    \item Second release with numerous internal changes made possible by
    changes in Rcpp
  }
}
\section{Changes in RProtoBuf version 0.1-0 (2010-02-01)}{
  \itemize{
    \item Initial CRAN release
  }
}
