#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set title 'Mean Squared Displacement N = 250'
set xlabel '{/Symbol D}t'
set ylabel 'MSD'

set output 'img/MSD.eps'
plot for [i=1:8] sprintf('data/250_%.3f_msd.dat',0.25+i*0.05) u 2:3:4 every 10 w e ps 0 lc i+2 t sprintf("{/Symbol h} = %.2f",0.25+i*0.05),\
                 1.0/4.0 lc 0 t '1/4'


set xlabel 'x'
set ylabel 'y'
set zlabel 'z'
do for[i=1:8]{
    set title sprintf('{/Symbol h} = %.2f',0.25+i*0.05)
    set output sprintf('img/trajectory_%.2f.eps',0.25+i*0.05)
    splot sprintf('data/position_125_250_%.6f.dat',0.25+i*0.05) u 3:4:5 every 100 ps 0.5 pt 7 lc 6 notitle
}
