#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'N = 250'
set xlabel '{/Symbol h}'
set grid

## pressure

set ylabel 'pressure'
set output 'img/pressure.eps'
plot 'data/250_multi.sort' u 1:2  w l lc rgb "#FF0000" notitle,\
     'data/250_multi.sort' u 1:2:3 w e lc 0 pt 1 notitle

