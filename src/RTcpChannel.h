#ifndef RPROTOBUF_RTCPCHANNEL_H
#define RPROTOBUF_RTCPCHANNEL_H
#include "rprotobuf.h"
#include "protobufrpc.pb.h" 
#include "SocketCopyingInputStream.h"

#include <sys/types.h>
#include <sys/socket.h>

#include "sisocks.h"

/* FIXME: this should be probably handled by sisocks
          we need it for the TCP_NODELAY socket option */
#include <netinet/tcp.h>

namespace rprotobuf {

	class RTcpChannel : public RpcChannel {
		public:
			RTcpChannel() ;
			
			void CallMethod(const MethodDescriptor* method,
                          RpcController* controller,
                          const Message* request,
                          Message* response,
                          Closure* done) ;
			
            int connect_socket(const char* host, int port) ;
            bool is_connected() ; 
            int getSocketId() ;
            
		private:
			int send_(SEXP payload) ;
			int send_rpc(Rpc* rpc) ;
			int read_response( Rpc* response) ;
			void reset() ;
			void socketError() ; 
			
			/* the socket descriptor */
			int socket_id ;
			
			/* rpc id */
			static uint32 id ;
	} ;
	
} // namespace rprotobuf

#endif
