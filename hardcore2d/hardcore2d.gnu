#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## lattice

set xlabel "x"
set ylabel "y"

set size ratio 1

set title 'Circle Packing'

set output 'img/packing.eps'
plot 'data/position.dat' ps 5 pt 7 lc 6 notitle

