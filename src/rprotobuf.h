#ifndef RPROTOBUF_H
#define RPROTOBUF_H

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/importer.h>

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <R_ext/Callbacks.h>

#include <Rcpp.h>

/* undefine this to quiet debug messages */
#define RPB_DEBUG

#define PrintValue Rf_PrintValue
#define install Rf_install
#define error Rf_error

#define PRINT_DEBUG_INFO(name,o) \
	Rprintf( "     %s [%d] =     ", name, TYPEOF(o) ) ; \
	PrintValue( o ) ; \

#define RPROTOBUF_LOOKUP 24
#define LOOKUP_DEBUG

/* FIXME : quick hack because just using TRUE and FALSE did not work in lookup.cpp */
#define _TRUE_ (Rboolean)TRUE
#define _FALSE_ (Rboolean)FALSE


#endif
