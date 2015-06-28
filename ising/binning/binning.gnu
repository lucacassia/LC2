#set title "Binning"
set xlabel "block size k"
set ylabel "k{/Symbol s}_{B}^{2}/{/Symbol s}_{0}^{2}"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

f(x) = 2*t*(1-t*(1-exp(-x/t))/x)

##MH

set output 'img/binning_MH_0.35.eps'
fit f(x) 'data/32_0.350000_MH_999000.var' via t
plot 'data/32_0.350000_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.35',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.40.eps'
fit f(x) 'data/32_0.400000_MH_999000.var' via t
plot 'data/32_0.400000_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.40',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.43.eps'
fit f(x) 'data/32_0.430000_MH_999000.var' via t
plot 'data/32_0.430000_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.44.eps'
fit f(x) 'data/32_0.440687_MH_999000.var' via t
plot 'data/32_0.440687_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.44',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.45.eps'
fit f(x) 'data/32_0.450000_MH_999000.var' via t
plot 'data/32_0.450000_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.45',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_MH_0.50.eps'
fit f(x) 'data/32_0.500000_MH_999000.var' via t
plot 'data/32_0.500000_MH_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'MH: L = 32 \@ beta = 0.50',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)


##SW

set yrange[0:8]

set output 'img/binning_SW_0.35.eps'
fit f(x) 'data/32_0.350000_SW_999000.var' via t
plot 'data/32_0.350000_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.35',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.40.eps'
fit f(x) 'data/32_0.400000_SW_999000.var' via t
plot 'data/32_0.400000_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.40',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.43.eps'
fit f(x) 'data/32_0.430000_SW_999000.var' via t
plot 'data/32_0.430000_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.43',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.44.eps'
fit f(x) 'data/32_0.440687_SW_999000.var' via t
plot 'data/32_0.440687_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.44',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.45.eps'
fit f(x) 'data/32_0.450000_SW_999000.var' via t
plot 'data/32_0.450000_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.45',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)

set output 'img/binning_SW_0.50.eps'
fit f(x) 'data/32_0.500000_SW_999000.var' via t
plot 'data/32_0.500000_SW_999000.var'   pt 1 ps 0.8 lc rgb '#000000' title 'SW: L = 32 \@ beta = 0.50',\
     f(x) lc rgb '#000000' title sprintf("{/Symbol t}_{exp} = %.2f",t)




## magnetization binning

#set xlabel "Markov time"
#set ylabel "m"
#unset yrange
#set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

#set output 'img/magnetization_bin_1000_MH.eps'
#plot 'data/MH_magnetization_bin_1000_0.430000.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH  N_B = 1000 \@ {/Symbol b} = 0.43'

#set output 'img/magnetization_bin_1000_SW.eps'
#plot 'data/SW_magnetization_bin_1000_0.430000.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW  N_B = 1000 \@ {/Symbol b} = 0.43'

