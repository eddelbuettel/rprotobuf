#ifndef RPROTOBUF_ZeroCopyInputStreamWrapper_H
#define RPROTOBUF_ZeroCopyInputStreamWrapper_H
#include "rprotobuf.h"

namespace rprotobuf{
	
	/**
	 * simple class that wraps together a ZeroCopyInputStream 
	 * and its associated CodedInputStream. Since we don't expose
	 * CodedInputStream at the R level, this allows to keep only one such 
	 * object with each zero copy input stream
	 */
	class ZeroCopyInputStreamWrapper {
		public:	
			ZeroCopyInputStreamWrapper( GPB::io::ZeroCopyInputStream* stream );
			~ZeroCopyInputStreamWrapper() ;
			
			GPB::io::ZeroCopyInputStream* get_stream(); 
			GPB::io::CodedInputStream* get_coded_stream() ; 
			
		private: 
			GPB::io::ZeroCopyInputStream* stream ;
			GPB::io::CodedInputStream* coded_stream ;
} ;

} // namespace rprotobuf

#endif
