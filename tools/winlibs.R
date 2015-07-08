# Build against libprotobuf libraries that were compiled with the Rtools gcc toolchain
# by Jeroen Ooms. Last updated: December 2014.
if(!file.exists("../windows/protobuf-2.6.1/include/google/protobuf/descriptor.h")){
  setInternet2()
  download.file("https://github.com/rwinlib/libprotobuf/archive/v2.6.1.zip", "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
