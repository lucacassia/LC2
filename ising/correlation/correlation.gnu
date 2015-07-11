#!/usr/bin/gnuplot

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## green functions

set ylabel "G(r)"
set xlabel "r"
set xrange[0:64]

#MH
f1(x) = a1*(exp(-x/b1)+exp((x-128)/b1))
f2(x) = a2*(exp(-x/b2)+exp((x-128)/b2))
f3(x) = a3*(exp(-x/b3)+exp((x-128)/b3))
f4(x) = a4*(exp(-x/b4)+exp((x-128)/b4))
f5(x) = a5*(exp(-x/b5)+exp((x-128)/b5))
fit f1(x) 'data/128_0.270255_MH_99000.cor' using 1:11 via a1,b1
fit f2(x) 'data/128_0.356053_MH_99000.cor' using 1:11 via a2,b2
fit f3(x) 'data/128_0.398659_MH_99000.cor' using 1:11 via a3,b3
fit f4(x) 'data/128_0.419816_MH_99000.cor' using 1:11 via a4,b4
fit f5(x) 'data/128_0.430323_MH_99000.cor' using 1:11 via a5,b5

set output 'img/green_MH.eps'
set title '128x128 MH'
plot  f1(x) ls 0 notitle, f2(x) ls 0 notitle, f3(x) ls 0 notitle, f4(x) ls 0 notitle, f5(x) ls 0 notitle,\
      'data/128_0.270255_MH_99000.cor' using 1:11 pt 1 ps 0.8 lc 1 title sprintf('{/Symbol b} = 0.270255 {/Symbol x} = %.6f',b1),\
      'data/128_0.356053_MH_99000.cor' using 1:11 pt 1 ps 0.8 lc 2 title sprintf('{/Symbol b} = 0.356053 {/Symbol x} = %.6f',b2),\
      'data/128_0.398659_MH_99000.cor' using 1:11 pt 1 ps 0.8 lc 3 title sprintf('{/Symbol b} = 0.398659 {/Symbol x} = %.6f',b3),\
      'data/128_0.419816_MH_99000.cor' using 1:11 pt 1 ps 0.8 lc 4 title sprintf('{/Symbol b} = 0.419816 {/Symbol x} = %.6f',b4),\
      'data/128_0.430323_MH_99000.cor' using 1:11 pt 1 ps 0.8 lc 7 title sprintf('{/Symbol b} = 0.430323 {/Symbol x} = %.6f',b5),


#SW
fit f1(x) 'data/128_0.270255_SW_9000.cor' using 1:11 via a1,b1
fit f2(x) 'data/128_0.356053_SW_9000.cor' using 1:11 via a2,b2
fit f3(x) 'data/128_0.398659_SW_9000.cor' using 1:11 via a3,b3
fit f4(x) 'data/128_0.419816_SW_9000.cor' using 1:11 via a4,b4
fit f5(x) 'data/128_0.430323_SW_9000.cor' using 1:11 via a5,b5

set output 'img/green_SW.eps'
set title '128x128 SW'
plot  f1(x) ls 0 notitle, f2(x) ls 0 notitle, f3(x) ls 0 notitle, f4(x) ls 0 notitle, f5(x) ls 0 notitle,\
      'data/128_0.270255_SW_9000.cor' using 1:11 pt 2 ps 0.8 lc 1 title sprintf('{/Symbol b} = 0.270255 {/Symbol x} = %.6f',b1),\
      'data/128_0.356053_SW_9000.cor' using 1:11 pt 2 ps 0.8 lc 2 title sprintf('{/Symbol b} = 0.356053 {/Symbol x} = %.6f',b2),\
      'data/128_0.398659_SW_9000.cor' using 1:11 pt 2 ps 0.8 lc 3 title sprintf('{/Symbol b} = 0.398659 {/Symbol x} = %.6f',b3),\
      'data/128_0.419816_SW_9000.cor' using 1:11 pt 2 ps 0.8 lc 4 title sprintf('{/Symbol b} = 0.419816 {/Symbol x} = %.6f',b4),\
      'data/128_0.430323_SW_9000.cor' using 1:11 pt 2 ps 0.8 lc 7 title sprintf('{/Symbol b} = 0.430323 {/Symbol x} = %.6f',b5)


## correlation length as a function of x

set xlabel "log(|x|)"
set ylabel "log({/Symbol x})"
unset xrange

f(x)=q-m*x
set fit errorvariables

fit f(x) 'data/128_MH.fit' via m,q

set output 'img/correlation_MH.eps'
set title '128x128 MH'
plot 'data/128_MH.fit' pt 1 lc 6 title 'MH',\
      f(x) ls 0 title sprintf("{/Symbol n} = %.6f +/- %.6f", m, m_err)

fit f(x) 'data/128_SW.fit' via m,q

set output 'img/correlation_SW.eps'
set title '128x128 SW'
plot 'data/128_SW.fit' pt 2 lc 7 title 'SW',\
      f(x) ls 0 title sprintf("{/Symbol n} = %.6f +/- %.6f", m, m_err)

