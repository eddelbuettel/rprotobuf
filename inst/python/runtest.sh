#!/bin/sh

#write some PB data with R
Rscript writemsg.R

#compile proto file
cp -f ../proto/rexp.proto .
protoc rexp.proto --python_out=.
rm rexp.proto

#read with python and print
python readmsg.py

#cleanup tmp files
rm rexp_pb2.py rexp_pb2.pyc
rm *.msg
