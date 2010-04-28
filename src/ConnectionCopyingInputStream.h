#ifndef RPROTOBUF_ConnectionCopyingInputStream_H
#define RPROTOBUF_ConnectionCopyingInputStream_H

namespace rprotobuf{

	class ConnectionCopyingInputStream : public GPB::io::CopyingInputStream {
		public:	
			ConnectionCopyingInputStream( SEXP con );
			int Read(void * buffer, int size) ;
	
		private: 
			/* 
			 	the actual connection object from R
				it is protected by the external pointer that 
				wraps the ConnectionInputStream, which is the only 
				thing that uses this class, so we don't need to take
				care of GC here
			*/
			SEXP con ;
			
			Rcpp::Function readBin ;
} ;

} // namespace rprotobuf

#endif
