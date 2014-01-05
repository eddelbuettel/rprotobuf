#!/usr/bin/env python
# Jeroen Ooms
#
# HTTPS+ProtoBuf RPC POC using OpenCPU
# Script below downloads MASS::Animals using protobuf
import urllib2;
from rexp_pb2 import *;

#HTTP GET
req = urllib2.Request('https://public.opencpu.org/ocpu/library/MASS/data/Animals/pb');
res = urllib2.urlopen(req);
	
#parse output pb
msg = REXP();
msg.ParseFromString(res.read());

#the return value is a double vector in this case
print(msg);
