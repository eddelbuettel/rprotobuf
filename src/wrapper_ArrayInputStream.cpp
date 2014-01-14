// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-

#include "rprotobuf.h"
#include "RcppMacros.h"
#include <stdio.h>
namespace rprotobuf {

RPB_FUNCTION_2(S4_ArrayInputStream, ArrayInputStream__new, Rcpp::RawVector payload,
               int block_size) {
    printf("In ArrayInputStream__new, returning S4_ArrayInputStream(payload, blocksize)\n");
    return S4_ArrayInputStream(payload, block_size);
}
}
