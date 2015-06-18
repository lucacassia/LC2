set title "Binning"
set xlabel "block size k"
set ylabel "k{/Symbol s}_{B}^{2}/{/Symbol s}_{0}^{2}"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

f(x) = 2*t*(1-t*(1-exp(-x/t))/x)

##MH

set output 'img/binning_MH_0.35.eps'
fit f(x) 'data/variance_0_0.350000.dat' via t
plot 'data/variance_0_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.35', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.40.eps'
fit f(x) 'data/variance_0_0.400000.dat' via t
plot 'data/variance_0_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.40', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.43.eps'
fit f(x) 'data/variance_0_0.430000.dat' via t
plot 'data/variance_0_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.43', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.44.eps'
fit f(x) 'data/variance_0_0.440000.dat' via t
plot 'data/variance_0_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.44', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

t=2683.65

set output 'img/binning_MH_0.45.eps'
fit f(x) 'data/variance_0_0.450000.dat' via t
plot 'data/variance_0_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.45', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.50.eps'
fit f(x) 'data/variance_0_0.500000.dat' via t
plot 'data/variance_0_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'MH \@ beta = 0.50', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

##SW

set output 'img/binning_SW_0.35.eps'
fit f(x) 'data/variance_1_0.350000.dat' via t
plot 'data/variance_1_0.350000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.35', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.40.eps'
fit f(x) 'data/variance_1_0.400000.dat' via t
plot 'data/variance_1_0.400000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.40', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.43.eps'
fit f(x) 'data/variance_1_0.430000.dat' via t
plot 'data/variance_1_0.430000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.43', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.44.eps'
fit f(x) 'data/variance_1_0.440000.dat' via t
plot 'data/variance_1_0.440000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.44', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.45.eps'
fit f(x) 'data/variance_1_0.450000.dat' via t
plot 'data/variance_1_0.450000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.45', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.50.eps'
fit f(x) 'data/variance_1_0.500000.dat' via t
plot 'data/variance_1_0.500000.dat'   pt 1 ps 0.8 lc rgb '#000000' title 'SW \@ beta = 0.50', f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

