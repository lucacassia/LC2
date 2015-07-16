#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

color = "4 7 1 3 6"

## energy

set xlabel "{/Symbol b}"
set ylabel "e"

set output 'img/energy.eps'
set title 'SW'
plot for [i=1:words(color)] sprintf('data/%d_SW.obs',2*(2**i)) u 1:2 w l lw 2 lc word(color, i) title sprintf('%d^2',2*(2**i))


## magnetization

set xlabel "{/Symbol b}"
set ylabel "m"

set output 'img/magnetization.eps'
set title 'SW'
plot for [i=1:words(color)] sprintf('data/%d_SW.obs',2*(2**i)) u 1:5 w l lw 2 lc word(color, i) title sprintf('%d^2',2*(2**i))


## susceptibility
set logscale y

set xlabel "{/Symbol b}"
set ylabel "{/Symbol c}"

set output 'img/susceptibility.eps'
set title 'SW'
plot for [i=1:words(color)] sprintf('data/%d_SW.obs',2*(2**i)) u 1:6:7 w e pt 7 ps 0.5 lc word(color, i) title sprintf('%d^2',2*(2**i))


## heat capacity

set xrange[0.8:1.1]
set xlabel "{/Symbol b}"
set ylabel "C"

set output 'img/heat_capacity.eps'
set title 'SW'
plot for [i=1:words(color)] sprintf('data/%d_SW.obs',2*(2**i)) u 1:3:4 w e pt 7 ps 0.5 lc word(color, i) title sprintf('%d^2',2*(2**i))

