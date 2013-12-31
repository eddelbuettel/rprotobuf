#include "rprotobuf.h"

namespace rprotobuf {

ZeroCopyInputStreamWrapper::ZeroCopyInputStreamWrapper(GPB::io::ZeroCopyInputStream* stream)
    : stream(stream) {
    coded_stream = new GPB::io::CodedInputStream(stream);
}

ZeroCopyInputStreamWrapper::~ZeroCopyInputStreamWrapper() {
    try {
	/* first clear the coded stream */
	delete coded_stream;
	/* then the stream itself */
	delete stream;
    } catch (...) { }
}
GPB::io::ZeroCopyInputStream* ZeroCopyInputStreamWrapper::get_stream() { return stream; }
GPB::io::CodedInputStream* ZeroCopyInputStreamWrapper::get_coded_stream() { return coded_stream; }

}  // namespace rprotobuf
