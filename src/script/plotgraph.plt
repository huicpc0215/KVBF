set term pdfcairo lw 2 font "Times New Roman,16"
set output "result.pdf"
set xlabel "cell number"
set ylabel "error rate"
plot "result.out" u 1:2 w lp lc 2 lw 2 pt 19 ps 1 title "kvbf",    "result.out" u 1:4 w lp lc 4 lw 2 pt 17 ps 1 title "kbf"
