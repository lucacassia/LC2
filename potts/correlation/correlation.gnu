#!/usr/bin/gnuplot

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set palette negative defined ( \
    0 '#3288BD',\
    1 '#66C2A5',\
    2 '#ABDDA4',\
    3 '#E6F598',\
    4 '#FEE08B',\
    5 '#FDAE61',\
    6 '#F46D43',\
    7 '#D53E4F' )


## green functions

set ylabel "G(r)"
set xlabel "r"

##64x64
set xrange[0:31]
set yrange[0:1]
set title '64x64 SW'
set output 'img/64_green_SW.eps'

!rm filetoload
! for ((i=0;i<15;i++)); do echo "f$i(x)=a$i*(exp(-x/b$i)+exp((x-64)/b$i)); fit f$i(x) sprintf('data/64_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:182 via a$i, b$i">> filetoload;done
!printf "plot " >> filetoload
! for ((i=0;i<15;i++)); do echo "sprintf('data/64_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:182:183 w linespoints pt 7 ps 0.5 lc palette t sprintf('{/Symbol b} = %.3f, {/Symbol x} = %.3f',0.8+$i*0.01,b$i),\\">> filetoload;done

load "filetoload"
!rm filetoload


##64x64
load '../../modules/parula.pal'
unset xrange
unset yrange

set pm3d depthorder hidden3d 1
set hidden3d
set ticslevel 0

set xlabel "{/Symbol b}"
set ylabel "r"
set zlabel "G(r)"
set title '64x64 SW'
set output 'img/64_green_SW_3d.eps'

splot "data/64_SW.3d" u 183:1:182 ls 1 lw 0.5 w pm3d notitle


## correlation length as a function of x

set xlabel "log(|x|)"
set ylabel "log({/Symbol x})"
unset xrange

f(x)=q-m*x
set fit errorvariables

fit f(x) 'data/64_SW.fit' via m,q

set output 'img/correlation_SW.eps'
set title '64x64 SW'
plot 'data/64_SW.fit' pt 1 ps 1.5 lc 0 notitle,\
      f(x) ls 0 title sprintf("{/Symbol n} = %.6f +/- %.6f", m, m_err)

