#!/usr/bin/gnuplot

reset
set macros

set terminal pdf size 6,4.5 enhanced color dashed lw 1

set style line 1 lc rgb '#377eb8'
set style line 2 lc rgb '#4daf4a'
set style line 3 lc rgb '#e41a1c'

set title "Mean Free Path Distribution N = 100"
set ylabel "Probability Intensity"
set xlabel "mean free path"
set output "img/mean_free_path.pdf"

set style fill transparent solid 0.5

# call histogram function
binwidth = 0.00001
binstart = 0

set xrange[0:0.002]

hist = 'u (binwidth*(floor(($1-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq w filledcurves x1'
plot for [i=1:4] sprintf('data/100_%.3f_mfp.dat',0.9-i*0.15) @hist ls i title sprintf("{/Symbol h} = %.2f",0.9-i*0.15)

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set output 'img/mean_free_path_fit.eps'

set table 'hist.txt'
plot 'data/100_0.300_mfp.dat' @hist ls 1
unset table
a= 15000
t=0.0005
f(x)=a*exp(-x/t)
fit f(x) 'hist.txt' u 1:2 via a,t
unset xrange

plot 'data/100_0.300_mfp.dat' @hist ls 4 t '{/Symbol h} = 0.30', f(x) lc 6 t sprintf('{/Symbol t} = %.6f',t)

