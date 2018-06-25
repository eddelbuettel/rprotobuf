# Build against protobuf libs compiled with Rtools
# by Jeroen Ooms. Last updated: June 2018 (for gcc 8.1.0)
if (!file.exists("../windows/protobuf-3.5.1/include/google/protobuf/descriptor.h")) {
    if (getRversion() < "3.3.0") setInternet2()
    download.file("https://github.com/rwinlib/protobuf/archive/v3.5.1.zip", "lib.zip", quiet = TRUE)
    dir.create("../windows", showWarnings = FALSE)
    unzip("lib.zip", exdir = "../windows")
    unlink("lib.zip")
}
