## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## e

set xlabel "{/Symbol b}"
set ylabel "e"
set yrange[-2:0]

set output 'img/energy_plot_MH.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) ls 0 lc rgb '#000000' title 'exact',\
     'data/32_MH_99000.obs' using 1:2:3 pt 7 ps 0.5 lc rgb '#000000' title 'MH' w yerrorbars

set output 'img/energy_plot_SW.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) ls 0 lc rgb '#000000' title 'exact',\
     'data/32_SW_99000.obs' using 1:2:3 pt 7 ps 0.5 lc rgb '#000000' title 'SW' w yerrorbars

## m

set xlabel "{/Symbol b}"
set ylabel "m"
set yrange[0:1]

set output 'img/magnetization_plot_MH.eps'
plot (1-1/(sinh(2*x)**4))**0.125 ls 0 lc rgb '#000000' title 'exact',\
     'data/32_MH_99000.obs' using 1:4:5 pt 7 ps 0.5 lc rgb '#000000' title 'MH' w yerrorbars

set output 'img/magnetization_plot_SW.eps'
plot (1-1/(sinh(2*x)**4))**0.125 ls 0 lc rgb '#000000' title 'exact',\
     'data/32_SW_99000.obs' using 1:4:5 pt 7 ps 0.5 lc rgb '#000000' title 'SW' w yerrorbars

unset yrange

## variance e

set xlabel "{/Symbol b}"
set ylabel "C / V"

set output 'img/variance_e_plot_MH.eps'
plot 'data/32_MH_99000.obs' using 1:($3)**2 pt 7 ps 0.5 lc rgb '#000000' title 'MH'

set output 'img/variance_e_plot_SW.eps'
plot 'data/32_SW_99000.obs' using 1:($3)**2 pt 7 ps 0.5 lc rgb '#000000' title 'SW'

## variance m

set xlabel "{/Symbol b}"
set ylabel "{/Symbol c} / V"

set output 'img/variance_m_plot_MH.eps'
plot 'data/32_MH_99000.obs' using 1:($5)**2 pt 7 ps 0.5 lc rgb '#000000' title 'MH'

set output 'img/variance_m_plot_SW.eps'
plot 'data/32_SW_99000.obs' using 1:($5)**2 pt 7 ps 0.5 lc rgb '#000000' title 'SW'


