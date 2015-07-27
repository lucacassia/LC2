#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 20

set title 'Mean Squared Displacement N = 256 {/Symbol r} = 0.9'
set xlabel '{/Symbol D}t'
set ylabel 'MSD'


set xrange[0:200]
set output 'img/MSD.eps'
plot 'data/256_0.900_1.087_msd.dat' u 2:3:4 w e ps 0  t "{/Symbol T} = 1.087",\
     'data/256_0.900_0.800_msd.dat' u 2:3:4 w e ps 0  t "{/Symbol T} = 0.800"
     

