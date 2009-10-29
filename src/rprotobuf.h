#ifndef RPROTOBUF_H
#define RPROTOBUF_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <Rcpp.h>
#include <Rdefines.h>
#include <Rinternals.h>

/* undefine this to quiet debug messages */
#define RPB_DEBUG

#define PrintValue Rf_PrintValue
#define install Rf_install
#define error Rf_error

#define PRINT_DEBUG_INFO(name,o) \
	Rprintf( "     %s [%d] =     ", name, TYPEOF(o) ) ; \
	PrintValue( o ) ; \

#endif
