#!/usr/bin/gnuplot

load '../../modules/parula.pal'

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## integrated autocorrelation time as a function of k_max

set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"

set palette negative defined ( \
    0 '#D53E4F',\
    1 '#F46D43',\
    2 '#FDAE61',\
    3 '#FEE08B',\
    4 '#E6F598',\
    5 '#ABDDA4',\
    6 '#66C2A5',\
    7 '#3288BD' )

## SW
set title '8x8 SW'
set output sprintf('img/8_SW_acr.eps' )
plot for [i=0:12] sprintf('data/8_%.6f_SW_99000.acr', (0.7+i*0.05) ) u 1:2:(0.7+i*0.05) w linespoints pt 1 lc palette notitle


## autocorrelation time as a function of x

set xlabel "x"
set ylabel "{/Symbol t}_{int}"
set xrange[-0.35:0.35]
set yrange[0:10]

set title '8x8 SW'
set output 'img/autocorrelation_time.eps'
plot 'data/8_SW.fit' w linespoints pt 7 ps 1 lc 0 notitle

