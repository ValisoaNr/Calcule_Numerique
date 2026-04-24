set xzeroaxis
set yzeroaxis
set pointsize 0.2
set ylabel "abscisses"
set xlabel "ordonnees"
set xrange [1.000000:3.000000]
set yrange [-1:1]
plot log(x)-1 title "log(x)-1" with lines
replot "solution.txt" using 1:2 title "approxm" with points pt 1 ps 1.2
