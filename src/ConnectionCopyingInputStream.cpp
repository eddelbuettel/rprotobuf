// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "ConnectionCopyingInputStream.h"

namespace rprotobuf {

ConnectionCopyingInputStream::ConnectionCopyingInputStream(SEXP con)
    : con(con), readBin("readBin") {}

/**
 * call readBin to read size bytes from R
 *
 * @param buffer buffer to fill with at most size bytes
 * @param size maximum number of bytes
 *
 * @return the number of bytes actually read
 */
int ConnectionCopyingInputStream::Read(void* buffer, int size) {

    /* TODO: error handling */
    Rcpp::RawVector res = readBin(con, Rcpp::RawVector(0), size);
    memcpy(buffer, res.begin(), res.size());
    return res.size();
}
}
