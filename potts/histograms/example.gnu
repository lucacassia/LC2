#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set xlabel "Re"
set ylabel "Im"

set title 'Magnetization Levels 4x4'
set yrange[-1:1]
set xrange[-0.75:1.25]
set size ratio 1

set output 'img/example.eps'
plot 'data/example.dat' pt 7 lc 6 notitle
