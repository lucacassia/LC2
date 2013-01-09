set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.0 # --- indigo
set style line 2 lc rgb '#bf0d23' lt 1 lw 2 pt 7 ps 1.0 # --- red
set style line 3 lc rgb '#0060ad' lt 1 lw 1 pt 7 ps 0.5 # --- indigo
set style line 4 lc rgb '#0060ad' pt 1 # --- indigo
set border linewidth 1.5
set grid
set title "Maxwell-Boltzmann"
set xlabel "v"
set ylabel "PDF"
set term postscript enhanced color landscape lw 1 "Verdana,10"
set output 'Maxwell-Boltzmann.eps'
f(x) = N*sqrt(2/3.1415/T/T/T)*x*x*exp(-x*x/2/T)
T=0.2
N=5
fit f(x) 'bin.dat' using 1:2 via T,N
plot 'bin.dat' using 1:2:3 w errorbars ls 2 title 'PDF', f(x) ls 1 title 'fit'
