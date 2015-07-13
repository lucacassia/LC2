#!/usr/bin/gnuplot

## histograms

load 'parula.pal'

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

#set pm3d depthorder hidden3d 1
#set hidden3d
#set ticslevel 0

set pm3d at b      # draw on bottom, not as 3d surface
set view map       # don't do a 3-d looking plot
#set dgrid 100,100  # grid of 100x100 pixels

set xlabel "Re(m)"
set ylabel "Im(m)"

do for [i=0:7] {
    beta_value = 0.8+i*0.05

    ##SW
    set output sprintf('img/8_%.6f_SW_histogram.eps', beta_value )
    inputfile = sprintf('data/8_%.6f_SW_999000.hist', beta_value )
    splot inputfile ls 1 w pm3d t sprintf('8x8 SW \@ {/Symbol b} = %.3f', beta_value )
}

set title 'Magnetization 4x4 SW'
set xrange[-1:1]
set yrange[-1:1]

#set output 'img/8_SW_histogram.eps'
#plot 'data/4_1.005053_SW_1000000.dat' u 2:3 pt 7 lc 7 notitle
