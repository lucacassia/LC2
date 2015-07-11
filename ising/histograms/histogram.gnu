## histograms

set terminal postscript eps size 3,4.5 enhanced color dashed lw 1 "DejaVuSans" 12

set xlabel "m"
set ylabel "P(m)"

do for [i=0:6] {
    beta_value = 0.3+i*0.15/6.0
    ## MH
    set output sprintf('img/8_%.6f_MH_histogram.eps', beta_value )
    inputfile = sprintf('data/8_%.6f_MH_999000.hist', beta_value )
    plot inputfile w linespoints pt 1 lc 6 title sprintf('MH : L = 8 \@ {/Symbol b} = %.2f', beta_value )

    set output sprintf('img/8_%.6f_SW_histogram.eps', beta_value )
    inputfile = sprintf('data/8_%.6f_SW_999000.hist', beta_value )
    plot inputfile w linespoints pt 1 lc 7 title sprintf('SW : L = 8 \@ {/Symbol b} = %.2f', beta_value )
}



