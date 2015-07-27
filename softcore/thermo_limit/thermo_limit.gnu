#!/usr/bin/gnuplot

reset

set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 20


f(x) = a+b/x

## potential

set xlabel '1/N'
set ylabel '<u>'
set title '{/Symbol r} = 0.7 - Potential Energy'

fit f(x) "data/U.dat" u 1:2:($3)/sqrt(1000) via a,b
set xrange[0:0.012]
set output 'img/limitU.eps'
plot f(1/x) t sprintf("u_{fit} = %.6f",a) lc 0,"data/U.dat" u (1/$1):2:($3)/sqrt(1000) lc 0 w e notitle

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 20

set output 'img/sigmaU.eps'
set ylabel '{/Symbol s}_u'
unset xrange
fit f(x) "data/U.dat" u 1:3 via a,b
set xrange[0:0.012]
plot f(1/x) t sprintf("{/Symbol s}_u = %.6f",b) lc 0, "data/U.dat" u (1/$1):3 lc 0 pt 7 notitle


## temperature
set terminal postscript eps size 6,4.5 enhanced color dashed lw 1 "DejaVuSans" 20
set xlabel '1/N'
set ylabel '<T>'
set title '{/Symbol r} = 0.7 - Temperature'

set output 'img/limitT.eps'
unset xrange
fit f(x) "data/T.dat" u 1:2:($3)/sqrt(1000) via a,b
set xrange[0:0.012]
plot f(1/x) t sprintf("{/Symbol s}_T = %.6f",a) lc 0 , "data/T.dat" u (1/$1):2:($3)/sqrt(1000) lc 0 w e notitle


set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 20
set output 'img/sigmaT.eps'
set ylabel '{/Symbol s}_T'
unset xrange
fit f(x) "data/T.dat" u 1:3 via a,b
set xrange[0:0.012]
plot f(1/x) t sprintf("T_{fit} = %.6f",b) lc 0, "data/T.dat" u (1/$1):3 lc 0 pt 7 notitle

