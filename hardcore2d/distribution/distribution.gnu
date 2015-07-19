#!/usr/bin/gnuplot

reset
set macros

set terminal pdf size 4.5,4.5 enhanced color dashed lw 1

f1(v)=a1*(v/t1)*exp(-v**2/(t1*2)) #module
f2(v)=a2*(v/t2)*exp(-v**2/(t2*2)) #module
f3(v)=a3*(v/t3)*exp(-v**2/(t3*2)) #module

set style line 1 lc rgb '#377eb8'
set style line 2 lc rgb '#4daf4a'
set style line 3 lc rgb '#e41a1c'

set sample 500
set title "Momentum Distribution"
set ylabel "Probability Intensity"
set style fill transparent solid 0.5
set key Left

# call histogram function
binwidth = 0.1
binstart = -100

set xrange[-15:15]
set xlabel "v_x"
set output "img/xdistribution.pdf"
hist = 'u (binwidth*(floor(($1-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'
plot 'data/momentum_100_0.500_1.000.dat'   @hist w filledcurves x1 ls 1 title "T =  1",\
     'data/momentum_100_0.500_4.000.dat'   @hist w filledcurves x1 ls 2 title "T =  4",\
     'data/momentum_100_0.500_16.000.dat'  @hist w filledcurves x1 ls 3 title "T = 16"

set xlabel "v_y"
set output "img/ydistribution.pdf"
hist = 'u (binwidth*(floor(($2-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'
plot 'data/momentum_100_0.500_1.000.dat'   @hist w filledcurves x1 ls 1 title "T =  1",\
     'data/momentum_100_0.500_4.000.dat'   @hist w filledcurves x1 ls 2 title "T =  4",\
     'data/momentum_100_0.500_16.000.dat'  @hist w filledcurves x1 ls 3 title "T = 16"


##module
set xrange[0:15]
set xlabel "|v|"
set output "img/mdistribution.pdf"
hist = 'u (binwidth*(floor(($3-binstart)/binwidth)+0.5)+binstart):(1.0) smooth freq'

# store data in a temporary file for fitting
set table 'hist1.txt'
plot 'data/momentum_100_0.500_1.000.dat' @hist ls 1
unset table
set table 'hist2.txt'
plot 'data/momentum_100_0.500_4.000.dat' @hist ls 1
unset table
set table 'hist3.txt'
plot 'data/momentum_100_0.500_16.000.dat' @hist ls 1
unset table
fit f1(x) 'hist1.txt' u 1:2 via a1,t1
fit f2(x) 'hist2.txt' u 1:2 via a2,t2
fit f3(x) 'hist3.txt' u 1:2 via a3,t3

plot 'data/momentum_100_0.500_1.000.dat'   @hist w filledcurves x1 ls 1 title "T =  1", f1(x) ls 1 notitle,\
     'data/momentum_100_0.500_4.000.dat'   @hist w filledcurves x1 ls 2 title "T =  4", f2(x) ls 2 notitle,\
     'data/momentum_100_0.500_16.000.dat'  @hist w filledcurves x1 ls 3 title "T = 16", f3(x) ls 3 notitle

