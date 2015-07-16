#!/usr/bin/gnuplot

## observables

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12
set samples 100000
color = "4 7 1 6"
set xrange[-10:10]

## magnetization

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "mL^{{/Symbol b}/{/Symbol n}}"

beta = "0.85303 0.93607 0.97245 0.99079"

set output 'img/magnetization.eps'
set title 'SW'
plot for [i=1:words(beta)] sprintf('data/%d_SW.obs',2*(2**i)) u (((($1)-word(beta, i))/word(beta, i))*exp(6.0*log(2*(2**i))/5.0)):\
                           ($5)*exp(2.0*log(2*(2**i))/15.0) w linespoints pt 7 ps 0.5 lc word(color, i) title sprintf('%d^2',2*(2**i))

## susceptibility

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "{/Symbol c}/L^{{/Symbol g}/{/Symbol n}}"

set output 'img/susceptibility.eps'
set title 'SW'

plot for [i=1:words(beta)] sprintf('data/%d_SW.obs',2*(2**i)) u (((($1)-word(beta, i))/word(beta, i))*exp(6.0*log(2*(2**i))/5.0)):\
                           ($6)/exp(26.0*log(2*(2**i))/15.0):($7)/exp(26.0*log(2*(2**i))/15.0) w e pt 7 ps 0.5 lc word(color, i)\
                            title sprintf('%d^2',2*(2**i))


## heat capacity

set xlabel "xL^{1/{/Symbol n}}"
set ylabel "C/L^{{/Symbol a}/{/Symbol n}}"

beta = "0.93530 0.96457 0.98577 0.99651"

set output 'img/heat_capacity.eps'
set title 'SW'
plot for [i=1:words(beta)] sprintf('data/%d_SW.obs',2*(2**i)) u (((($1)-word(beta, i))/word(beta, i))*exp(6.0*log(2*(2**i))/5.0)):\
                           ($3)/exp(0.4*log(2*(2**i))):($4)/exp(0.4*log(2*(2**i))) w e pt 7 ps 0.5 lc word(color, i) title sprintf('%d^2',2*(2**i))

