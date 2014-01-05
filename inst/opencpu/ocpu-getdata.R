# Jeroen Ooms
#
# HTTPS+ProtoBuf RPC POC using OpenCPU
# Script below downloads MASS::Animals using protobuf
library(RProtoBuf)
library(httr)

req <- GET ('https://public.opencpu.org/ocpu/library/MASS/data/Animals/pb')
output <- unserialize_pb(req$content)
identical(output, MASS::Animals)
