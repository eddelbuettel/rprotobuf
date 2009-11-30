#include "rprotobuf.h"
#include "SocketCopyingInputStream.h"

namespace rprotobuf{
	
	SocketCopyingInputStream::SocketCopyingInputStream(int id){
		socket_id = id ;
	}
	
	/** 
	 * read from the socket
	 * 
	 * @param buffer buffer to fill with at most size bytes
	 * @param size maximum number of bytes
	 *
	 * @return the number of bytes actually read
	 */
	int	SocketCopyingInputStream::Read(void * buffer, int size){
		int received = recv( socket_id, buffer, size, 0 ) ; 
		if( received < 0 ) THROW_SOCKET_ERROR( "recv" ) ;
		return received ;
	}
	
	
}

