#!/usr/bin/env python
# Jeroen Ooms
#
# HTTPS+ProtoBuf RPC POC using OpenCPU
# The call below maps to: do.call(stats::rnorm, list(n=42, mean=100))
import urllib2;
from rexp_pb2 import *;

#create the post payload, i.e. list(n=42, mean=100)
payload = REXP(
	rclass = 5,
	rexpValue = [
		REXP(rclass = 2, realValue = [42]), 
		REXP(rclass = 2, realValue = [100])
	],
	attrName = [
		"names"
	],
	attrValue = [
		REXP(rclass = 0, stringValue = [STRING(strval="n"), STRING(strval="mean")])
	]
);

#HTTP POST
req = urllib2.Request(
	'https://public.opencpu.org/ocpu/library/stats/R/rnorm/pb', 
	data = payload.SerializeToString(), 
	headers = {
		'Content-type': 'application/x-protobuf'
	}
);
res = urllib2.urlopen(req);
	
#parse output pb
msg = REXP();
msg.ParseFromString(res.read());

#the return value is a double vector in this case
print(msg.realValue);


##### To debug: 
#f = open("payload.msg", "wb")
#f.write(payload.SerializeToString())
#f.close()
#
# Then do in R do:
# library(RProtoBuf)
# payload <- unserialize_pb("payload.msg")
# do.call(stats::rnorm, payload)