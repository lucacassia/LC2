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

set output 'img/autocorrelation_time_MH_0.35.eps'
fit f(x) 'data/autocorrelation_time_0_0.350000.dat' via t,a
plot 'data/autocorrelation_time_0_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.35',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/autocorrelation_time_MH_0.36.eps'
plot 'data/autocorrelation_time_0_0.360000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.36'
set output 'img/autocorrelation_time_MH_0.37.eps'
plot 'data/autocorrelation_time_0_0.370000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.37'
set output 'img/autocorrelation_time_MH_0.38.eps'
plot 'data/autocorrelation_time_0_0.380000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.38'
set output 'img/autocorrelation_time_MH_0.39.eps'
plot 'data/autocorrelation_time_0_0.390000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.39'
set output 'img/autocorrelation_time_MH_0.40.eps'
plot 'data/autocorrelation_time_0_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.40'
set output 'img/autocorrelation_time_MH_0.41.eps'
plot 'data/autocorrelation_time_0_0.410000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.41'
set output 'img/autocorrelation_time_MH_0.42.eps'
plot 'data/autocorrelation_time_0_0.420000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.42'
set output 'img/autocorrelation_time_MH_0.43.eps' 
plot 'data/autocorrelation_time_0_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.43'
set output 'img/autocorrelation_time_MH_0.44.eps' 
plot 'data/autocorrelation_time_0_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.44'
set output 'img/autocorrelation_time_MH_0.45.eps' 
plot 'data/autocorrelation_time_0_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.45'
set output 'img/autocorrelation_time_MH_0.46.eps' 
plot 'data/autocorrelation_time_0_0.460000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.46'
set output 'img/autocorrelation_time_MH_0.47.eps' 
plot 'data/autocorrelation_time_0_0.470000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.47'
set output 'img/autocorrelation_time_MH_0.48.eps' 
plot 'data/autocorrelation_time_0_0.480000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.48'
set output 'img/autocorrelation_time_MH_0.49.eps' 
plot 'data/autocorrelation_time_0_0.490000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.49'
set output 'img/autocorrelation_time_MH_0.50.eps' 
plot 'data/autocorrelation_time_0_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.50'
set output 'img/autocorrelation_time_MH_0.51.eps'
plot 'data/autocorrelation_time_0_0.510000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.51'
set output 'img/autocorrelation_time_MH_0.52.eps'
plot 'data/autocorrelation_time_0_0.520000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.52'
set output 'img/autocorrelation_time_MH_0.53.eps'
plot 'data/autocorrelation_time_0_0.530000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.53'
set output 'img/autocorrelation_time_MH_0.54.eps'
plot 'data/autocorrelation_time_0_0.540000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.54'
set output 'img/autocorrelation_time_MH_0.55.eps'
plot 'data/autocorrelation_time_0_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.55'

set output 'img/autocorrelation_time_SW_0.35.eps'
plot 'data/autocorrelation_time_1_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.35'
set output 'img/autocorrelation_time_SW_0.36.eps'
plot 'data/autocorrelation_time_1_0.360000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.36'
set output 'img/autocorrelation_time_SW_0.37.eps'
plot 'data/autocorrelation_time_1_0.370000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.37'
set output 'img/autocorrelation_time_SW_0.38.eps'
plot 'data/autocorrelation_time_1_0.380000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.38'
set output 'img/autocorrelation_time_SW_0.39.eps'
plot 'data/autocorrelation_time_1_0.390000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.39'
set output 'img/autocorrelation_time_SW_0.40.eps'
plot 'data/autocorrelation_time_1_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.40'
set output 'img/autocorrelation_time_SW_0.41.eps'
plot 'data/autocorrelation_time_1_0.410000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.41'
set output 'img/autocorrelation_time_SW_0.42.eps'
plot 'data/autocorrelation_time_1_0.420000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.42'
set output 'img/autocorrelation_time_SW_0.43.eps'
plot 'data/autocorrelation_time_1_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.43'
set output 'img/autocorrelation_time_SW_0.44.eps'
plot 'data/autocorrelation_time_1_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.44'
set output 'img/autocorrelation_time_SW_0.45.eps'
plot 'data/autocorrelation_time_1_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.45'
set output 'img/autocorrelation_time_SW_0.46.eps'
plot 'data/autocorrelation_time_1_0.460000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.46'
set output 'img/autocorrelation_time_SW_0.47.eps'
plot 'data/autocorrelation_time_1_0.470000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.47'
set output 'img/autocorrelation_time_SW_0.48.eps'
plot 'data/autocorrelation_time_1_0.480000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.48'
set output 'img/autocorrelation_time_SW_0.49.eps'
plot 'data/autocorrelation_time_1_0.490000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.49'
set output 'img/autocorrelation_time_SW_0.50.eps'
plot 'data/autocorrelation_time_1_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.50'
set output 'img/autocorrelation_time_SW_0.51.eps'
plot 'data/autocorrelation_time_1_0.510000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.51'
set output 'img/autocorrelation_time_SW_0.52.eps'
plot 'data/autocorrelation_time_1_0.520000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.52'
set output 'img/autocorrelation_time_SW_0.53.eps'
plot 'data/autocorrelation_time_1_0.530000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.53'
set output 'img/autocorrelation_time_SW_0.54.eps'
plot 'data/autocorrelation_time_1_0.540000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.54'
set output 'img/autocorrelation_time_SW_0.55.eps'
plot 'data/autocorrelation_time_1_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.55'

