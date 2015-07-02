set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set xlabel "{/Symbol b}"
set ylabel "{/Symbol x}"

set yrange[0:20]

bc = 0.44
a = 1
n = 1
f(x)=a/abs(((x-bc)/(x*bc))**n)

set output 'img/correlation_MH.eps'
fit [x=0.395:0.42] f(x) 'data/128_MH_99000.fit' using 1:2:3 via a,n,bc
plot 'data/128_MH_99000.fit' pt 7 ps 0.5 lc rgb '#000000' title 'MH',\
      f(x) lc rgb '#000000' title sprintf("{/Symbol n} = %.3f,  {/Symbol b}_c = %.3f", n, bc)

bc = 0.44
a = 1
n = 1

set output 'img/correlation_SW.eps'
fit [x=0.395:0.425] f(x) 'data/128_SW_99000.fit' using 1:2:3 via a,n,bc
plot 'data/128_SW_99000.fit' pt 7 ps 0.5 lc rgb '#000000' title 'SW',\
      f(x) lc rgb '#000000' title sprintf("{/Symbol n} = %.3f,  {/Symbol b}_c = %.3f", n, bc)

