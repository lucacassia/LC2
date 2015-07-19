#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

load '../../modules/palette/diverging/RdBu.plt'

## packing

set xlabel "x"
set ylabel "y"

set size ratio 1

set title 'Circle Packing'

set output 'img/packing.eps'
plot 'data/position_100_0.500000.dat' ps 1 pt 7 lc 6 notitle

## thermalization

set ylabel 'pressure'
set xlabel 'collisions'

set title 'N = 100'
set output 'img/thermalization1.eps'
plot 'data/thermalization_100_1.000000.dat' u 2:3:1 w l lc palette notitle

set title 'N = 400'
set output 'img/thermalization2.eps'
plot 'data/thermalization_400_1.000000.dat' u 2:3:1 w l lc palette notitle

set ylabel 'mean free path'
set xlabel 'collisions'

set title 'N = 100'
set output 'img/thermalization3.eps'
plot 'data/thermalization_100_1.000000.dat' u 2:4:1 w l lc palette notitle

set title 'N = 400'
set output 'img/thermalization4.eps'
plot 'data/thermalization_400_1.000000.dat' u 2:4:1 w l lc palette notitle
