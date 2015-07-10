#!/bin/bash
#rm -rf build/
mkdir build
cd build/
cmake ..
make

cd ../data
filecnt=0
echo "select the file you want to simulation :"

for file in `ls | grep .*\.dump`
do
    echo "${filecnt}. ${file}"
    filecnt=`expr $filecnt + 1`
    files=(${files[*]} $file)
done

read filenum
filename=${files[$filenum]}
echo "you select ${filenum}. ${filename}"

echo "select the variant :"
echo "0. number of hash"
echo "1. memery size"
echo "2. number of layer per cell"
read p

if [ $p -eq 0 ] ; then
    xlabel="hash number"
elif [ $p -eq 1 ] ; then
    xlabel="cell number"
elif [ $p -eq 2 ] ; then
    xlabel="layer per cell"
fi

../build/bin/main ${filename} ${p}

echo -e "\nend simulation\n"

echo "set term pdfcairo lw 2 font \"Times New Roman,12\"">../src/script/plotgraph.plt
echo "set output \"result_hash_time.pdf\"">>../src/script/plotgraph.plt
echo "set xlabel \"${xlabel}\"">>../src/script/plotgraph.plt
echo "set ylabel \"time\"">>../src/script/plotgraph.plt
echo "plot \"result_statusbf.out\" u 2:8 w lp lc 2 lw 2 pt 19 ps 1 title \"statusbf\",\
    \"result_sbf.out\" u 2:7 w lp lc 3 lw 2 pt 18 ps 1 title \"sbf\",\
    \"result_kbf.out\" u 2:7 w lp lc 4 lw 2 pt 17 ps 1 title \"kbf\""\
    >>../src/script/plotgraph.plt

echo "set output \"result_hash_false_positive.pdf\"">>../src/script/plotgraph.plt
echo "set xlabel \"${xlabel}\"">>../src/script/plotgraph.plt
echo "set ylabel \"false_positive\"">>../src/script/plotgraph.plt
echo "plot \"result_statusbf.out\" u 2:4 w lp lc 2 lw 2 pt 19 ps 1 title \"statusbf\",\
    \"result_sbf.out\" u 2:3 w lp lc 3 lw 2 pt 18 ps 1 title \"sbf\",\
    \"result_kbf.out\" u 2:3 w lp lc 4 lw 2 pt 17 ps 1 title \"kbf\""\
    >>../src/script/plotgraph.plt

echo "set output \"result_hash_false_nagetive.pdf\"">>../src/script/plotgraph.plt
echo "set xlabel \"${xlabel}\"">>../src/script/plotgraph.plt
echo "set ylabel \"false_nagetive\"">>../src/script/plotgraph.plt
echo "plot \"result_statusbf.out\" u 2:5 w lp lc 2 lw 2 pt 19 ps 1 title \"statusbf\",\
    \"result_sbf.out\" u 2:4 w lp lc 3 lw 2 pt 18 ps 1 title \"sbf\",\
    \"result_kbf.out\" u 2:4 w lp lc 4 lw 2 pt 17 ps 1 title \"kbf\""\
    >>../src/script/plotgraph.plt
#echo "plot \"result.out\" u 1:2 w lp lc 2 lw 2 pt 19 ps 1 title \"kvbf\""\
    #>>../src/script/plotgraph.plt
#gnuplot ../src/script/plotgraph.plt

#evince result.pdf


