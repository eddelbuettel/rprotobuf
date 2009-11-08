#ifndef RPROTOBUF_RconnectionCopyingInputStream_H
#define RPROTOBUF_RconnectionCopyingInputStream_H

namespace rprotobuf{

	class RconnectionCopyingInputStream : public io::CopyingInputStream {
		public:	
			RconnectionCopyingInputStream( int id );
	
			int Read(void * buffer, int size) ;
	
		private: 
			int connection_id ;
} ;

} // namespace rprotobuf

#endif
