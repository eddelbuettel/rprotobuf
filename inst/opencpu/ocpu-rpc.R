# Jeroen Ooms
#
# HTTPS+ProtoBuf RPC POC using OpenCPU
# The call below maps to: do.call(stats::rnorm, list(n=42, mean=100))

# !! This requires httr (>= 0.2.99). Version 0.2 has a bug.
# library(devtools)
# install_github("httr")

# Actual code
library(RProtoBuf)
library(httr)

args <- list(n=42, mean=100)
payload <- serialize_pb(args, NULL)

req <- POST (
  url = "https://public.opencpu.org/ocpu/library/stats/R/rnorm/pb",
  body = payload,
  add_headers(
  	"Content-Type" = "application/x-protobuf"
  )
)

#This is the output of stats::rnorm(n=42, mean=100)
output <- unserialize_pb(req$content)
print(length(output))
