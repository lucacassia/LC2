#!/usr/bin/gnuplot

## thermalization
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

load '../../modules/parula.pal'

## energy
set xlabel "Markov time"
set ylabel "E/V"
#set yrange[-2:0]
set xrange[0:100]

do for [k=1:2] {
    l=32*k
    ##SW
    set output sprintf('img/%d_SW_thermalization.eps', l )
    set title sprintf('%dx%d SW',l,l)
    plot for [i=0:4] sprintf('data/%d_%.6f_SW_500.dat', l, 0.5+i*0.25 ) u 1 w l ls (1+i) t sprintf('{/Symbol b} = %.3f', 0.5+i*0.25 )
}

do for [k=1:2] {
    l=32*k
    ##MH
    set output sprintf('img/%d_MH_thermalization.eps', l )
    set title sprintf('%dx%d MH',l,l)
    plot for [i=0:4] sprintf('data/%d_%.6f_MH_500.dat', l, 0.5+i*0.25 ) u 1 w l ls (1+i) t sprintf('{/Symbol b} = %.3f', 0.5+i*0.25 )
}
