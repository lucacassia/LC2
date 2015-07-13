## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set samples 100000

## magnetization

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "mL^{{/Symbol b}/{/Symbol n}}"

set xrange[-20:20]
set output 'img/magnetization_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'    u (((($1)-0.39448)/0.39448)*8):(($5)*sqrt(sqrt(sqrt(8))))   w linespoints pt 7 lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'   u (((($1)-0.41541)/0.41541)*16):(($5)*sqrt(sqrt(sqrt(16)))) w linespoints pt 7 lc 7 title 'L =   16',\
     'data/32_MH_99000.obs'   u (((($1)-0.42620)/0.42620)*32):(($5)*sqrt(sqrt(sqrt(32)))) w linespoints pt 7 lc 1 title 'L =   32',\
     'data/64_MH_99000.obs'   u (((($1)-0.43405)/0.43405)*64):(($5)*sqrt(sqrt(sqrt(64)))) w linespoints pt 7 lc 6 title 'L =   64'


set output 'img/magnetization_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'    u (((($1)-0.39295)/0.39295)*8):(($5)*sqrt(sqrt(sqrt(8))))   w linespoints pt 7 lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'   u (((($1)-0.41729)/0.41729)*16):(($5)*sqrt(sqrt(sqrt(16)))) w linespoints pt 7 lc 7 title 'L =   16',\
     'data/32_SW_9000.obs'   u (((($1)-0.42686)/0.42686)*32):(($5)*sqrt(sqrt(sqrt(32)))) w linespoints pt 7 lc 1 title 'L =   32',\
     'data/64_SW_9000.obs'   u (((($1)-0.43481)/0.43481)*64):(($5)*sqrt(sqrt(sqrt(64)))) w linespoints pt 7 lc 6 title 'L =   64'


## susceptibility
set xrange[-10:10]
set yrange[0:0.06]

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "{/Symbol c}/L^{{/Symbol g}/{/Symbol n}}"

set output 'img/susceptibility_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'   u (((($1)-0.39448)/0.39448)*8):(($6)/(exp(1.75*log(8)))):(($7)/(exp(1.75*log(8))))    w e pt 7 lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'  u (((($1)-0.41541)/0.41541)*16):(($6)/(exp(1.75*log(16)))):(($7)/(exp(1.75*log(16)))) w e pt 7 lc 7 title 'L =  16',\
     'data/32_MH_99000.obs'  u (((($1)-0.42620)/0.42620)*32):(($6)/(exp(1.75*log(32)))):(($7)/(exp(1.75*log(32)))) w e pt 7 lc 1 title 'L =  32',\
     'data/64_MH_99000.obs'  u (((($1)-0.43405)/0.43405)*64):(($6)/(exp(1.75*log(64)))):(($7)/(exp(1.75*log(64)))) w e pt 7 lc 6 title 'L =  64'

set output 'img/susceptibility_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'   u (((($1)-0.39295)/0.39295)*8):(($6)/(exp(1.75*log(8)))):(($7)/(exp(1.75*log(8))))    w e pt 7 lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'  u (((($1)-0.41729)/0.41729)*16):(($6)/(exp(1.75*log(16)))):(($7)/(exp(1.75*log(16)))) w e pt 7 lc 7 title 'L =  16',\
     'data/32_SW_9000.obs'  u (((($1)-0.42686)/0.42686)*32):(($6)/(exp(1.75*log(32)))):(($7)/(exp(1.75*log(32)))) w e pt 7 lc 1 title 'L =  32',\
     'data/64_SW_9000.obs'  u (((($1)-0.43481)/0.43481)*64):(($6)/(exp(1.75*log(64)))):(($7)/(exp(1.75*log(64)))) w e pt 7 lc 6 title 'L =  64'


## heat capacity
unset yrange
set xrange[-5:5]

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "C/log(L^{1/{/Symbol n}})"

set output 'img/heat_capacity_MH.eps'
set title 'MH'
plot 'data/8_MH_99000.obs'   u (((($1)-0.42400)/0.42400)*8):($3)/log(8):($4)/log(8)    w e pt 7 lc 4 title 'L =   8',\
     'data/16_MH_99000.obs'  u (((($1)-0.43086)/0.43086)*16):($3)/log(16):($4)/log(16) w e pt 7 lc 7 title 'L =  16',\
     'data/32_MH_99000.obs'  u (((($1)-0.43613)/0.43613)*32):($3)/log(32):($4)/log(32) w e pt 7 lc 1 title 'L =  32',\
     'data/64_MH_99000.obs'  u (((($1)-0.43718)/0.43718)*64):($3)/log(64):($4)/log(64) w e pt 7 lc 6 title 'L =  64'

set output 'img/heat_capacity_SW.eps'
set title 'SW'
plot 'data/8_SW_9000.obs'   u (((($1)-0.42296)/0.42296)*8):($3)/log(8):($4)/log(8)    w e pt 7 lc 4 title 'L =   8',\
     'data/16_SW_9000.obs'  u (((($1)-0.43174)/0.43174)*16):($3)/log(16):($4)/log(16) w e pt 7 lc 7 title 'L =  16',\
     'data/32_SW_9000.obs'  u (((($1)-0.43524)/0.43524)*32):($3)/log(32):($4)/log(32) w e pt 7 lc 1 title 'L =  32',\
     'data/64_SW_9000.obs'  u (((($1)-0.43788)/0.43788)*64):($3)/log(64):($4)/log(64) w e pt 7 lc 6 title 'L =  64'


