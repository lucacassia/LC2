#!/usr/bin/gnuplot

set terminal postscript eps size 4.5,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

## beta

set ylabel "{/Symbol b}_{max}"
set xlabel "1/L"
set fit errorvariables

n1=1
n2=1
f(x) = b1-c1*x**n1
g(x) = b2-c2*x**n2
fit f(x) 'data/beta.sw' using (1/$1):2:3 via b1,c1,n1
fit g(x) 'data/beta.sw' using (1/$1):4:5 via b2,c2,n2

# helper function for getting the rotation angle of the labels in degree

dx = 0.25
dy = 1.0-0.84
s = dx/dy

r(x) = (atan(s*x)/pi)*180.0

set label 1 '{/Symbol b}_{max}(C)' at 0.21,f(0.2) rotate by r(-c1*n1*exp((n1-1)*log(0.2))) left tc ls 1
set label 2 '{/Symbol b}_{max}({/Symbol c})' at 0.205,g(0.2) rotate by r(-c2*n2*exp((n2-1)*log(0.2))) left tc ls 2

set output 'img/beta_SW.eps'
set title 'SW'
plot  'data/beta.sw' using (1/$1):2:3 w errorbars pt 7 lc 1 notitle,\
      f(x) ls 1  title sprintf('{/Symbol b}_c = %.6f+/-%.6f', b1, b1_err),\
      'data/beta.sw' using (1/$1):4:5 w errorbars pt 7 lc 2 notitle,\
      g(x) ls 2  title sprintf('{/Symbol b}_c = %.6f+/-%.6f', b2, b2_err)

