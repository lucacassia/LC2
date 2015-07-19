#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

load '../modules/palette/diverging/RdBu.plt'

set xlabel 'pressure'
set ylabel 'collisions'

set title 'Thermalization T = 1.0'
set output 'img/thermalization1.eps'
plot 'data/thermalization.dat' u 2:3:1 w l lc palette notitle

set xlabel 'mean free path'
set ylabel 'collisions'

set title 'Thermalization T = 1.0'
set output 'img/thermalization2.eps'
plot 'data/thermalization.dat' u 2:4:1 w l lc palette notitle
