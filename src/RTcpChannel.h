#ifndef RPROTOBUF_RTCPCHANNEL_H
#define RPROTOBUF_RTCPCHANNEL_H
#include "rprotobuf.h"
#include "protobufrpc.pb.h" 
#include <sys/types.h>
#include <sys/socket.h>

namespace rprotobuf {

	class RTcpChannel : public RpcChannel {
		public:
			RTcpChannel() ;
			
			void CallMethod(const MethodDescriptor* method,
                          RpcController* controller,
                          const Message* request,
                          Message* response,
                          Closure* done) ;
			
            void connect(const char* host, int port) ;
            
		private:
			/* the socket descriptor */
			int socket_id ;
			
			/* rpc id */
			static uint32 id ;
	} ;
	
} // namespace rprotobuf

#endif
