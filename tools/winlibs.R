# Build against protobuf libs compiled with Rtools
VERSION <- commandArgs(TRUE)
if (!file.exists(sprintf("../windows/protobuf-%s/include/google/protobuf/descriptor.h", VERSION))) {
    if (getRversion() < "3.3.0") setInternet2()
    download.file(sprintf("https://github.com/rwinlib/protobuf/archive/v%s.zip", VERSION), "lib.zip", quiet = TRUE)
    dir.create("../windows", showWarnings = FALSE)
    unzip("lib.zip", exdir = "../windows")
    unlink("lib.zip")
}
