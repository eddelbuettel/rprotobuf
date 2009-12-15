#ifndef RPROTOBUF_ConnectionOutputStream_H
#define RPROTOBUF_ConnectionOutputStream_H

namespace rprotobuf{

	class ConnectionOutputStream : public GPB::io::CopyingOutputStreamAdaptor {
		public:	
			ConnectionOutputStream( SEXP con, bool was_open ) ;
			~ConnectionOutputStream() ;
			
		private:
			bool was_open ;
			SEXP con ;
} ;

} // namespace rprotobuf

#endif
