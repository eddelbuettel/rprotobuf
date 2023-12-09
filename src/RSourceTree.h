#ifndef RPROTOBUF_RSourceTree_H
#define RPROTOBUF_RSourceTree_H

namespace rprotobuf {
class RSourceTree : public GPB::compiler::SourceTree {
   public:
    RSourceTree();
    #if GOOGLE_PROTOBUF_VERSION < 4022000
        GPB::io::ZeroCopyInputStream* Open(const std::string& filename);
    #else
        GPB::io::ZeroCopyInputStream* Open(absl::string_view filename);
    #endif
    void addDirectory(const std::string& directory);
    void addDirectories(SEXP dirs);
    void removeDirectory(const std::string& directory);
    void removeDirectories(SEXP dirs);
    void removeAllDirectories();

   private:
    std::set<std::string> directories;
};

}  // namespace rprotobuf

#endif
