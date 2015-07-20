#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'N = 100'
set xlabel '{/Symbol h}'
set grid

## pressure

set ylabel 'pressure'
set output 'img/pressure.eps'
plot 'data/100_multi.sort' u 1:2  w l lc rgb "#FF0000" notitle,\
     'data/100_multi.sort' u 1:2:3 w e lc 0 pt 1 notitle

set ylabel 'mean collision time'
set output 'img/mct.eps'
plot 'data/100_multi.sort' u 1:4  w l lc rgb "#FF0000" notitle,\
     'data/100_multi.sort' u 1:4 lc 0 pt 1 notitle

set ylabel 'mean free path'
set output 'img/mfp.eps'
plot 'data/100_multi.sort' u 1:6  w l lc rgb "#FF0000" notitle,\
     'data/100_multi.sort' u 1:6 lc 0 pt 1 notitle

