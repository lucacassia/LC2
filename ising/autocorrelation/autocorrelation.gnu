#!/usr/bin/gnuplot

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## integrated autocorrelation time as a function of k_max

set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"


f(x)=a*(1-(2*t/(2*t+1))*exp(-x/t))

do for [i=0:9] {
    beta_value = 0.39+i*0.01
    ## MH
    unset yrange
    set output sprintf('img/32_%.6f_MH.eps', beta_value )
    inputfile = sprintf('data/32_%.6f_MH_999000.acr', beta_value )
    fit f(x) inputfile via t,a
    plot inputfile pt 1 ps 0.8 lc 0 title sprintf('MH : L = 32 \@ {/Symbol b} = %.2f', beta_value ),\
         f(x) lc 0 title sprintf('{/Symbol t}_{exp} = %.3f  {/Symbol t}_{int} = %.3f', t, a )
    ## SW
    set yrange[0:6]
    set output sprintf('img/32_%.6f_SW.eps', beta_value )
    inputfile = sprintf('data/32_%.6f_SW_99000.acr', beta_value )
    fit f(x) inputfile via t,a
    plot inputfile pt 1 ps 0.8 lc 0 title sprintf('SW : L = 32 \@ {/Symbol b} = %.2f', beta_value ),\
         f(x) lc 0 title sprintf('{/Symbol t}_{exp} = %.3f  {/Symbol t}_{int} = %.3f', t, a )
}


## autocorrelation time as a function of x

set xlabel "x"
set ylabel "{/Symbol t}_{int}"
set xrange[-0.1:0.1]
unset yrange

set output 'img/autocorrelation_time.eps'
plot 'data/32_MH.fit'  pt 1 ps 1 lc 0 title 'MH : L = 32',\
     'data/32_SW.fit'  pt 2 ps 1 lc 0 title 'SW : L = 32'

