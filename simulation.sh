#!/bin/bash

filename=all.pcap

rm -rf build/
mkdir build
cd build/
cmake ..
make
cd ../data
../build/bin/main ${filename}
