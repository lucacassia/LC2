#!/usr/bin/gnuplot

reset

load '../../modules/palette/diverging/RdBu.plt'

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'Mean Squared Displacement N = 100'
set xlabel '{/Symbol h}'
set ylabel 'MSD'

set output 'img/MSD.eps'
plot  1.0/6.0 lc 0 t '1/6', for [i=1:10] sprintf('data/100_%.3f_msd.dat',0.25+i*0.05) u 2:3:4:1  w e ps 0 lc palette notitle,\
      'data/100_0.690_msd.dat' u 2:3:4:1  w e ps 0 lc palette notitle,\
      'data/100_0.710_msd.dat' u 2:3:4:1  w e ps 0 lc palette notitle

set output 'img/MSD2.eps'
plot  'data/100_0.750_msd_long.dat' u 2:3:4  w e ps 0 lc 6 title '{/Symbol h} = 0.75'
