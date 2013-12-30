#include "rprotobuf.h"
#include "ConnectionOutputStream.h"
#include "ConnectionCopyingOutputStream.h"

namespace rprotobuf {

ConnectionOutputStream::ConnectionOutputStream(SEXP con, bool was_open)
    : GPB::io::CopyingOutputStreamAdaptor(
          new ConnectionCopyingOutputStream(con)),
      was_open(was_open),
      con(con) {
    /* clean the wrapped stream on delete */
    SetOwnsCopyingStream(true);
}

ConnectionOutputStream::~ConnectionOutputStream() {
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
