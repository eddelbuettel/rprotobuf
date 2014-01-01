// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "RconnectionCopyingInputStream.h"

namespace rprotobuf {
/* N.B. connection must be opened in binary mode due to call
 * to readBin below. */
RconnectionCopyingInputStream::RconnectionCopyingInputStream(int id)
    : connection_id(id), failure(false) {}

/**
 * call readBin to read size bytes from R
 *
 * @param buffer buffer to fill with at most size bytes
 * @param size maximum number of bytes
 *
 * @return the number of bytes actually read
 */
int RconnectionCopyingInputStream::Read(void* buffer, int size) {
    Rcpp::Language call("readBin", connection_id, Rcpp::RawVector(0), size);
    Rcpp::RawVector res;
    try {
        res = call.eval();
    }
    catch (...) {
        /* Failed to read anything from the connection,
         * could have been permissions, or connection opened
         * in the wrong type, etc. */
        failure = true;
        return -1;
    }
    int len = res.size();
    memcpy(buffer, reinterpret_cast<const void*>(res.begin()), len);
    return len;
}
}
