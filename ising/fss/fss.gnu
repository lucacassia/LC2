## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set samples 100000

## magnetization

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "mL^{{/Symbol b}/{/Symbol n}}"

set xrange[-20:20]
set output 'img/magnetization_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'    u (((($1)-0.39448)/0.39448)*8):(($5)*sqrt(sqrt(sqrt(8))))   w l lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'   u (((($1)-0.41541)/0.41541)*16):(($5)*sqrt(sqrt(sqrt(16)))) w l lc 7 title 'L =   16',\
     'data/32_MH_99000.obs'   u (((($1)-0.42620)/0.42620)*32):(($5)*sqrt(sqrt(sqrt(32)))) w l lc 1 title 'L =   32',\
     'data/64_MH_99000.obs'   u (((($1)-0.43405)/0.43405)*64):(($5)*sqrt(sqrt(sqrt(64)))) w l lc 6 title 'L =   64'


set output 'img/magnetization_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'    u (((($1)-0.39295)/0.39295)*8):(($5)*sqrt(sqrt(sqrt(8))))   w l lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'   u (((($1)-0.41729)/0.41729)*16):(($5)*sqrt(sqrt(sqrt(16)))) w l lc 7 title 'L =   16',\
     'data/32_SW_9000.obs'   u (((($1)-0.42686)/0.42686)*32):(($5)*sqrt(sqrt(sqrt(32)))) w l lc 1 title 'L =   32',\
     'data/64_SW_9000.obs'   u (((($1)-0.43481)/0.43481)*64):(($5)*sqrt(sqrt(sqrt(64)))) w l lc 6 title 'L =   64'


## susceptibility
set xrange[-10:10]
set yrange[0:0.06]

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "{/Symbol c}/L^{{/Symbol g}/{/Symbol n}}"

set output 'img/susceptibility_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'   u (((($1)-0.39448)/0.39448)*8):(($6)/(exp(1.75*log(8))))  pt 7 lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'  u (((($1)-0.41541)/0.41541)*16):(($6)/(exp(1.75*log(16)))) pt 7 lc 7 title 'L =  16',\
     'data/32_MH_99000.obs'  u (((($1)-0.42620)/0.42620)*32):(($6)/(exp(1.75*log(32)))) pt 7 lc 1 title 'L =  32',\
     'data/64_MH_99000.obs'  u (((($1)-0.43405)/0.43405)*64):(($6)/(exp(1.75*log(64)))) pt 7 lc 6 title 'L =  64'

set output 'img/susceptibility_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'   u (((($1)-0.39295)/0.39295)*8):(($6)/(exp(1.75*log(8)))) pt 7 lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'  u (((($1)-0.41729)/0.41729)*16):(($6)/(exp(1.75*log(16)))) pt 7 lc 7 title 'L =  16',\
     'data/32_SW_9000.obs'  u (((($1)-0.42686)/0.42686)*32):(($6)/(exp(1.75*log(32)))) pt 7 lc 1 title 'L =  32',\
     'data/64_SW_9000.obs'  u (((($1)-0.43481)/0.43481)*64):(($6)/(exp(1.75*log(64)))) pt 7 lc 6 title 'L =  64'


## heat capacity
set xrange[0.36:0.5]
unset yrange

set xlabel "{/Symbol b}"
set ylabel "C"

set output 'img/heat_capacity_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'   u 1:3:4 w linespoints pt 7 lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'  u 1:3:4 w linespoints pt 7 lc 7 title 'L =  16',\
     'data/32_MH_99000.obs'  u 1:3:4 w linespoints pt 7 lc 1 title 'L =  32',\
     'data/64_MH_99000.obs'  u 1:3:4 w linespoints pt 7 lc 6 title 'L =  64'

set output 'img/heat_capacity_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'   u 1:3:4 w linespoints pt 7 lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'  u 1:3:4 w linespoints pt 7 lc 7 title 'L =  16',\
     'data/32_SW_9000.obs'  u 1:3:4 w linespoints pt 7 lc 1 title 'L =  32',\
     'data/64_SW_9000.obs'  u 1:3:4 w linespoints pt 7 lc 6 title 'L =  64'


