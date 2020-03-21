
## RProtoBuf configure.ac
##
## Copyright (C) 2009 - 2020  Dirk Eddelbuettel <edd@debian.org>
## Portions Copyright (C) 2010  Romain Francois
## Portions Copyright (C) 2013  Murray Stokely
## Portions Copyright (C) 2016  Craig Radcliffe

# require at least autoconf 2.61
AC_PREREQ(2.61)

# Process this file with autoconf to produce a configure script.
AC_INIT([RProtoBuf], m4_esyscmd_s([awk -e '/^Version:/ {print $2}' DESCRIPTION]))

# Ensure C++ is set up as R expects
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
    AC_MSG_ERROR([Could not determine R_HOME.])
fi
CXX=`"${R_HOME}/bin/R" CMD config CXX`
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
AC_LANG(C++)
AC_REQUIRE_CPP
AC_PROG_CC
AC_PROG_CXX

## simpler alternative to test below:  AC_PATH_PROG(PROTOC, protoc)

AC_DEFUN([AC_PROG_PKGCONFIG], [AC_CHECK_PROG(PKGCONFIG,pkg-config,yes)])
AC_PROG_PKGCONFIG

## use pkg-config for ProtoBuf settings
##
if test x"${PKGCONFIG}" == x"yes"; then
    if pkg-config --exists protobuf; then
        protobuf_cxxflags=`pkg-config --cflags protobuf`
        protobuf_libs=`pkg-config --libs protobuf`
    else
        protobuf_cxxflags=""
        protobuf_libs="-lprotobuf"
    fi
else
    # Add a reasonable default of -lprotobuf if we don't have pkg-config
    protobuf_cxxflags=""
    protobuf_libs="-lprotobuf"
fi

## And make sure these flags are used for the tests below.
CPPFLAGS="${protobuf_cxxflags} ${CPPFLAGS}"
CXXFLAGS="${protobuf_cxxflags} ${CXXFLAGS}"

## look for protoc, the ProtoBuf compiler
AC_DEFUN([AC_PROG_PROTOC], [AC_CHECK_PROG(PROTOC,protoc,yes)])
AC_PROG_PROTOC
if test x"${PROTOC}" == x"no" ; then
    echo "
  Your installation does not appear to have protoc installed.

  Please make sure that you have a working and complete ProtoBuf installation.
"
    exit 1
fi

## look for protobuf headers -- now use pkg-config which even does minimum version
##
## next two lines break witha autoconf 2.65 :-/
#PROTOBUF_VERSION="2.2.0"
#PKG_CHECK_MODULES(ProtoBuf, protobuf >= 2.2.0, , AC_MSG_ERROR(Protobuf version 2.2.0 required))

## check for header and ability to link
## first for headers Debian has in libprotobuf-dev
protobuf_common_header=google/protobuf/stubs/common.h
protobuf_common_header_cache_var=AS_TR_SH([ac_cv_header_$protobuf_common_header])
AC_CHECK_HEADER([$protobuf_common_header],,
                [
		# If it didn't work, try adding /usr/local directly then trying again
		AC_MSG_WARN([Protobuf headers not found with default CXXFLAGS and CPPFLAGS, manually trying /usr/local/include])
		CPPFLAGS="${protobuf_cxxflags} ${CPPFLAGS} -I/usr/local/include"
		CXXFLAGS="${protobuf_cxxflags} ${CXXFLAGS} -I/usr/local/include -L/usr/local/lib"
		# unset the cache variable for this particular header
		# check, so we can check again with different defaults
		# specified.
		AC_MSG_WARN([Unsetting $protobuf_common_header_cache_var])
		AS_UNSET([$protobuf_common_header_cache_var])
		AC_CHECK_HEADER([$protobuf_common_header],,
		[AC_MSG_ERROR([ERROR: ProtoBuf headers required; use '-Iincludedir' in CXXFLAGS for unusual locations.])])
		])
## second for headers Debian has in libprotoc-dev
AC_CHECK_HEADER(google/protobuf/compiler/code_generator.h,,
                [AC_MSG_ERROR([ERROR: ProtoBuf compiler headers required; use '-Iincludedir' in CXXFLAGS for unusual locations.])])
## third check the lib itself
#pb_savedlibs="$LIBS"
# LIBS="$LIBS -lprotoc -lprotobuf -lpthread"
LIBS="$LIBS $protobuf_libs"

## also check for minimum version
AC_MSG_CHECKING([if ProtoBuf version >= 2.2.0])
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <google/protobuf/stubs/common.h>
int main() {
   if (GOOGLE_PROTOBUF_VERSION >= 2001000) {
        exit (0);
   } else {
        exit(1);
   }
}
]])],
[pb_version_ok=yes],
[pb_version_ok=no],
[pb_version_ok=yes])
if test x"${pb_version_ok}" == x"no"; then
    AC_MSG_ERROR([Need ProtoBuf version >= 2.2.0])
else
    AC_MSG_RESULT([yes])
fi

AC_DEFUN([AC_PROG_R], [AC_CHECK_PROG(R,R,yes)])
AC_PROG_R

## With thanks to Kurt (now set above)
#: ${R_HOME=`R RHOME`}
#if test -z "${R_HOME}"; then
#    AC_MSG_ERROR([Could not determine R_HOME.])
#fi
#R_CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
#CXXFLAGS="${CXXFLAGS} ${R_CXXFLAGS}"

## now use all these
AC_SUBST([PKG_CPPFLAGS],["${PKG_CPPFLAGS} ${CXXFLAGS} ${protobuf_cxxflags}"])
AC_SUBST([PKG_LIBS],["${PKG_LIBS} ${protobuf_libs}"])
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

echo "
${PACKAGE_NAME} $PACKAGE_VERSION
================

cflags:  ${PKG_CPPFLAGS}
libs:    ${PKG_LIBS}
"
