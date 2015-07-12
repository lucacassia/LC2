## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set samples 100000

## energy

set xlabel "{/Symbol b}"
set ylabel "e"
set yrange[-2:0]
set xrange[0:1]

set output 'img/energy_MH.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) lc 0 title 'exact',\
     'data/8_MH_99000.obs'   using 1:2 pt 1 lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:2 pt 1 lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:2 pt 1 lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:2 pt 1 lc 3 ps 0.5 title 'MH: L =  64'

set output 'img/energy_SW.eps'
plot -(1+(2/3.14159265359)*(2*tanh(2*x)**2-1)*EllipticK(2*sinh(2*x)/cosh(2*x)**2))/tanh(2*x) lc 0 title 'exact',\
     'data/8_SW_9000.obs'   using 1:2 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:2 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:2 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:2 pt 2 lc 3 ps 0.5 title 'SW: L =  64'

## magnetization

set xlabel "{/Symbol b}"
set ylabel "m"
set yrange[0:1]

set output 'img/magnetization_MH.eps'
plot (1-1/(sinh(2*x)**4))**0.125 lc 0 title 'exact',\
     'data/8_MH_99000.obs'   using 1:4 pt 1 lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:4 pt 1 lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:4 pt 1 lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:4 pt 1 lc 3 ps 0.5 title 'MH: L =  64'

set output 'img/magnetization_SW.eps'
plot (1-1/(sinh(2*x)**4))**0.125 lc 0 title 'exact',\
     'data/8_SW_9000.obs'   using 1:4 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:4 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:4 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:4 pt 2 lc 3 ps 0.5 title 'SW: L =  64'

unset yrange
unset xrange
set logscale y

## specific heat
set xrange[0.36:0.5]

set xlabel "{/Symbol b}"
set ylabel "C"

set output 'img/specific_heat_MH.eps'
plot 'data/8_MH_99000.obs'   using 1:3 pt 1 lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:3 pt 1 lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:3 pt 1 lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:3 pt 1 lc 3 ps 0.5 title 'MH: L =  64'

set output 'img/specific_heat_SW.eps'
plot 'data/8_SW_9000.obs'   using 1:3 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:3 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:3 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:3 pt 2 lc 3 ps 0.5 title 'SW: L =  64'

## susceptibility
set xrange[0.3:0.55]

set xlabel "{/Symbol b}"
set ylabel "{/Symbol c}"

set output 'img/susceptibility_MH.eps'
plot 'data/8_MH_99000.obs'   using 1:5 pt 1 lc 7 ps 0.5 title 'MH: L =   8',\
     'data/16_MH_99000.obs'  using 1:5 pt 1 lc 1 ps 0.5 title 'MH: L =  16',\
     'data/32_MH_99000.obs'  using 1:5 pt 1 lc 6 ps 0.5 title 'MH: L =  32',\
     'data/64_MH_99000.obs'  using 1:5 pt 1 lc 3 ps 0.5 title 'MH: L =  64'

set output 'img/susceptibility_SW.eps'
plot 'data/8_SW_9000.obs'   using 1:5 pt 2 lc 7 ps 0.5 title 'SW: L =   8',\
     'data/16_SW_9000.obs'  using 1:5 pt 2 lc 1 ps 0.5 title 'SW: L =  16',\
     'data/32_SW_9000.obs'  using 1:5 pt 2 lc 6 ps 0.5 title 'SW: L =  32',\
     'data/64_SW_9000.obs'  using 1:5 pt 2 lc 3 ps 0.5 title 'SW: L =  64'


