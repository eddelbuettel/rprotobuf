#ifndef RPROTOBUF_ConnectionInputStream_H
#define RPROTOBUF_ConnectionInputStream_H

namespace rprotobuf{

	class ConnectionInputStream : public GPB::io::CopyingInputStreamAdaptor {
		public:	
			ConnectionInputStream( SEXP con, bool was_open ) ;
			~ConnectionInputStream() ;
			
		private:
			bool was_open ;
			SEXP con ;
} ;

} // namespace rprotobuf

#endif
