# Build against libprotobuf libraries that were compiled with the Rtools gcc toolchain
# by Jeroen Ooms. Last updated: December 2014.
if (!file.exists("../windows/protobuf-2.6.1/include/google/protobuf/descriptor.h")) {
    if (getRversion() < "3.3.0") setInternet2()
    download.file("https://github.com/rwinlib/protobuf/archive/v2.6.1.zip", "lib.zip", quiet = TRUE)
    dir.create("../windows", showWarnings = FALSE)
    unzip("lib.zip", exdir = "../windows")
    unlink("lib.zip")
}
