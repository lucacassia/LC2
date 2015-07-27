#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 20


##internal energy
set title 'Potential Energy'

set ylabel 'U/N'
set xlabel 'time'

set xrange[10:110]
set output 'img/obsU.eps'
plot "data/output" u 1:3 w l lc 1 lw 2 t 'N = 108'


##temperature
set title 'Temperature'

set ylabel 'kT'
set xlabel 'time'

set xrange[10:110]
set output 'img/obsT.eps'
plot "data/output" u 1:5 w l lc 3 lw 2 t 'N = 108'


##pressure
set title 'Pressure'

set ylabel 'PV/NkT-1'
set xlabel 'time'

set xrange[10:110]
set yrange[-4:4]
set output 'img/obsP.eps'
plot "data/pressure.dat" w l lc 3 lw 2 t 'N = 108'


##all
set title 'N = 108 {/Symbol r} = 0.6'
set xlabel 'time'
unset ylabel

set yrange[-4:3]
set xrange[10:110]
set output 'img/obsA.eps'
plot "data/output" u 1:4 w l lc 6 t 'K/N',\
     "data/output" u 1:5 w l lc 3 t 'T',\
     "data/output" u 1:2 w l lc 7 t 'H/N',\
     "data/output" u 1:3 w l lc 1 t 'U/N'
     





