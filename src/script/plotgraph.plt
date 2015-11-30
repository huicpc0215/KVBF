set term pdfcairo lw 2 font "Times-New Roman-Bold,14"
#set key left box
set key box
set ytics
set output "result_hash_time.pdf"
set xlabel "hash number" font "Times-New Roman-Bold,18"
set ylabel "time" font "Times-New Roman-Bold,18"
set format y "%0.1e"
#set format y "%2.0t*10^%L"
set key at 10,0.000009
plot "result_statusbf.out" u 2:8 w lp lc 2 lw 4 pt 19 ps 1.3 title "stateBF",    "result_sbf.out" u 2:7 w lp lc 3 lw 4 pt 18 ps 1.3 title "sbf",    "result_kbf.out" u 2:7 w lp lc 4 lw 4 pt 17 ps 1.3 title "kbf"
set mytics 2
set output "result_hash_false_positive.pdf"
set xlabel "hash number"
set ylabel "false positive"
set format y "%0.3f"
set key at 9,0.02
plot "result_statusbf.out" u 2:4 w lp lc 2 lw 4 pt 19 ps 1.3 title "stateBF",    "result_sbf.out" u 2:3 w lp lc 3 lw 4 pt 18 ps 1.3 title "sbf",    "result_kbf.out" u 2:3 w lp lc 4 lw 4 pt 17 ps 1.3 title "kbf"
set output "result_hash_false_negative.pdf"
set xlabel "hash number"
set ylabel "false negative"
set key at 9,0.35
plot "result_statusbf.out" u 2:5 w lp lc 2 lw 4 pt 19 ps 1.3 title "stateBF",    "result_sbf.out" u 2:4 w lp lc 3 lw 4 pt 18 ps 1.3 title "sbf",    "result_kbf.out" u 2:4 w lp lc 4 lw 4 pt 17 ps 1.3 title "kbf"
