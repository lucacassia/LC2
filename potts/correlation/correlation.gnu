#!/usr/bin/gnuplot

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

load '../../modules/parula.pal'
set palette negative defined ( \
    0 '#D53E4F',\
    1 '#F46D43',\
    2 '#FDAE61',\
    3 '#FEE08B',\
    4 '#E6F598',\
    5 '#ABDDA4',\
    6 '#66C2A5',\
    7 '#3288BD' )

## green functions

set ylabel "G(r)"
set xlabel "r"

##32x32
set xrange[0:16]
set title '32x32 SW'
set output 'img/32_green_SW.eps'

!rm filetoload
! for ((i=0;i<20;i++)); do echo "f$i(x)=a$i*(exp(-x/b$i)+exp((x-32)/b$i)); fit f$i(x) sprintf('data/32_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:11 via a$i, b$i">> filetoload;done
!printf "plot " >> filetoload
! for ((i=0;i<20;i++)); do echo "f$i(x) pointtype 2 dashtype 2 pointsize default pointinterval 0 lc 0 notitle, sprintf('data/32_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:11:(0.8+$i*0.01) pt 7 lc palette t sprintf('{/Symbol b} = %.3f, {/Symbol x} = %.3f',0.8+$i*0.01,b$i),\\">> filetoload;done

load "filetoload"
!rm filetoload


##64x64
set xrange[0:32]
set title '64x64 SW'
set output 'img/64_green_SW.eps'

!rm filetoload
! for ((i=0;i<16;i++)); do echo "f$i(x)=a$i*(exp(-x/b$i)+exp((x-32)/b$i)); fit f$i(x) sprintf('data/64_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:11 via a$i, b$i">> filetoload;done
!printf "plot " >> filetoload
! for ((i=0;i<16;i++)); do echo "f$i(x) pointtype 2 dashtype 2 pointsize default pointinterval 0 lc 0 notitle, sprintf('data/64_%.6f_SW_9000.cor',0.8+$i*0.01) u 1:11:(0.8+$i*0.01) pt 7 lc palette t sprintf('{/Symbol b} = %.3f, {/Symbol x} = %.3f',0.8+$i*0.01,b$i),\\">> filetoload;done

load "filetoload"
!rm filetoload


## correlation length as a function of x

set xlabel "log(|x|)"
set ylabel "log({/Symbol x})"
unset xrange

f(x)=q-m*x
set fit errorvariables

#fit f(x) 'data/128_SW.fit' via m,q

#set output 'img/correlation_SW.eps'
#set title '128x128 SW'
#plot 'data/128_SW.fit' pt 2 ps 1.5 lc 7 title 'SW',\
#      f(x) ls 0 title sprintf("{/Symbol n} = %.6f +/- %.6f", m, m_err)

