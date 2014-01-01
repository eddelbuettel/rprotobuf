// -*- indent-tabs-mode: nil; tab-width: 4; show-trailing-whitespace: t; c-indent-level: 4; c-basic-offset: 4; -*-
#include "rprotobuf.h"
#include "RSourceTree.h"

namespace rprotobuf {

RSourceTree::RSourceTree() : directories() {}

GPB::io::ZeroCopyInputStream* RSourceTree::Open(const std::string& filename) {
    /* first, try to open the file as it is */
    int file_descriptor = open(filename.c_str(), O_RDONLY);
    if (file_descriptor < 0) {
        /* then try the directories */
        std::set<std::string>::iterator it;
        it = directories.begin();
        std::string file;
        while (it != directories.end()) {
            file = *it;
            file += "/";
            file += filename;
            file_descriptor = open(file.c_str(), O_RDONLY);
            if (file_descriptor > 0) break;
            ++it;
        }
    }

    if (file_descriptor < 0) {
        return NULL;
    }

    GPB::io::FileInputStream* result = new GPB::io::FileInputStream(file_descriptor);
    result->SetCloseOnDelete(true);
    return result;
}

void RSourceTree::addDirectory(const std::string& directory) { directories.insert(directory); }
void RSourceTree::addDirectories(SEXP dirs) {
    int n = LENGTH(dirs);
    for (int i = 0; i < n; i++) {
        directories.insert(std::string(CHAR(STRING_ELT(dirs, i))));
    }
}

void RSourceTree::removeDirectory(const std::string& directory) { directories.erase(directory); }
void RSourceTree::removeDirectories(SEXP dirs) {
    int n = LENGTH(dirs);
    for (int i = 0; i < n; i++) {
        directories.erase(std::string(CHAR(STRING_ELT(dirs, i))));
    }
}

}  // namespace rprotobuf
