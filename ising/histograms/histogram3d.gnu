#!/usr/bin/gnuplot

reset

set terminal postscript eps size 4.5,3.5 enhanced color dashed lw 1 "DejaVuSans" 12

set pm3d depthorder hidden3d 1
set hidden3d
#set style fill transparent solid 0.65
#set palette rgb 9,9,3
#unset colorbox
#unset key
#unset border
#unset tics
set ticslevel 0
#set view 60,210,1.5,1
#set isosamples 19,44

set xlabel "{/Symbol b}"
set ylabel "m"

load 'parula.pal'

set output 'img/8_MH_histogram3d.eps'
splot "data/8_MH.3d" ls 1 w pm3d t '8x8 MH'
