#!/usr/bin/gnuplot

reset
set macros
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 20

f(v)=a*(v**2)*exp(-v**2/(t*2))
t=1
a=1e4

set style line 1 lc rgb '#888888'
set style line 2 lc rgb '#4daf4a'
set style line 3 lc rgb '#e41a1c'

set sample 500
set title "Momentum Distribution"
set ylabel "Probability Intensity"
set style fill transparent solid 0.5

# call histogram function
binwidth = 0.1
binstart = -1

set xrange[0:5]
set xlabel "v"
set output "img/mdistribution.eps"
hist = 'u (binwidth*(floor(($1-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'

# store data in a temporary file for fitting
set table 'hist.txt'
plot 'data/distribution.dat' @hist ls 1
unset table
fit f(x) 'hist.txt' u 1:2 via a,t

plot 'data/distribution.dat'   @hist w boxes ls 1  notitle, f(x) lc 7 lw 3 t sprintf('k_bT = %.6f',t)


##component
a=1e4
t=1
f(x)=a*exp(-x**2/(2*t))

unset xrange
set yrange[0:12000]
set xlabel "x-component of v"
set output "img/xdistribution.eps"
hist = 'u (binwidth*(floor(($2-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'

# store data in a temporary file for fitting
set table 'histx.txt'
plot 'data/distribution.dat' @hist ls 1
unset table
fit f(x) 'histx.txt' u 1:2 via a,t

plot 'data/distribution.dat'   @hist w boxes ls 1  notitle, f(x) lc 7 lw 3 t sprintf('k_bT = %.6f',t)

