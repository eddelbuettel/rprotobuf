// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "ConnectionCopyingOutputStream.h"

namespace rprotobuf {

ConnectionCopyingOutputStream::ConnectionCopyingOutputStream(SEXP con)
    : con(con), writeBin("writeBin") {}

bool ConnectionCopyingOutputStream::Write(const void* buffer, int size) {

    /* we need to take care of error handling */
    Rcpp::RawVector payload(size);
    memcpy(payload.begin(), buffer, size);

    writeBin(payload, con);
    return true;
}
}
