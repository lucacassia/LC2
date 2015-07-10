## example
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set xlabel "Markov time"
set ylabel "E/V"
set xrange[500:1000]

set output 'img/MH_energy.eps'
plot 'data/32_0.440687_MH_1000.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.440687'

set output 'img/SW_energy.eps'
plot 'data/32_0.440687_SW_1000.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.440687'

## thermalization
set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## energy
set xlabel "Markov time"
set ylabel "E/V"
set yrange[-2:0]
set xrange[0:500]

# MH algorithm

set output 'img/MH_thermalization_e_0.300000.eps'
plot 'data/32_0.300000_MH_500.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.300000'

set output 'img/MH_thermalization_e_0.400000.eps'
plot 'data/32_0.400000_MH_500.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.400000'

set output 'img/MH_thermalization_e_0.440687.eps'
plot 'data/32_0.440687_MH_1000.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.440687'

# SW algorithm

set output 'img/SW_thermalization_e_0.300000.eps'
plot 'data/32_0.300000_SW_500.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.300000'

set output 'img/SW_thermalization_e_0.400000.eps'
plot 'data/32_0.400000_SW_500.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.400000'

set output 'img/SW_thermalization_e_0.440687.eps'
plot 'data/32_0.440687_SW_1000.dat' using 1  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.440687'


## magnetization
set ylabel "m"
set yrange[0:1]

# MH algorithm

set output 'img/MH_thermalization_m_0.300000.eps'
plot 'data/32_0.300000_MH_500.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.300000'

set output 'img/MH_thermalization_m_0.400000.eps'
plot 'data/32_0.400000_MH_500.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.400000'

set output 'img/MH_thermalization_m_0.440687.eps'
plot 'data/32_0.440687_MH_1000.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'MH : L = 32 \@ {/Symbol b} = 0.440687'

# SW algorithm

set output 'img/SW_thermalization_m_0.300000.eps'
plot 'data/32_0.300000_SW_500.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.300000'

set output 'img/SW_thermalization_m_0.400000.eps'
plot 'data/32_0.400000_SW_500.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.400000'

set output 'img/SW_thermalization_m_0.440687.eps'
plot 'data/32_0.440687_SW_1000.dat' using 2  pt 1 ps 0.5 lc rgb '#000000' title 'SW : L = 32 \@ {/Symbol b} = 0.440687'

