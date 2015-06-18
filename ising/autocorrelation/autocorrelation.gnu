## autocorrelation

#set title "Autocorrelation"
set xlabel "k"
set ylabel "R(k)"
#set yrange[0:1]
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/autocorrelation_MH.eps'
plot 'data/autocorrelation_0_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.3'

set output 'img/autocorrelation_SW.eps'
plot 'data/autocorrelation_1_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.3'

## autocorrelation time

#set title "Autocorrelation Time"
set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/autocorrelation_time_MH.eps'
plot 'data/autocorrelation_time_0_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.3'

set output 'img/autocorrelation_time_SW.eps'
plot 'data/autocorrelation_time_1_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.3'

