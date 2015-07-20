#!/usr/bin/gnuplot

reset
set macros

set terminal pdf size 6,4.5 enhanced color dashed lw 1

set style line 1 lc rgb '#377eb8'
set style line 2 lc rgb '#4daf4a'
set style line 3 lc rgb '#e41a1c'

set title "Collision Time Distribution N = 100"
set ylabel "Probability Intensity"
set xlabel "t_c"
set output "img/collision_time.pdf"

set style fill transparent solid 0.5

# call histogram function
binwidth = 0.00001
binstart = 0

set xrange[0:0.002]

hist = 'u (binwidth*(floor(($1-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq w filledcurves x1'
plot for [i=1:4] sprintf('data/100_%.3f_times.dat',0.9-i*0.15) @hist ls i title sprintf("{/Symbol h} = %.2f",0.9-i*0.15)
