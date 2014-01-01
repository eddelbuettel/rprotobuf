// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"

namespace rprotobuf {

ZeroCopyOutputStreamWrapper::ZeroCopyOutputStreamWrapper(GPB::io::ZeroCopyOutputStream* stream)
    : stream(stream) {
    coded_stream = new GPB::io::CodedOutputStream(stream);
}

ZeroCopyOutputStreamWrapper::~ZeroCopyOutputStreamWrapper() {
    try {
	/* first clear the coded stream */
	delete coded_stream;
	/* then the stream itself */
	delete stream;
    } catch (...) { }
}
GPB::io::ZeroCopyOutputStream* ZeroCopyOutputStreamWrapper::get_stream() { return stream; }
GPB::io::CodedOutputStream* ZeroCopyOutputStreamWrapper::get_coded_stream() { return coded_stream; }

}  // namespace rprotobuf
