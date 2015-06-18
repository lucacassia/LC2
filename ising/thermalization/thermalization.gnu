## magnetization

#set title "Magnetization"
set xlabel "Markov time"
set ylabel "average magnetization"
set yrange[-0.3:0.3]
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/magnetization_MH_0.3.eps'
plot 'data/magnetization_MH_0.3.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/magnetization_MH2_0.3.eps'
plot 'data/magnetization_MH2_0.3.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/magnetization_SW_0.3.eps'
plot 'data/magnetization_SW_0.3.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.3'

## energy

set title "Thermalization"
set xlabel "Markov time"
set ylabel "energy density"
set yrange[-2:0]
set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

# MH algorithm

set output 'img/thermalization_MH_0.2.eps'
plot 'data/thermalization_MH_0.2.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.2'

set output 'img/thermalization_MH_0.3.eps'
plot 'data/thermalization_MH_0.3.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.3'

set output 'img/thermalization_MH_0.4.eps'
plot 'data/thermalization_MH_0.4.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.4'

set output 'img/thermalization_MH_0.45.eps'
plot 'data/thermalization_MH_0.45.dat'  pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.45'

set output 'img/thermalization_MH_0.5.eps'
plot 'data/thermalization_MH_0.5.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.5'

set output 'img/thermalization_MH_0.6.eps'
plot 'data/thermalization_MH_0.6.dat'   pt 7 ps 0.5 lc rgb '#000000' title 'MH \@ {/Symbol b} = 0.6'

# SW algorithm

set output 'img/thermalization_SW_0.2.eps'
plot 'data/thermalization_SW_0.2.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.2'

set output 'img/thermalization_SW_0.3.eps'
plot 'data/thermalization_SW_0.3.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.3'

set output 'img/thermalization_SW_0.4.eps'
plot 'data/thermalization_SW_0.4.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.4'

set output 'img/thermalization_SW_0.45.eps'
plot 'data/thermalization_SW_0.45.dat'  pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.45'

set output 'img/thermalization_SW_0.5.eps'
plot 'data/thermalization_SW_0.5.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.5'

set output 'img/thermalization_SW_0.6.eps'
plot 'data/thermalization_SW_0.6.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW \@ {/Symbol b} = 0.6'
