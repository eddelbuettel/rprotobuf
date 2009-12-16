#include "ZeroCopyOutputStreamWrapper.h"

namespace rprotobuf{
	
	ZeroCopyOutputStreamWrapper::ZeroCopyOutputStreamWrapper( GPB::io::ZeroCopyOutputStream* stream ) : stream(stream){
		coded_stream = new GPB::io::CodedOutputStream(stream);
	}
	
	ZeroCopyOutputStreamWrapper::~ZeroCopyOutputStreamWrapper(){
		/* first clear the coded stream */
		delete coded_stream ;
		
		/* then the stream itself */
		delete stream ; 
	}
	GPB::io::ZeroCopyOutputStream* ZeroCopyOutputStreamWrapper::get_stream(){
		return stream ;
	}
	GPB::io::CodedOutputStream* ZeroCopyOutputStreamWrapper::get_coded_stream(){
		return coded_stream ;
	}

} // namespace rprotobuf

