#ifndef RPROTOBUF_SocketCopyingInputStream_H
#define RPROTOBUF_SocketCopyingInputStream_H

/* FIXME: this should be probably handled by sisocks
          we need it for the TCP_NODELAY socket option */
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "sisocks.h"

namespace rprotobuf {

class SocketCopyingInputStream : public GPB::io::CopyingInputStream {
   public:
    SocketCopyingInputStream(int socket_id);

    int Read(void* buffer, int size);

   private:
    int socket_id;
};

}  // namespace rprotobuf

#endif
