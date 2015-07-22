#!/usr/bin/gnuplot

reset

load '../../modules/palette/diverging/RdBu.plt'

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'Mean Squared Displacement N = 100'

set xlabel '{/Symbol D}t'
set ylabel 'MSD'

set output 'img/MSD.eps'
plot  for [i=1:10] sprintf('data/100_%.3f_msd.dat',0.25+i*0.05) u 2:3:4:1 every 10 w e ps 0 lc palette notitle,\
      'data/100_0.690_msd.dat' u 2:3:4:1 every 10 w e ps 0 lc palette notitle,\
      'data/100_0.710_msd.dat' u 2:3:4:1 every 10 w e ps 0 lc palette notitle,\
      1.0/6.0 lc 0 t '1/6'

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/MSD2.eps'
plot  'data/100_0.555_msd.dat' u 2:3:4  every 10 w e ps 0 lc 7 title '{/Symbol h} = 0.555'
set output 'img/MSD3.eps'
plot  'data/100_0.725_msd.dat' u 2:3:4  every 10 w e ps 0 lc 6 title '{/Symbol h} = 0.725'

set title 'Unfolded Mean Squared Displacement N = 100'
set output 'img/MSD4.eps'
plot  'data/100_0.555_unf_msd.dat' u 2:3:4  every 10 w e ps 0 lc 7 title '{/Symbol h} = 0.555'
set output 'img/MSD5.eps'
plot  'data/100_0.725_unf_msd.dat' u 2:3:4  every 10 w e ps 0 lc 6 title '{/Symbol h} = 0.725'


set xlabel 'x'
set ylabel 'y'
set size ratio 1

set xrange[0:1]
set yrange[0:1]

set output 'img/trajectory1.eps'
set title 'Trajectory N = 100 {/Symbol h} = 0.555'
plot "data/position_50_100_0.555000.dat" u 3:4:2 every 10 pt 7 ps 0.1 lc 7 notitle

set output 'img/trajectory2.eps'
set title 'Trajectory N = 100 {/Symbol h} = 0.725'
plot "data/position_50_100_0.725000.dat" u 3:4:2 every 10 pt 7 ps 0.1 lc 6 notitle

unset xrange
unset yrange

set output 'img/trajectory1u.eps'
set title 'Unfolded Trajectory N = 100 {/Symbol h} = 0.555'
plot "data/position_50_100_0.555000.dat" u 5:6:2 every 10 pt 7 ps 0.1 lc 7 notitle

set output 'img/trajectory2u.eps'
set title 'Unfolded Trajectory N = 100 {/Symbol h} = 0.725'
plot "data/position_50_100_0.725000.dat" u 5:6:2 every 10 pt 7 ps 0.1 lc 6 notitle

