#ifndef RPROTOBUF_RconnectionCopyingInputStream_H
#define RPROTOBUF_RconnectionCopyingInputStream_H

namespace rprotobuf {

class RconnectionCopyingInputStream : public GPB::io::CopyingInputStream {
   public:
    RconnectionCopyingInputStream(int id);

    int Read(void* buffer, int size);
    bool Failure() const { return (failure); }

   private:
    int connection_id;
    bool failure;
};

}  // namespace rprotobuf

#endif
