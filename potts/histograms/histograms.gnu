#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set palette negative defined ( \
    0 '#D53E4F',\
    1 '#F46D43',\
    2 '#FDAE61',\
    3 '#FEE08B',\
    4 '#E6F598',\
    5 '#ABDDA4',\
    6 '#66C2A5',\
    7 '#3288BD' )

#load '../../modules/parula.pal'


## levels

set xlabel "Re"
set ylabel "Im"

set yrange[-1:1]
set xrange[-0.75:1.25]
set size ratio 1

set title 'Magnetization Levels 4x4'

set output 'img/levels.eps'
plot 'data/levels.dat' pt 7 lc 6 notitle


## histograms

do for [i=0:10] {
    beta_value = 0.75+i*0.02

    set title '8x8 SW'
    set output sprintf('img/8_%.6f_SW_histogram.eps', beta_value )
    inputfile = sprintf('data/8_%.6f_SW_999000.hist', beta_value )
    plot inputfile  u 1:2:(0.01):3  pt 7 lc palette t sprintf('{/Symbol b} = %.2f', beta_value )
}

