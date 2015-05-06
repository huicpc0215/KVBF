#!/bin/bash

filename=all.pcap

rm -rf build/
mkdir build
cd build/
cmake ..
make
cd ../data
echo -e "\nstart proceed origin data\n"
../build/bin/main ${filename}
echo -e "\nproceed data finish\n"


