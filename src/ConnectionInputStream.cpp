// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "ConnectionInputStream.h"
#include "ConnectionCopyingInputStream.h"

namespace rprotobuf {

ConnectionInputStream::ConnectionInputStream(SEXP con, bool was_open)
    : GPB::io::CopyingInputStreamAdaptor(new ConnectionCopyingInputStream(con)),
      was_open(was_open),
      con(con) {
    /* clean the wrapped stream on delete */
    SetOwnsCopyingStream(true);
}

ConnectionInputStream::~ConnectionInputStream() {
    if (!was_open) {
        /* then we need to close it */
        SEXP call = PROTECT(Rf_lang2(Rf_install("close"), con));
        Rf_eval(call, R_GlobalEnv);
        UNPROTECT(1); /* call */
    }
    /* con will be disposed by the R GC, it is
       protected as part of the protection of the
       external pointer that wraps this */
}

}  // namespace rprotobuf
