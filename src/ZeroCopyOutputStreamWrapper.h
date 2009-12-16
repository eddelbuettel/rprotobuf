#ifndef RPROTOBUF_ZeroCopyOutputStreamWrapper_H
#define RPROTOBUF_ZeroCopyOutputStreamWrapper_H
#include "rprotobuf.h"

namespace rprotobuf{
	
	/**
	 * simple class that wraps together a ZeroCopyOutputStream 
	 * and its associated CodedOutputStream. Since we don't expose
	 * CodedOutputStream at the R level, this allows to keep only one such 
	 * object with each ZeroCopyOutputStream
	 */
	class ZeroCopyOutputStreamWrapper {
		public:	
			ZeroCopyOutputStreamWrapper( GPB::io::ZeroCopyOutputStream* stream );
			~ZeroCopyOutputStreamWrapper() ;
			
			GPB::io::ZeroCopyOutputStream* get_stream(); 
			GPB::io::CodedOutputStream* get_coded_stream() ; 
			
		private: 
			GPB::io::ZeroCopyOutputStream* stream ;
			GPB::io::CodedOutputStream* coded_stream ;
} ;

} // namespace rprotobuf

#endif
