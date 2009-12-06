#ifndef RPROTOBUF_SocketCopyingInputStream_H
#define RPROTOBUF_SocketCopyingInputStream_H

#include <sys/types.h>
#include <sys/socket.h>

#include "sisocks.h"

/* FIXME: this should be probably handled by sisocks
          we need it for the TCP_NODELAY socket option */
#include <netinet/tcp.h>

namespace rprotobuf{

	class SocketCopyingInputStream : public GPB::io::CopyingInputStream {
		public:	
			SocketCopyingInputStream( int socket_id );
	
			int Read(void * buffer, int size) ;
	
		private: 
			int socket_id ;
			
} ;

} // namespace rprotobuf

#endif
