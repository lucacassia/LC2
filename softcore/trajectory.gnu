#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'trajectory.eps'
splot 'trajectory.dat' every 10 ps 0.5 pt 7 lc rgb '#0060ad' notitle

