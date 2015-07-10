## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set samples 100000

## energy

set xlabel "{/Symbol b}"
set ylabel "e"
set yrange[-2:0]
set xrange[0:1]

set output 'img/energy_plot_MH.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) lc rgb '#000000' title 'exact',\
     'data/8_MH_99000.obs'   using 1:2 w l lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:2 w l lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:2 w l lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:2 w l lc 3 ps 0.5 title 'MH: L =  64',\
     'data/128_MH_99000.obs' using 1:2 w l lc 2 ps 0.5 title 'MH: L = 128'

set output 'img/energy_plot_SW.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) lc rgb '#000000' title 'exact',\
     'data/8_SW_9000.obs'  using 1:2 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs' using 1:2 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs' using 1:2 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs' using 1:2 pt 2 lc 3 ps 0.5 title 'SW: L =  64',\
     'data/128_SW_9000.obs' using 1:2 pt 2 lc 2 ps 0.5 title 'SW: L = 128'

## magnetization

set xlabel "{/Symbol b}"
set ylabel "m"
set yrange[0:1]

set output 'img/magnetization_plot_MH.eps'
plot (1-1/(sinh(2*x)**4))**0.125 lc rgb '#000000' title 'exact',\
     'data/8_MH_99000.obs'   using 1:4 w l lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:4 w l lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:4 w l lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:4 w l lc 3 ps 0.5 title 'MH: L =  64',\
     'data/128_MH_99000.obs' using 1:4 w l lc 2 ps 0.5 title 'MH: L = 128'

set output 'img/magnetization_plot_SW.eps'
plot (1-1/(sinh(2*x)**4))**0.125 lc rgb '#000000' title 'exact',\
     'data/8_SW_9000.obs'   using 1:4 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:4 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:4 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:4 pt 2 lc 3 ps 0.5 title 'SW: L =  64',\
     'data/128_SW_9000.obs' using 1:4 pt 2 lc 2 ps 0.5 title 'SW: L = 128'

unset yrange
unset xrange
set xrange[0.3:0.55]
set logscale y

## specific heat

set xlabel "{/Symbol b}"
set ylabel "C"

set output 'img/variance_e_plot_MH.eps'
plot 'data/8_MH_99000.obs'   using 1:3 w l lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:3 w l lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:3 w l lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:3 w l lc 3 ps 0.5 title 'MH: L =  64',\
     'data/128_MH_99000.obs' using 1:3 w l lc 2 ps 0.5 title 'MH: L = 128'

set output 'img/variance_e_plot_SW.eps'
plot 'data/8_SW_9000.obs'   using 1:3 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:3 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:3 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:3 pt 2 lc 3 ps 0.5 title 'SW: L =  64',\
     'data/128_SW_9000.obs' using 1:3 pt 2 lc 2 ps 0.5 title 'SW: L = 128'

## susceptibility

set xlabel "{/Symbol b}"
set ylabel "{/Symbol c}"

set output 'img/variance_m_plot_MH.eps'
plot 'data/8_MH_99000.obs'   using 1:5 w l lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:5 w l lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:5 w l lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:5 w l lc 3 ps 0.5 title 'MH: L =  64',\
     'data/128_MH_99000.obs' using 1:5 w l lc 2 ps 0.5 title 'MH: L = 128'

set output 'img/variance_m_plot_SW.eps'
plot 'data/8_SW_9000.obs'   using 1:5 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:5 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:5 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:5 pt 2 lc 3 ps 0.5 title 'SW: L =  64',\
     'data/128_SW_9000.obs' using 1:5 pt 2 lc 2 ps 0.5 title 'SW: L = 128'


