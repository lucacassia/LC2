#!/usr/bin/gnuplot

reset
set macros

set xlabel "m"
set ylabel "P(m)"

# eps
set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

# colors
set style line 2 lt 1 lc rgb '#909090' # light grey

unset key

# axes
set style line 11 lc rgb '#000000' lt 1
set border 3 front ls 11
set tics nomirror out scale 0.75

# call histogram function

binwidth = 0.002
binstart = -0.001
load 'hist.fct'

set output 'img/pdf_m_0.30_MH.eps'
set title 'MH \@ {/Symbol b} = 0.30'
plot 'data/magnetization_bin_1000_0.300000_MH.dat' i 0 @hist ls 2

binwidth = 0.00014
binstart = -0.00007
load 'hist.fct'

set output 'img/pdf_m_0.80_MH.eps'
set title 'MH \@ {/Symbol b} = 0.80'
plot 'data/magnetization_bin_1000_0.800000_MH.dat' i 0 @hist ls 2

set xrange[0:0.9]

binwidth = 0.03
binstart = -0.015
load 'hist.fct'

set output 'img/pdf_m_0.42_MH.eps'
set title 'MH \@ {/Symbol b} = 0.42'
plot 'data/magnetization_bin_1000_0.420000_MH.dat' i 0 @hist ls 2

binwidth = 0.03
binstart = -0.015
load 'hist.fct'

set output 'img/pdf_m_0.43_MH.eps'
set title 'MH \@ {/Symbol b} = 0.43'
plot 'data/magnetization_bin_1000_0.430000_MH.dat' i 0 @hist ls 2

binwidth = 0.03
binstart = -0.015
load 'hist.fct'

set output 'img/pdf_m_0.44_MH.eps'
set title 'MH \@ {/Symbol b} = 0.44'
plot 'data/magnetization_bin_1000_0.440000_MH.dat' i 0 @hist ls 2

binwidth = 0.03
binstart = -0.015
load 'hist.fct'

set output 'img/pdf_m_0.46_MH.eps'
set title 'MH \@ {/Symbol b} = 0.46'
plot 'data/magnetization_bin_1000_0.460000_MH.dat' i 0 @hist ls 2

