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

set output 'img/MH_autocorrelation_time_0.35.eps'
fit f(x) 'data/MH_autocorrelation_time_0.350000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.35',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.36.eps'
fit f(x) 'data/MH_autocorrelation_time_0.360000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.360000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.36',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.37.eps'
fit f(x) 'data/MH_autocorrelation_time_0.370000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.370000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.37',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.38.eps'
fit f(x) 'data/MH_autocorrelation_time_0.380000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.380000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.38',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.39.eps'
fit f(x) 'data/MH_autocorrelation_time_0.390000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.390000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.39',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.40.eps'
fit f(x) 'data/MH_autocorrelation_time_0.400000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.40',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.41.eps'
fit f(x) 'data/MH_autocorrelation_time_0.410000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.410000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.41',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.42.eps'
fit f(x) 'data/MH_autocorrelation_time_0.420000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.420000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.42',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.43.eps'
fit f(x) 'data/MH_autocorrelation_time_0.430000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.44.eps'
fit f(x) 'data/MH_autocorrelation_time_0.440000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.44',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.45.eps'
fit f(x) 'data/MH_autocorrelation_time_0.450000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.45',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.46.eps'
fit f(x) 'data/MH_autocorrelation_time_0.460000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.460000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.46',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.47.eps'
fit f(x) 'data/MH_autocorrelation_time_0.470000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.470000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.47',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.48.eps'
fit f(x) 'data/MH_autocorrelation_time_0.480000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.480000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.48',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.49.eps'
fit f(x) 'data/MH_autocorrelation_time_0.490000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.490000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.49',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.50.eps'
fit f(x) 'data/MH_autocorrelation_time_0.500000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.50',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.51.eps'
fit f(x) 'data/MH_autocorrelation_time_0.510000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.510000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.51',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.52.eps'
fit f(x) 'data/MH_autocorrelation_time_0.520000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.520000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.52',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.53.eps'
fit f(x) 'data/MH_autocorrelation_time_0.530000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.530000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.53',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.54.eps'
fit f(x) 'data/MH_autocorrelation_time_0.540000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.540000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.54',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/MH_autocorrelation_time_0.55.eps'
fit f(x) 'data/MH_autocorrelation_time_0.550000.dat' via t,a
plot 'data/MH_autocorrelation_time_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.55',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)


## SW

set output 'img/SW_autocorrelation_time_0.35.eps'
fit f(x) 'data/SW_autocorrelation_time_0.350000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.35',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.36.eps'
fit f(x) 'data/SW_autocorrelation_time_0.360000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.360000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.36',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.37.eps'
fit f(x) 'data/SW_autocorrelation_time_0.370000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.370000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.37',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.38.eps'
fit f(x) 'data/SW_autocorrelation_time_0.380000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.380000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.38',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.39.eps'
fit f(x) 'data/SW_autocorrelation_time_0.390000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.390000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.39',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.40.eps'
fit f(x) 'data/SW_autocorrelation_time_0.400000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.40',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.41.eps'
fit f(x) 'data/SW_autocorrelation_time_0.410000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.410000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.41',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.42.eps'
fit f(x) 'data/SW_autocorrelation_time_0.420000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.420000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.42',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.43.eps'
fit f(x) 'data/SW_autocorrelation_time_0.430000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.44.eps'
fit f(x) 'data/SW_autocorrelation_time_0.440000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.44',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.45.eps'
fit f(x) 'data/SW_autocorrelation_time_0.450000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.45',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.46.eps'
fit f(x) 'data/SW_autocorrelation_time_0.460000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.460000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.46',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.47.eps'
fit f(x) 'data/SW_autocorrelation_time_0.470000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.470000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.47',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.48.eps'
fit f(x) 'data/SW_autocorrelation_time_0.480000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.480000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.48',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.49.eps'
fit f(x) 'data/SW_autocorrelation_time_0.490000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.490000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.49',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.50.eps'
fit f(x) 'data/SW_autocorrelation_time_0.500000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.50',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.51.eps'
fit f(x) 'data/SW_autocorrelation_time_0.510000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.510000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.51',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.52.eps'
fit f(x) 'data/SW_autocorrelation_time_0.520000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.520000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.52',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.53.eps'
fit f(x) 'data/SW_autocorrelation_time_0.530000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.530000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.53',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.54.eps'
fit f(x) 'data/SW_autocorrelation_time_0.540000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.540000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.54',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)
set output 'img/SW_autocorrelation_time_0.55.eps'
fit f(x) 'data/SW_autocorrelation_time_0.550000.dat' via t,a
plot 'data/SW_autocorrelation_time_0.550000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.55',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f  {/Symbol t}_{int} = %.2f",t,a)

