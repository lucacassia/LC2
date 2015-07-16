#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## energy

set xlabel "{/Symbol b}"
set ylabel "e"

set output 'img/energy.eps'
set title 'SW'
plot 'data/4_SW.obs'   u 1:2 w l lw 2 lc 4 title '4^2',\
     'data/8_SW.obs'   u 1:2 w l lw 2 lc 7 title '8^2',\
     'data/16_SW.obs'  u 1:2 w l lw 2 lc 1 title '16^2',\
     'data/32_SW.obs'  u 1:2 w l lw 2 lc 3 title '32^2',\


## magnetization

set xlabel "{/Symbol b}"
set ylabel "m"

set output 'img/magnetization.eps'
set title 'SW'
plot 'data/4_SW.obs'   u 1:5 w l lw 2 lc 4 title '4^2',\
     'data/8_SW.obs'   u 1:5 w l lw 2 lc 7 title '8^2',\
     'data/16_SW.obs'  u 1:5 w l lw 2 lc 1 title '16^2',\
     'data/32_SW.obs'  u 1:5 w l lw 2 lc 6 title '32^2',\


## heat capacity

set xlabel "{/Symbol b}"
set ylabel "C"

set output 'img/heat_capacity.eps'
set title 'SW'
plot 'data/4_SW.obs'   u 1:3:4 w errorbars pt 7 lc 4 ps 0.5 title '4^2',\
     'data/8_SW.obs'   u 1:3:4 w errorbars pt 7 lc 7 ps 0.5 title '8^2',\
     'data/16_SW.obs'  u 1:3:4 w errorbars pt 7 lc 1 ps 0.5 title '16^2',\
     'data/32_SW.obs'  u 1:3:4 w errorbars pt 7 lc 6 ps 0.5 title '32^2'


## susceptibility
set logscale y

set xlabel "{/Symbol b}"
set ylabel "{/Symbol c}"

set output 'img/susceptibility.eps'
set title 'SW'
plot 'data/4_SW.obs'   u 1:6:7 w errorbars pt 7 lc 4 ps 0.5 title '4^2',\
     'data/8_SW.obs'   u 1:6:7 w errorbars pt 7 lc 7 ps 0.5 title '8^2',\
     'data/16_SW.obs'  u 1:6:7 w errorbars pt 7 lc 1 ps 0.5 title '16^2',\
     'data/32_SW.obs'  u 1:6:7 w errorbars pt 7 lc 6 ps 0.5 title '32^2'

