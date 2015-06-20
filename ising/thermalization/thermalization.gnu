## magnetization

#set title "Magnetization"
set xlabel "Markov time"
set ylabel "magnetization"
set yrange[-0.3:0.3]
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/magnetization_0.300000_MH.eps'
plot 'data/magnetization_0.300000_MH.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/magnetization_0.300000_MH2.eps'
plot 'data/magnetization_0.300000_MH2.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/magnetization_0.300000_SW.eps'
plot 'data/magnetization_0.300000_SW.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.3'

## energy

set title "Thermalization"
set xlabel "Markov time"
set ylabel "energy density"
set yrange[-2:0]
set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

# MH algorithm

set output 'img/thermalization_0.200000_MH.eps'
plot 'data/thermalization_0.200000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.20'

set output 'img/thermalization_0.300000_MH.eps'
plot 'data/thermalization_0.300000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.30'

set output 'img/thermalization_0.400000_MH.eps'
plot 'data/thermalization_0.400000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.40'

set output 'img/thermalization_0.450000_MH.eps'
plot 'data/thermalization_0.450000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.45'

set output 'img/thermalization_0.500000_MH.eps'
plot 'data/thermalization_0.500000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.50'

set output 'img/thermalization_0.600000_MH.eps'
plot 'data/thermalization_0.600000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.60'

set output 'img/thermalization_0.800000_MH.eps'
plot 'data/thermalization_0.800000_MH.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.80'


# SW algorithm

set output 'img/thermalization_0.200000_SW.eps'
plot 'data/thermalization_0.200000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.20'

set output 'img/thermalization_0.300000_SW.eps'
plot 'data/thermalization_0.300000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.30'

set output 'img/thermalization_0.400000_SW.eps'
plot 'data/thermalization_0.400000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.40'

set output 'img/thermalization_0.450000_SW.eps'
plot 'data/thermalization_0.450000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.45'

set output 'img/thermalization_0.500000_SW.eps'
plot 'data/thermalization_0.500000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.50'

set output 'img/thermalization_0.600000_SW.eps'
plot 'data/thermalization_0.600000_SW.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.60'

