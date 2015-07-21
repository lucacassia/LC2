#!/usr/bin/gnuplot

reset
set macros
set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

f(v)=a*(v/t)*exp(-v**2/(t*2))

set style line 1 lc rgb '#377eb8'
set style line 2 lc rgb '#4daf4a'
set style line 3 lc rgb '#e41a1c'

set sample 500
set title "Momentum Distribution"
set ylabel "Probability Intensity"
set style fill transparent solid 0.5

# call histogram function
binwidth = 0.1
binstart = -100

#set xrange[0:15]
set xlabel "|v|"
set output "img/mdistribution.pdf"
hist = 'u (binwidth*(floor(($3-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'

# store data in a temporary file for fitting
set table 'hist.txt'
plot 'data/momentum_128_0.500_1.000.dat' @hist ls 1
unset table
fit f(x) 'hist.txt' u 1:2 via a,t

plot 'data/momentum_128_0.500_1.000.dat'   @hist w boxes ls 1  notitle, f(x) lc 7 lw 2 t sprintf('k_bT = %.6f',t)

