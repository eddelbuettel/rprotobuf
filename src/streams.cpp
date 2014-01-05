// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "ConnectionInputStream.h"
#include "ConnectionOutputStream.h"

namespace rprotobuf {

void ZeroCopyInputStreamWrapper_finalizer(SEXP xp) { delete (ZeroCopyInputStreamWrapper*)XPP(xp); }
void ZeroCopyOutputStreamWrapper_finalizer(SEXP xp) {
    delete (ZeroCopyOutputStreamWrapper*)XPP(xp);
}

// {{{ input streams

// {{{ FileInputStream
SEXP FileInputStream_new(SEXP filename, SEXP block_size, SEXP close_on_delete) {
    BEGIN_RCPP
    NEW_S4_OBJECT("FileInputStream");
    int fd = open(CHAR(STRING_ELT(filename, 0)), O_RDONLY | O_BINARY);

    GPB::io::FileInputStream* stream = new GPB::io::FileInputStream(fd, INTEGER(block_size)[0]);
    stream->SetCloseOnDelete(LOGICAL(close_on_delete)[0]);
    ZeroCopyInputStreamWrapper* wrapper = new ZeroCopyInputStreamWrapper(stream);

    SEXP ptr = PROTECT(R_MakeExternalPtr((void*)wrapper, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ptr, ZeroCopyInputStreamWrapper_finalizer, _FALSE_);
    SET_SLOT(oo, Rf_install("pointer"), ptr);

    UNPROTECT(2); /* oo, ptr */
    return oo;
    END_RCPP
}
SEXP FileInputStream_GetErrno(SEXP xp) {
    BEGIN_RCPP
    GPB::io::FileInputStream* stream = GET_FIS(xp);
    return Rf_ScalarInteger(stream->GetErrno());
    END_RCPP
}
SEXP FileInputStream_SetCloseOnDelete(SEXP xp, SEXP close) {
    BEGIN_RCPP
    GPB::io::FileInputStream* stream = GET_FIS(xp);
    stream->SetCloseOnDelete(LOGICAL(close));
    return R_NilValue;
    END_RCPP
}

SEXP FileInputStream_Close(SEXP xp) {
    BEGIN_RCPP
    GPB::io::FileInputStream* stream = GET_FIS(xp);
    bool res = stream->Close();
    return Rf_ScalarLogical(res ? _TRUE_ : _FALSE_);
    END_RCPP
}
// }}}
// {{{ ConnectionInputStream
SEXP ConnectionInputStream_new(SEXP con, SEXP was_open) {
    BEGIN_RCPP
    NEW_S4_OBJECT("ConnectionInputStream");
    ConnectionInputStream* stream = new ConnectionInputStream(con, (bool)LOGICAL(was_open)[0]);
    ZeroCopyInputStreamWrapper* wrapper = new ZeroCopyInputStreamWrapper(stream);
    SEXP ptr = PROTECT(R_MakeExternalPtr((void*)wrapper, R_NilValue, con));
    R_RegisterCFinalizerEx(ptr, ZeroCopyInputStreamWrapper_finalizer, _FALSE_);
    SET_SLOT(oo, Rf_install("pointer"), ptr);

    UNPROTECT(2); /* oo, ptr */
    return oo;
    END_RCPP
}
// }}}
// }}}

// {{{ output streams
// {{{ ZeroCopyOutputStream
SEXP ZeroCopyOutputStream_Next(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::ZeroCopyOutputStream* stream = GET_ZCOS(xp);
    void* out;
    int s = LENGTH(payload);
    bool res = stream->Next(&out, &s);
    if (!res) {
        Rcpp_error("cannot write to stream");
    }
    memcpy(out, RAW(payload), s);
    return Rf_ScalarInteger(s);
    END_RCPP
}

SEXP ZeroCopyOutputStream_ByteCount(SEXP xp) {
    BEGIN_RCPP
    GPB::io::ZeroCopyOutputStream* stream = GET_ZCOS(xp);
    return (Rf_ScalarReal((double)stream->ByteCount()));
    END_RCPP
}

SEXP ZeroCopyOutputStream_BackUp(SEXP xp, SEXP count) {
    BEGIN_RCPP
    GPB::io::ZeroCopyOutputStream* stream = GET_ZCOS(xp);
    int s = GET_int(count, 0);
    stream->BackUp(s);
    return R_NilValue;
    END_RCPP
}
// }}}
// {{{ ArrayOutputStream
// }}}
// {{{ FileOutputStream
SEXP FileOutputStream_new(SEXP filename, SEXP block_size, SEXP close_on_delete) {
    BEGIN_RCPP
    NEW_S4_OBJECT("FileOutputStream");
    int fd = open(CHAR(STRING_ELT(filename, 0)), O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);

    GPB::io::FileOutputStream* stream = new GPB::io::FileOutputStream(fd, INTEGER(block_size)[0]);
    stream->SetCloseOnDelete(LOGICAL(close_on_delete)[0]);
    ZeroCopyOutputStreamWrapper* wrapper = new ZeroCopyOutputStreamWrapper(stream);

    SEXP ptr = PROTECT(R_MakeExternalPtr((void*)wrapper, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ptr, ZeroCopyOutputStreamWrapper_finalizer, _FALSE_);
    SET_SLOT(oo, Rf_install("pointer"), ptr);

    UNPROTECT(2); /* oo, ptr */
    return oo;
    END_RCPP
}
SEXP FileOutputStream_Flush(SEXP xp) {
    BEGIN_RCPP
    GPB::io::FileOutputStream* stream = GET_FOS(xp);
    bool res = stream->Flush();
    return Rf_ScalarLogical(res ? _TRUE_ : _FALSE_);
    END_RCPP
}
SEXP FileOutputStream_Close(SEXP xp) {
    BEGIN_RCPP
    GPB::io::FileOutputStream* stream = GET_FOS(xp);
    bool res = stream->Close();
    return Rf_ScalarLogical(res ? _TRUE_ : _FALSE_);
    END_RCPP
}
SEXP FileOutputStream_GetErrno(SEXP xp) {
    BEGIN_RCPP
    GPB::io::FileOutputStream* stream = GET_FOS(xp);
    return Rf_ScalarInteger(stream->GetErrno());
    END_RCPP
}
SEXP FileOutputStream_SetCloseOnDelete(SEXP xp, SEXP close) {
    BEGIN_RCPP
    GPB::io::FileOutputStream* stream = GET_FOS(xp);
    stream->SetCloseOnDelete(LOGICAL(close));
    return R_NilValue;
    END_RCPP
}
// }}}
// {{{ ConnectionOutputStream
SEXP ConnectionOutputStream_new(SEXP con, SEXP was_open) {
    BEGIN_RCPP
    NEW_S4_OBJECT("ConnectionOutputStream");
    ConnectionOutputStream* stream = new ConnectionOutputStream(con, (bool)LOGICAL(was_open)[0]);
    ZeroCopyOutputStreamWrapper* wrapper = new ZeroCopyOutputStreamWrapper(stream);
    /* we keep the R connection protected as long as the
       external pointer is kept out of GC */
    SEXP ptr = PROTECT(R_MakeExternalPtr((void*)wrapper, R_NilValue, con));
    R_RegisterCFinalizerEx(ptr, ZeroCopyOutputStreamWrapper_finalizer, _FALSE_);
    SET_SLOT(oo, Rf_install("pointer"), ptr);

    UNPROTECT(2); /* oo, ptr */
    return oo;
    END_RCPP
}
// }}}

// }}}

// {{{ Read*** functions using CodedInputStream
SEXP ZeroCopyInputStream_ReadRaw(SEXP xp, SEXP size) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    int s = INTEGER(size)[0];
    SEXP payload = PROTECT(Rf_allocVector(RAWSXP, s));
    if (!coded_stream->ReadRaw(RAW(payload), s)) Rcpp_error("error reading raw bytes");
    UNPROTECT(1); /* payload */
    return payload;
    END_RCPP
}

SEXP ZeroCopyInputStream_ReadString(SEXP xp, SEXP size) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    int s = INTEGER(size)[0];
    std::string buffer("");
    if (!coded_stream->ReadString(&buffer, s)) Rcpp_error("error reading string");

    return Rf_mkString(buffer.c_str());
    END_RCPP
}

SEXP ZeroCopyInputStream_ReadVarint32(SEXP xp) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    uint32 res = 0;
    if (!coded_stream->ReadVarint32(&res)) Rcpp_error("error reading varint32");
    return Rf_ScalarInteger(res);
    END_RCPP
}

SEXP ZeroCopyInputStream_ReadLittleEndian32(SEXP xp) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    uint32 res = 0;
    if (!coded_stream->ReadVarint32(&res)) Rcpp_error("error reading little endian int32");
    return Rf_ScalarInteger(res);
    END_RCPP
}

SEXP ZeroCopyInputStream_ReadLittleEndian64(SEXP xp) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    uint64 res = 0;
    if (!coded_stream->ReadVarint64(&res)) Rcpp_error("error reading little endian int32");
    return Rf_ScalarReal((double)res);
    END_RCPP
}

SEXP ZeroCopyInputStream_ReadVarint64(SEXP xp) {
    BEGIN_RCPP
    GPB::io::CodedInputStream* coded_stream = GET_CIS(xp);
    uint64 res = 0;
    if (!coded_stream->ReadVarint64(&res)) Rcpp_error("error reading varint64");
    return Rf_ScalarReal((double)res);
    END_RCPP
}
// }}}

// {{{ Write*** functions using CodedOuputStream
SEXP ZeroCopyOutputStream_WriteRaw(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteRaw(RAW(payload), LENGTH(payload));
    return R_NilValue;
    END_RCPP
}
SEXP ZeroCopyOutputStream_WriteString(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    if (LENGTH(payload) > 1) {
        Rf_warning("only the first element is used");
    }
    if (LENGTH(payload) == 0) {
        Rcpp_error("need at least one element");
    }
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteString(CHAR(STRING_ELT(payload, 0)));
    return R_NilValue;
    END_RCPP
}

SEXP ZeroCopyOutputStream_WriteLittleEndian32(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteLittleEndian32(GET_int32(payload, 0));
    return R_NilValue;
    END_RCPP
}

SEXP ZeroCopyOutputStream_WriteLittleEndian64(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteLittleEndian64(GET_int64(payload, 0));
    return R_NilValue;
    END_RCPP
}

SEXP ZeroCopyOutputStream_WriteVarint32(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteVarint32(GET_int32(payload, 0));
    return R_NilValue;
    END_RCPP
}

SEXP ZeroCopyOutputStream_WriteVarint64(SEXP xp, SEXP payload) {
    BEGIN_RCPP
    GPB::io::CodedOutputStream* stream = GET_COS(xp);
    stream->WriteVarint64(GET_int64(payload, 0));
    return R_NilValue;
    END_RCPP
}
// }}}

}  // namespace rprotobuf
