## autocorrelation

#set title "Autocorrelation"
set xlabel "k"
set ylabel "R(k)"
#set yrange[0:1]
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/autocorrelation_MH_0.30.eps'
plot 'data/autocorrelation_0_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.30'
set output 'img/autocorrelation_SW_0.30.eps'
plot 'data/autocorrelation_1_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.30'

set output 'img/autocorrelation_MH_0.35.eps'
plot 'data/autocorrelation_0_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.35'
set output 'img/autocorrelation_SW_0.35.eps'
plot 'data/autocorrelation_1_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.35'

set output 'img/autocorrelation_MH_0.40.eps'
plot 'data/autocorrelation_0_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.40'
set output 'img/autocorrelation_SW_0.40.eps'
plot 'data/autocorrelation_1_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.40'

set output 'img/autocorrelation_MH_0.45.eps'
plot 'data/autocorrelation_0_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.45'
set output 'img/autocorrelation_SW_0.45.eps'
plot 'data/autocorrelation_1_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.45'

set output 'img/autocorrelation_MH_0.50.eps'
plot 'data/autocorrelation_0_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.50'
set output 'img/autocorrelation_SW_0.50.eps'
plot 'data/autocorrelation_1_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.50'

set output 'img/autocorrelation_MH_0.55.eps'
plot 'data/autocorrelation_0_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.55'
set output 'img/autocorrelation_SW_0.55.eps'
plot 'data/autocorrelation_1_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.55'

set output 'img/autocorrelation_MH_0.60.eps'
plot 'data/autocorrelation_0_0.600000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.60'
set output 'img/autocorrelation_SW_0.60.eps'
plot 'data/autocorrelation_1_0.600000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.60'


## autocorrelation time

#set title "Autocorrelation Time"
set xlabel "k_{max}"
set ylabel "{/Symbol t}_{int}(\k_{max})"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/autocorrelation_time_MH_0.30.eps'
plot 'data/autocorrelation_time_0_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.30'
set output 'img/autocorrelation_time_SW_0.30.eps'
plot 'data/autocorrelation_time_1_0.300000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.30'

set output 'img/autocorrelation_time_MH_0.35.eps'
plot 'data/autocorrelation_time_0_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.35'
set output 'img/autocorrelation_time_SW_0.35.eps'
plot 'data/autocorrelation_time_1_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.35'

set output 'img/autocorrelation_time_MH_0.40.eps'
plot 'data/autocorrelation_time_0_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.40'
set output 'img/autocorrelation_time_SW_0.40.eps'
plot 'data/autocorrelation_time_1_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.40'

set output 'img/autocorrelation_time_MH_0.45.eps'
plot 'data/autocorrelation_time_0_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.45'
set output 'img/autocorrelation_time_SW_0.45.eps'
plot 'data/autocorrelation_time_1_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.45'

set output 'img/autocorrelation_time_MH_0.50.eps'
plot 'data/autocorrelation_time_0_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.50'
set output 'img/autocorrelation_time_SW_0.50.eps'
plot 'data/autocorrelation_time_1_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.50'

set output 'img/autocorrelation_time_MH_0.55.eps'
plot 'data/autocorrelation_time_0_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.55'
set output 'img/autocorrelation_time_SW_0.55.eps'
plot 'data/autocorrelation_time_1_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.55'

set output 'img/autocorrelation_time_MH_0.60.eps'
plot 'data/autocorrelation_time_0_0.600000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.60'
set output 'img/autocorrelation_time_SW_0.60.eps'
plot 'data/autocorrelation_time_1_0.600000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.60'


