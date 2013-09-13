/*
 * Copyright 2013 Google Inc. All Rights Reserved.
 * Author: Murray Stokely
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

/*
 * This file contains macros for taking C++ functions that expect
 * native C++ types, automatically generating new stub functions that
 * take SEXPs and call the appropriate Rcpp conversion functions
 * before calling the original function.  It is based on slightly more
 * complex macros that were originally in Rcpp but have been
 * deprecated.
 *
 * In the future, Rcpp Modules would likely be a better more modern
 * way to implement RProtoBuf.
 */

#ifndef RPROTOBUF_RCPP_MACROS_H
#define RPROTOBUF_RCPP_MACROS_H

#include <Rcpp/macros/macros.h>  // RCPP_DECORATE, BEGIN_RCPP, END_RCPP

#define RPB_FUNCTION_0(__OUT__,__NAME__)            \
__OUT__ RCPP_DECORATE(__NAME__)();                  \
extern "C" SEXP __NAME__(){                         \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)() ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)()

#define RPB_FUNCTION_1(__OUT__,__NAME__, ___0)      \
__OUT__ RCPP_DECORATE(__NAME__)(___0);              \
extern "C" SEXP __NAME__(SEXP x0){                  \
SEXP res = R_NilValue ;                             \
BEGIN_RCPP                                          \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0)

#define RPB_FUNCTION_2(__OUT__,__NAME__, ___0, ___1)     \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1);             \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1){              \
SEXP res = R_NilValue ;                                  \
BEGIN_RCPP                                               \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1)

#define RPB_FUNCTION_3(__OUT__,__NAME__, ___0, ___1, ___2)   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2);           \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2){         \
SEXP res = R_NilValue ;                                      \
BEGIN_RCPP                                                   \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 )) ) ; \
return res ;                                        \
END_RCPP                                            \
}                                                   \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2)

#define RPB_FUNCTION_4(__OUT__,__NAME__, ___0, ___1, ___2, ___3)     \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3);             \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2, SEXP x3){        \
SEXP res = R_NilValue ;                                              \
BEGIN_RCPP                                                           \
res = ::Rcpp::wrap( RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 )), ::Rcpp::internal::converter( x3 )) ) ;   \
return res ;                                           \
END_RCPP                                               \
}                                                      \
__OUT__ RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3)

#define RPB_FUNCTION_VOID_0(__NAME__)               \
void RCPP_DECORATE(__NAME__)();                     \
extern "C" SEXP __NAME__(){                         \
BEGIN_RCPP                                          \
RCPP_DECORATE(__NAME__)();                          \
END_RCPP                                            \
}                                                   \
void RCPP_DECORATE(__NAME__)()

#define RPB_FUNCTION_VOID_1(__NAME__, ___0)         \
void RCPP_DECORATE(__NAME__)(___0);                 \
extern "C" SEXP __NAME__(SEXP x0){                  \
BEGIN_RCPP                                          \
RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 )); \
END_RCPP                                            \
}                                                   \
void RCPP_DECORATE(__NAME__)(___0)

#define RPB_FUNCTION_VOID_2(__NAME__, ___0, ___1)   \
void RCPP_DECORATE(__NAME__)(___0, ___1);           \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1){         \
BEGIN_RCPP                                          \
RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 )); \
END_RCPP                                            \
}                                                   \
void RCPP_DECORATE(__NAME__)(___0, ___1)

#define RPB_FUNCTION_VOID_3(__NAME__, ___0, ___1, ___2)   \
void RCPP_DECORATE(__NAME__)(___0, ___1, ___2);           \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2){      \
BEGIN_RCPP                                          \
RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 )); \
END_RCPP                                            \
}                                                   \
void RCPP_DECORATE(__NAME__)(___0, ___1, ___2)

#define RPB_FUNCTION_VOID_4(__NAME__, ___0, ___1, ___2, ___3)  \
void RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3);            \
extern "C" SEXP __NAME__(SEXP x0, SEXP x1, SEXP x2, SEXP x3){           \
BEGIN_RCPP                                          \
RCPP_DECORATE(__NAME__)(::Rcpp::internal::converter( x0 ), ::Rcpp::internal::converter( x1 ), ::Rcpp::internal::converter( x2 ), ::Rcpp::internal::converter( x3 )); \
END_RCPP                                            \
}                                                   \
void RCPP_DECORATE(__NAME__)(___0, ___1, ___2, ___3)

#endif
