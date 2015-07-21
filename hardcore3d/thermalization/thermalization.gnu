#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set style line 1 lw 2 lc rgb '#e41a1c'
set style line 2 lw 2 lc rgb '#377eb8'
set style line 3 lw 2 lc rgb '#4daf4a'
set style line 4 lw 2 lc rgb '#984ea3'
set style line 5 lw 2 lc rgb '#ff7f00'


## thermalization

set ylabel 'pressure'
set xlabel 'collisions'

set title 'N = 128'
set xrange[0:10000]
set output 'img/thermalization1.eps'
plot for [i=1:5] sprintf('data/128_%.6f.dat',0.15+i*0.1) u 2:3 w l ls i t sprintf('{/Symbol h} = %.2f',0.15+i*0.1)
set xrange[0:100000]
set output 'img/thermalization2.eps'
plot for [i=1:5] sprintf('data/128_%.6f.dat',0.15+i*0.1) u 2:3 w l ls i t sprintf('{/Symbol h} = %.2f',0.15+i*0.1)


set ylabel 'mean free path'
set xlabel 'collisions'

set title 'N = 128'
set xrange[0:10000]
set output 'img/thermalization5.eps'
plot for [i=1:5] sprintf('data/128_%.6f.dat',0.15+i*0.1) u 2:4 w l ls i t sprintf('{/Symbol h} = %.2f',0.15+i*0.1)
set xrange[0:100000]
set output 'img/thermalization6.eps'
plot for [i=1:5] sprintf('data/128_%.6f.dat',0.15+i*0.1) u 2:4 w l ls i t sprintf('{/Symbol h} = %.2f',0.15+i*0.1)

