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
plot 'data/energy_bin_1000_MH.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'MH  N_B = 1000 \@ {/Symbol b} = 0.3'

set output 'img/energy_bin_1000_SW.eps'
plot 'data/energy_bin_1000_SW.dat'   pt 1 ps 0.5 lc rgb '#000000' title 'SW  N_B = 1000 \@ {/Symbol b} = 0.3'


set xlabel "{/Symbol b}"
set ylabel "energy density"
set yrange[-2:0]
set xrange[0:1]

set output 'img/energy_plot_MH.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) ls 0 lc rgb '#000000' title 'exact',\
     'data/energy_plot_50_MH.dat' pt 7 ps 0.5 lc rgb '#000000' title 'MH' w yerrorbars

set xlabel "{/Symbol b}"
set ylabel "magnetization"
set yrange[0:1]

set output 'img/magnetization_plot_MH.eps'
plot (1-1/(sinh(2*x)**4))**0.125 ls 0 lc rgb '#000000' title 'exact',\
     'data/magnetization_plot_50_MH.dat' pt 7 ps 0.5 lc rgb '#000000' title 'MH' w yerrorbars
