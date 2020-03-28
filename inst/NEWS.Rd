\name{NEWS}
\title{News for Package \pkg{RProtoBuf}}
\newcommand{\ghpr}{\href{https://github.com/eddelbuettel/rprotobuf/pull/#1}{##1}}
\newcommand{\ghit}{\href{https://github.com/eddelbuettel/rprotobuf/issues/#1}{##1}}

\section{Changes in RProtoBuf version 0.4.17 (2020-03-xx)}{
  \itemize{
    \item Condition use of \code{ByteSizeLong()} on building with ProtoBuf
    3.6.0 or later (Dirk in \ghpr{71} fixing \ghit{70}).
    \item The JSON unit tests are skipped if ProtoBuf 2.* is used (Dirk,
    also \ghpr{71}).
    \item The \code{configure} script now extracts the version from the
    \code{DESCRIPTION} file ( (Dirk, also \ghpr{71}).
  }
}

\section{Changes in RProtoBuf version 0.4.16 (2020-03-19)}{
  \itemize{
    \item Added support for parsing and printing JSON (Siddhartha
    Bagaria in \ghpr{68} closing wishlist \ghit{61}).
    \item Switched \code{ByteSize()} to \code{ByteSizeLong()} to appease
    \code{clang} (Dirk).
  }
}

\section{Changes in RProtoBuf version 0.4.15 (2020-02-08)}{
  \itemize{
    \item Repeated Message and Group objects are now returned correctly
    (Dirk in \ghpr{64} fixing \ghit{62}).
    \item The unit tests are now run by \pkg{tinytest} (Dirk in \ghpr{65}).
    \item The vignettes are now included pre-made (Dirk in \ghpr{67}).
  }
}

\section{Changes in RProtoBuf version 0.4.14 (2019-06-30)}{
  \itemize{
    \item An \code{all.equal.Message} method was added to avoid a
    fallback to the generic (Jarod Meng in \ghpr{54} fixing \ghit{53})
    \item Recursive fields now handled by \code{identical()} (Jarod Meng
    in \ghpr{57} fixing \ghit{56})
    \item Update Windows build infrastructure (Jeroen)
  }
}

\section{Changes in RProtoBuf version 0.4.13 (2018-11-03)}{
  \itemize{
    \item The \code{configure} setup is more robust with respect to the
    C++ setup (CRAN request).
    \item \code{POSIXlt} elements are now properly serialized too
    (Jeffrey Shen in \ghpr{48} and \ghpr{50} fixing \ghit{47})
    \item Added two Dockerfiles for continuous integration and use; see
    \href{https://cloud.docker.com/swarm/rprotobuf/repository/list}{this
      url} for more.
  }
}

\section{Changes in RProtoBuf version 0.4.12 (2018-07-11)}{
  \itemize{
    \item Recursive serialization of sublists returning themselves is
    now recognised (Jeffrey Shen in \ghpr{38} fixing \ghit{37})
    \item New function \code{readProtoFiles2} to be consistent with
    \code{protoc} (Siddhartha Bagaria in \ghpr{40} fixing \ghit{39})
    \item Update Windows binary library used (Maciej Lach and Jeroen
    Ooms in \ghpr{42} and follow-up commits)
    \item New unit tests for new functionality (Siddhartha Bagaria in
    \ghpr{45})
  }
}

\section{Changes in RProtoBuf version 0.4.11 (2017-10-03)}{
  \itemize{
    \item The \code{RProtoBuf-intro} and \code{RProtoBuf-quickref}
    vignettes were converted to Rmarkdown using the templates and style
    file from the pinp package.
    \item A few minor internal upgrades
  }
}

\section{Changes in RProtoBuf version 0.4.10 (2017-08-13)}{
  \itemize{
    \item More careful operation in deserializer checking for a valid
    class attribute (Jeffey Shen in \ghpr{29} fixing \ghit{28})
    \item At the request of CRAN, correct one \code{.Call()} argument to
    \code{PACKAGE=}; update routine registration accordingly
  }
}

\section{Changes in RProtoBuf version 0.4.9 (2017-03-06)}{
  \itemize{
    \item A new file \code{init.c} was added with calls to
    \code{R_registerRoutines()} and \code{R_useDynamicSymbols()}
    \item Symbol registration is enabled in \code{useDynLib}
    \item Several missing \code{PACKAGE=} arguments were added to
    the corresponding \code{.Call} invocations
    \item Two (internal) C++ functions were renamed with suffix
    \code{_cpp} to disambiguate them from R functions with the same name
    \item All of above were part of \ghpr{26}
    \item Some editing corrections were made to the introductory
    vignette (David Kretch in \ghpr{25})
    \item The `configure.ac` file was updated, and renamed from the
    older converntion `configure.in`, along with `src/Makevars`. (PR
    \ghpr{24} fixing \ghit{23}) 
  }
}

\section{Changes in RProtoBuf version 0.4.8 (2017-01-17)}{
  \itemize{
    \item Windows builds now use the proto3 library as well (PR \ghpr{21}
    fixing \ghit{20})
  }
}

\section{Changes in RProtoBuf version 0.4.7 (2016-10-27)}{
  \itemize{
    \item At the request of CRAN, two documentation instances referring
    to the Omegehat repository were updated to \url{http://omegahat.net}
  }
}

\section{Changes in RProtoBuf version 0.4.6 (2016-09-08)}{
  \itemize{
    \item Support for serializing zero-length objects was added (PR
    \ghpr{18} addressing \ghit{13})
    \item S4 objects are natively encoded (also PR \ghpr{18})
    \item The vignette based on the JSS paper no longer uses a macro available
    only with the R-devel version of jss.cls, and hence builds on all R versions
  }
}

\section{Changes in RProtoBuf version 0.4.5 (2016-08-29)}{
  \itemize{
    \item Support for version 3 of the Protcol Buffers API
    \item Added 'syntax = "proto2";' to all proto files (PR \ghpr{17})
    \item Updated Travis CI script to test against both versions 2 and 3
    using custom-built .deb packages of version 3 (PR \ghpr{16})
    \item Improved build system with support for custom CXXFLAGS (Craig
    Radcliffe in PR \ghpr{15}) 
  }
}

\section{Changes in RProtoBuf version 0.4.4 (2016-07-10)}{
   \itemize{
    \item New vignette based on JSS publication (v71 i02)
    \item Some documentation enhancements were made, as well as other
    minor cleanups to file modes and operations
    \item Unit-test vignette no longer writes to \code{/tmp} per CRAN
    request
    \item The new Windows toolchain (based on g++ 4.9.*) is supported
  }
}

\section{Changes in RProtoBuf version 0.4.3 (2015-08-25)}{
  \itemize{
    \item Declare additional imports from \pkg{methods} in \code{NAMESPACE}.
    \item Travis CI tests now run faster as all CRAN dependencies are
    installed as binaries.
    \item The \code{tools/winlibs.R} script now tests for R (< 3.3.0)
    before calling the (soon-to-be phased out) \code{setInternet2()} function.
    \item Several small edits were made to \code{DESCRIPTION} to clarify
    library dependencies, provide additonal references and conform to
    now-current R packaging standards.
  }
}

\section{Changes in RProtoBuf version 0.4.2 (2014-12-10)}{
  \itemize{
    \item Address changes suggested by anonymous reviewers for our
    Journal of Statistical Software submission.
    \item Make \code{Descriptor} and \code{EnumDescriptor} objects subsettable with
    "\code{[[}".
    \item Add \code{length()} method for \code{Descriptor} objects.
    \item Add \code{names()} method for \code{Message},
    \code{Descriptor}, and \code{EnumDescriptor} objects.
    \item Clarify order of returned list for descriptor objects in
    \code{as.list} documentation.
    \item Correct the definition of \code{as.list} for \code{EnumDescriptors} to
    return a proper list instead of a named vector.
    \item Update the default print methods to use
    \code{cat()} with \code{fill=TRUE} instead of \code{show()} to eliminate the confusing
    \code{[1]} since the classes in \pkg{RProtoBuf} are not vectorized.
    \item Add support for serializing function, language, and
      environment objects by falling back to R's native serialization
      with \code{serialize_pb} and \code{unserialize_pb} to make it
      easy to serialize into a Protocol Buffer all of the more than 100
      datasets which come with R.
    \item Use \code{normalizePath} instead of creating a temporary
    file with \code{file.create} when getting absolute path names.
    \item Add unit tests for all of the above.
  }
}

\section{Changes in RProtoBuf version 0.4.1 (2014-03-25)}{
  \itemize{
    \item Document and add a test for the deprecated group
    functionality.
    \item Add a \code{CITATION} file pointing to the arXiv.org preprint.
    \item Fix a bug in the \code{show} method for \code{EnumDescriptor}
    types.
    \item Import all top-level enums from imported \code{.proto} files.
    \item Removed duplicate enum value type from the unit tests that
    caused problems with the most recent libprotobuf-2.5. (without option
    allow_alias).
  }
}

\section{Changes in RProtoBuf version 0.4.0 (2014-01-14)}{
  \itemize{
    \item Changes to support CRAN builds for MS Windows.
    \item Added functions \code{serialize_pb}, \code{unserialize_pb},
    and \code{can_serialize_pb} plus documentation from Jeroen Ooms
    RProtoBufUtils package.
    \item New dir \code{inst/python} with some Python examples.
    \item Added Jeroen Ooms as author.
    \item Vignettes have been converted to the R 3.0.0 or later use of
    external vignette builders, no longer need a \code{Makefile}
    \item Added missing methods to dollar completion list for Message,
    Descriptor, EnumValueDescriptor, and FileDescriptor classes.
    \item Add missing export for \code{.DollarNames} EnumValueDescriptor
    to allow completion on that class.
    \item Add more than 15 additional pages to the main Intro vignette
    documenting better all of the S4 classes implemented by RProtoBuf,
    updating the type mapping tables to take into account 64-bit
    support, and documenting advanced features such as Extensions.
    \item Added better error checking in EnumDescriptors to catch the
    case when wrong types are provided.
    \item Updated the FileDescriptor \code{name()} method to accept a boolean
    for full paths just like the generic \code{name()} method.
    \item Correct a bug that incorrectly dispatched \code{as.character()} when
    \code{as.list()} was called on Descriptor objects.
    \item Update FileDescriptor \code{$} dispatch to work properly for
    the names of fields defined in the FileDescriptor, instead of
    just returning \code{NULL} even for types returned by \code{$}
    completion.
    \item Added a reservation for extension fields in the example
    tutorial.Person schema.
    \item Support setting int32 fields with character representations
    and raise an R-level \code{stop()} error if the provided string can
    not be parsed as a 32-bit integer, rather than crashing the R
    instance.
    \item Update the project TODO file.
    \item Add better documentation and tests for all of the above.
    \item Corrected the handling of uint32 and fixed32 types in protocol
    buffers to ensure that they work with numbers as large as 2^32 - 1,
    which is larger than an integer can hold in R since R does not have an
    unsigned integer class.  These values are stored as doubles internally
    now to avoid losing precision.
    \item Added unit tests to verify behavior of RProtoBuf with extreme
    values for uint32 types.
    \item Removed old exception handling code and instead rely on the
    more modern Rcpp::stop method maintained in Rcpp.
    \item Add better error messages when setting a repeated field of
    messages to inform the user which element index was of the wrong type
    and what the expected type was.
    \item Add an optional 'partial' argument to readASCII allowing
    uninitialized message fragments to be read in.
    \item (internal) Added const qualifiers in more places throughout
    the C++ code for type safety.
    \item (internal) Standardize coding conventions of the C++ files and
    run them through clang-format for consistency.  A STYLE file has
    been submitted to R-Forge with details about the coding standards
    and how they are enforced with Emacs and clang-format.
    \item Applied changes suggested by Kevin Ushey to the \code{S4}
    class handling to support both the currently released \CRANpkg{Rcpp} as
    well as the currently pending next version.
  }
}

\section{Changes in RProtoBuf version 0.3.2 (2013-12-15)}{
  \itemize{
    \item Fixed a bug that erroneously prevented users from setting raw
    byte fields in protocol buffers under certain circumstances.
    \item Give a user friendly error message when seting an extension to
    a message of the wrong type instead of causing a C++ check failure
    that terminates the Rsession.
    \item Change object table lookup slightly to allow users to use the
    \code{<<-} operator in code using \pkg{RProtoBuf} without hitting a
    \code{stop()} error in the lookup routine.
    \item Add missing \code{enum_type} method and improve show method for
    EnumValueDescriptors.
    \item Improve documentation and tests for all of the above.
    \item Rewrote \code{tests/} script calling \CRANpkg{RUnit} tests
  }
}

\section{Changes in RProtoBuf version 0.3.1 (2013-09-13)}{
  \itemize{
    \item Added support for setting and getting 64-bit integer types as
      character strings of decimal integers to work around R's lack of
      native 64-bit integer types.
    \item Added better error handling, documentation, and tests to the
      extensions support (getExtension and setExtension).
      \item Add support to P for returning extension descriptors.
    \item Improved error messages to include field names when invalid
    fields are specified to protocol buffer messages with new, update, etc.
    \item Improved configure to detect and pass -std=c++0x if it is
    available to enable long long 64-bit integer support in Rcpp.
    \item Improved configure in the case when pkg-config is not
    available or does not know about the google protocol buffer
    includes.
    \item Replaced newly deprecated Rcpp macros with a simplified macro
    functionality to avoid warnings on the latest development version of
    Rcpp.
  }
}

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
