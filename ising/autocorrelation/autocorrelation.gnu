## autocorrelation time

#set title "Autocorrelation Time"
set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

f(x)=a*(1-(2*t/(2*t+1))*exp(-x/t))

## MH

set output 'img/MH_autocorrelation.eps'
#fit f(x) 'data/MH_autocorrelation_time_0.430000.dat' via t,a
#plot 'data/MH_autocorrelation_time_0.430000.dat' pt 1 ps 0.8 lc 0 title 'MH \@ beta = 0.43',\
#     f(x) lc 0 title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)

## SW

set output 'img/SW_autocorrelation.eps'
fit f(x) 'data/32_0.430000_SW_99000.acr' via t,a
plot 'data/32_0.430000_SW_99000.acr' pt 1 ps 0.8 lc 0 title 'SW \@ beta = 0.43',\
     f(x) lc 0 title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)

## fit

set xlabel "x"
set ylabel "{/Symbol t}_{int}"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set xrange[-0.1:0.1]

set output 'img/autocorrelation_time.eps'
plot 'data/32_MH.fit' pt 1 ps 0.5 lc 0 title 'MH : L = 32',\
     'data/32_SW.fit' pt 2 ps 0.5 lc 0 title 'SW : L = 32'
