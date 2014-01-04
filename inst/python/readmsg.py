#!/usr/bin/env python
#
# Simple test script to read a serialized message in python
#
import rexp_pb2;
import glob;

messages = glob.glob("*.msg");
for myfile in messages:
	print("Reading message " + myfile + " ...")
	f = open(myfile, 'rb')
	msg = rexp_pb2.REXP();	
	msg.ParseFromString(f.read())
	f.close();
	print(msg)
	del msg
