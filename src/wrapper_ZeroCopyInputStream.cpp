// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"

namespace rprotobuf {

SEXP ZeroCopyInputStream_Next(SEXP xp) {
    BEGIN_RCPP
    GPB::io::ZeroCopyInputStream* stream = GET_ZCIS(xp);
    int s = 0;
    const void* in;
    bool res = stream->Next(&in, &s);
    Rcpp::RawVector result;
    if (!res) {
        throw std::range_error("cannot read from stream");
    } else {
        result.assign(reinterpret_cast<const Rbyte*>(in), reinterpret_cast<const Rbyte*>(in) + s);
    }
    return result;
    END_RCPP
}

SEXP ZeroCopyInputStream_BackUp(SEXP xp, SEXP size) {
    BEGIN_RCPP
    GPB::io::ZeroCopyInputStream* stream = GET_ZCIS(xp);
    int s = GET_int(size, 0);
    if (s <= 0) {
        Rf_error("can only BackUp with positive numbers");
    }
    stream->BackUp(s);
    return R_NilValue;
    END_RCPP
}

SEXP ZeroCopyInputStream_Skip(SEXP xp, SEXP size) {
    BEGIN_RCPP
    GPB::io::ZeroCopyInputStream* stream = GET_ZCIS(xp);
    int s = GET_int(size, 0);
    bool res = stream->Skip(s);
    return (Rf_ScalarLogical(res ? _TRUE_ : _FALSE_));
    END_RCPP
}

SEXP ZeroCopyInputStream_ByteCount(SEXP xp) {
    BEGIN_RCPP
    GPB::io::ZeroCopyInputStream* stream = GET_ZCIS(xp);
    return (Rf_ScalarReal((double)stream->ByteCount()));
    END_RCPP
}
}
