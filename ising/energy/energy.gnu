## energy binning

#set title "Binning"
set xlabel "Markov time"
set ylabel "energy density"
set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set output 'img/energy_bin_100_MH.eps'
plot 'data/energy_bin_100_MH.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH  N_B = 100 \@ {/Symbol b} = 0.3'

set output 'img/energy_bin_100_SW.eps'
plot 'data/energy_bin_100_SW.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW  N_B = 100 \@ {/Symbol b} = 0.3'

set output 'img/energy_bin_1000_MH.eps'
plot 'data/energy_bin_100_MH.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH  N_B = 1000 \@ {/Symbol b} = 0.3'

set output 'img/energy_bin_1000_SW.eps'
plot 'data/energy_bin_100_SW.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW  N_B = 1000 \@ {/Symbol b} = 0.3'
