#ifndef RPROTOBUF_ConnectionInputStream_H
#define RPROTOBUF_ConnectionInputStream_H

namespace rprotobuf{

	class ConnectionInputStream : public GPB::io::ZeroCopyInputStream {
		public:	
			ConnectionInputStream( SEXP con, bool was_open );
			~ConnectionInputStream() ;
			
			/* implements ZeroCopyInputStream */
			bool Next( const void** data, int* size ) ;
			void BackUp( int count) ;
			bool Skip(int count);
			int64 ByteCount() const; 
			
		private: 
			bool was_open ;
			SEXP con ;
} ;

} // namespace rprotobuf

#endif
