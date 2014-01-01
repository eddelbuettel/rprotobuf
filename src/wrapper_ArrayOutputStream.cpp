// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-

#include "rprotobuf.h"
#include "RcppMacros.h"

namespace rprotobuf {

RPB_FUNCTION_2(S4_ArrayOutputStream, ArrayOutputStream__new, int size, int block_size) {
    return S4_ArrayOutputStream(size, block_size);
}
}
