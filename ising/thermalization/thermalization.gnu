## magnetization

set xlabel "Markov time"
set ylabel "E/V"

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/MH_energy_0.43.eps'
plot 'data/MH_energy_0.430000.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/SW_energy_0.43.eps'
plot 'data/SW_energy_0.430000.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.3'

set xlabel "Markov time"
set ylabel "E/V"

set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set yrange[-2:0]

# MH algorithm

set output 'img/MH_thermalization_0.500000.eps'
plot 'data/MH_thermalization_0.500000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.50'

set output 'img/MH_thermalization_0.300000.eps'
plot 'data/MH_thermalization_0.300000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.30'

set output 'img/MH_thermalization_0.400000.eps'
plot 'data/MH_thermalization_0.400000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.40'

set output 'img/MH_thermalization_0.430000.eps'
plot 'data/MH_thermalization_0.430000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.43'

set output 'img/MH_thermalization_0.600000.eps'
plot 'data/MH_thermalization_0.600000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.60'

set output 'img/MH_thermalization_0.800000.eps'
plot 'data/MH_thermalization_0.800000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.80'


# SW algorithm

set output 'img/SW_thermalization_0.500000.eps'
plot 'data/SW_thermalization_0.500000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.50'

set output 'img/SW_thermalization_0.300000.eps'
plot 'data/SW_thermalization_0.300000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.30'

set output 'img/SW_thermalization_0.400000.eps'
plot 'data/SW_thermalization_0.400000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.40'

set output 'img/SW_thermalization_0.430000.eps'
plot 'data/SW_thermalization_0.430000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.43'

set output 'img/SW_thermalization_0.600000.eps'
plot 'data/SW_thermalization_0.600000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.60'

set output 'img/SW_thermalization_0.800000.eps'
plot 'data/SW_thermalization_0.800000.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.80'

