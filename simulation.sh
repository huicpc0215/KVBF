#!/bin/bash
rm -rf build/
mkdir build
cd build/
cmake ..
make

cd ../data
filecnt=0
echo "select the file you want to simulation:"

for file in `ls | grep .*\.pcap`
do
    echo "${filecnt}. ${file}"
    filecnt=`expr $filecnt + 1`
    files=($files $file)
done

read filenum
filename=${files[$filenum]}
echo "you select ${filenum}. ${filename}"

echo -e "\nstart simulation\n"
../build/bin/main ${filename}
echo -e "\nend simulation\n"


