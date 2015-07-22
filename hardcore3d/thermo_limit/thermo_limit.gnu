#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'Thermodynamic Limit {/Symbol h} = 0.3'
set xlabel 'N'
set ylabel 'PV/NT-1'
set grid

set output 'img/TL.eps'
plot 'data/0.30_TL.dat' u 1:2:3 w e lc 0 pt 1 notitle

