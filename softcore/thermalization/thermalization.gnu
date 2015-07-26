#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 20

set style line 1 lw 2 lc rgb '#FF0000'
set style line 2 lw 2 lc rgb '#00FF00'
set style line 3 lw 2 lc rgb '#0000FF'


## thermalization

set ylabel 'H/N'
set xlabel 'time'

set xrange[0:20]
set output 'img/thermalizationH.eps'
plot "data/output.108" u 1:2 w l ls 1 t 'N = 108',\
     "data/output.250" u 1:2 w l ls 2 t 'N = 250',\
     "data/output.500" u 1:2 w l ls 3 t 'N = 500'

set ylabel 'U/N'
set xlabel 'time'

set xrange[0:5]
set output 'img/thermalizationU.eps'
plot "data/output.108" u 1:3 w l ls 1 t 'N = 108',\
     "data/output.250" u 1:3 w l ls 2 t 'N = 250',\
     "data/output.500" u 1:3 w l ls 3 t 'N = 500'

##fluctuations

set ylabel 'U/N'
set xlabel 'time'

set xrange[10:110]
set output 'img/fluctuationsU.eps'
plot "data/log.108" u 1:3 w l ls 1 t 'N = 108',\
     "data/log.250" u 1:3 w l ls 2 t 'N = 250',\
     "data/log.500" u 1:3 w l ls 3 t 'N = 500'

