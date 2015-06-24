## autocorrelation

#set title "Autocorrelation"
#set xlabel "k"
#set ylabel "R(k)"
#set yrange[0:1]
#set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## autocorrelation time

#set title "Autocorrelation Time"
set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

f(x)=a*(1-(2*t/(2*t+1))*exp(-x/t))

## MH

set output 'img/MH_autocorrelation_time_0.43.eps'
fit f(x) 'data/MH_autocorrelation_time_0.430110.dat' using 2:3 via t,a
plot 'data/MH_autocorrelation_time_0.430110.dat' using 2:3   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)

## SW

set output 'img/SW_autocorrelation_time_0.43.eps'
fit f(x) 'data/SW_autocorrelation_time_0.430110.dat' using 2:3 via t,a
plot 'data/SW_autocorrelation_time_0.430110.dat' using 2:3   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)

