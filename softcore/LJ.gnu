#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 20

set style line 1 lw 2 lc rgb '#e41a1c'

set title 'Truncated Lennard-Jones Potential'
set ylabel 'U/{/Symbol e}'
set xlabel 'r/{/Symbol s}'

U(x)=4*(1/(x**12)-1/(x**6))
F(x)=24*(2/(x**13)-1/(x**7))

set xrange[0.5:2.5]
set yrange[-1.5:1.5]
set sample 40000

set output 'LJ.eps'
plot 0 lc 0 notitle,\
     U(x)-U(2.5)+(x-2.5)*F(2.5) lc 6 lw 3 notitle
