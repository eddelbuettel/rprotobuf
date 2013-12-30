#ifndef RPROTOBUF_ConnectionCopyingOutputStream_H
#define RPROTOBUF_ConnectionCopyingOutputStream_H

namespace rprotobuf {

class ConnectionCopyingOutputStream : public GPB::io::CopyingOutputStream {
   public:
    ConnectionCopyingOutputStream(SEXP con);
    bool Write(const void* buffer, int size);

   private:
    /*
            the actual connection object from R
            it is protected by the external pointer that
            wraps the ConnectionInputStream, which is the only
            thing that uses this class, so we don't need to take
            care of GC here
    */
    SEXP con;

    Rcpp::Function writeBin;
};

}  // namespace rprotobuf

#endif
