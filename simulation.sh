#!/bin/bash
rm -rf build/
mkdir build
cd build/
cmake ..
make

cd ../data
filecnt=0
echo "select the file you want to simulation :"

for file in `ls | grep .*\.pcap`
do
    echo "${filecnt}. ${file}"
    filecnt=`expr $filecnt + 1`
    files=($files $file)
done

read filenum
filename=${files[$filenum]}
echo "you select ${filenum}. ${filename}"

echo "select the variant :"
echo "0. number of hash"
echo "1. number of cell per hash"
echo "2. number of layer per cell"
read p

if [ $p -eq 0 ] ; then
    xlabel="hash number"
elif [ $p -eq 1 ] ; then
    xlabel="cell number per hash"
elif [ $p -eq 2 ] ; then
    xlabel="layer per cell"
fi

../build/bin/main ${filename} ${p}

echo -e "\nend simulation\n"

echo "set term pdfcairo lw 2 font \"Times New Roman,8\"">../src/script/plotgraph.plt
echo "set output \"result.pdf\"">>../src/script/plotgraph.plt
echo "set xlabel \"${xlabel}\"">>../src/script/plotgraph.plt
echo "set ylabel \"error rate\"">>../src/script/plotgraph.plt
echo "plot \"result.out\" using 1:2 w lp lc 2 lw 2 pt 19 ps 1 title \"kvbf\"">>../src/script/plotgraph.plt
gnuplot ../src/script/plotgraph.plt

evince result.pdf


