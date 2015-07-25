<TeXmacs|1.99.2>

<style|article>

<\body>
  <doc-data|<doc-title|Laboratory of Computational
  Physics>|<doc-author|<author-data|<author-name|Luca
  Cassia>|<\author-affiliation>
    Dipartimento di Fisica, Università di Milano-Bicocca

    I-20126 Milano, Italy
  </author-affiliation>|<\author-email>
    l.cassia@campus.unimib.it
  </author-email>>>>

  <\table-of-contents|toc>
    <vspace*|1fn><with|font-series|bold|math-font-series|bold|1<space|2spc>Potts
    Model <with|mode|math|2d>> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-2>>

    <with|par-left|1tab|1.2<space|2spc>Autocorrelation Times
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-4>>

    <with|par-left|1tab|1.3<space|2spc>Observables
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-7>>

    <with|par-left|1tab|1.4<space|2spc><with|mode|math|\<beta\>> Critical
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-10>>

    <with|par-left|1tab|1.5<space|2spc>Probability Distribution Functions
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-14>>

    <with|par-left|1tab|1.6<space|2spc>Spatial Correlations
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-17>>

    <with|par-left|1tab|1.7<space|2spc>Finite Size Scaling
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-21>>
  </table-of-contents>

  <section|Potts Model <math|2d>>

  The <math|2>-dimensional Potts Model constitutes a generalization of the
  Ising Model to a generic number <math|q\<in\>\<bbb-N\>> of states for the
  spin variable. A useful way to picture the space of states of a Potts spin
  variable is to map it to the space <math|U<around*|(|1|)>\<subset\>\<bbb-C\>>
  of unimodular complex numbers. We represent each state <math|p> with the
  <math|p<rsup|th>> complex <math|q>-root of the unity in <math|\<bbb-C\>>:

  <\equation>
    p\<mapsto\>e<rsup|<frac|2\<pi\>i|q>*p>\<in\>U<around*|(|1|)>
  </equation>

  Lets consider a <math|3>-state Potts system of <math|L\<times\>L> spins
  situated on the points of a regular square lattice with periodic boundary
  conditions (PBC) in both directions, as for the Ising Model. Each spin
  interacts with its nearest neighbours inside the lattice, with an
  Hamiltonian:

  <\equation>
    \<cal-H\>=-<big|sum><rsub|<around*|\<langle\>|i,j|\<rangle\>>>\<delta\><rsub|\<sigma\><rsub|i>,\<sigma\><rsub|j>>
  </equation>

  where the sum is taken only over the set of unordered pairs
  <math|<around*|\<langle\>|i,j|\<rangle\>>> such that
  <math|\<sigma\><rsub|i>> and <math|\<sigma\><rsub|j>> are nearest
  neighbours. The implementation of the MH algorithm is completely analogous
  to that for the ising model, while for the SW algorithm we need to modify
  the probability with which to activate the link between neighbouring spins.
  In fact, the partition function can be written as:

  <\equation>
    Z<around*|[|\<beta\>|]>=<big|sum><rsub|<around*|{|\<sigma\>|}>>\<mathe\><rsup|\<beta\><big|sum><rsub|<around*|\<langle\>|i*j|\<rangle\>>>\<delta\><rsub|\<sigma\><rsub|i>*\<sigma\><rsub|j>>>=<big|sum><rsub|<around*|{|\<sigma\>|}>><big|prod><rsub|<around*|\<langle\>|i*j|\<rangle\>>>\<mathe\><rsup|\<beta\>*\<delta\><rsub|\<sigma\><rsub|i>*\<sigma\><rsub|j>>>
  </equation>

  using the Fortuin-Kasteleyn representation we can write:

  <\equation>
    \<mathe\><rsup|\<beta\>*\<delta\><rsub|\<sigma\><rsub|i>*\<sigma\><rsub|j>>>=1+<around*|(|\<mathe\><rsup|\<beta\>>-1|)>\<delta\><rsub|\<sigma\><rsub|i>*\<sigma\><rsub|j>>=\<mathe\><rsup|\<beta\>>*<around*|[|\<mathe\><rsup|-\<beta\>>+<around*|(|1-\<mathe\><rsup|-\<beta\>>|)>*\<delta\><rsub|\<sigma\><rsub|i>*\<sigma\><rsub|j>>|]>
  </equation>

  therefore we can immediately read the probability of establishing a link
  between neighbouring spins as:

  <\equation>
    p=1-\<mathe\><rsup|-\<beta\>>
  </equation>

  <subsection|Thermalization>

  As for the case of the Ising Model, we opted for a cold start approach. In
  (Fig.<reference|fig:thermalization>) we present the thermalization process
  for MH and SW at various temperatures and for two different volumes:
  <math|32<rsup|2>> and <math|64<rsup|2>>. The observed quantity is the
  energy density:

  <\equation>
    e=<around*|\<langle\>|\<cal-H\>|\<rangle\>>/V
  </equation>

  <\big-figure>
    <image|../potts/thermalization/img/32_MH_thermalization.eps|0.5par|||><image|../potts/thermalization/img/32_SW_thermalization.eps|0.5par|||>

    <image|../potts/thermalization/img/64_MH_thermalization.eps|0.5par|||><image|../potts/thermalization/img/64_SW_thermalization.eps|0.5par|||>
  </big-figure|<label|fig:thermalization>Thermalization process of the energy
  density on a lattice <math|32\<times\>32> in the top two pictures and
  <math|64\<times\>64> in the bottom two. MH on the left, SW on the right.>

  As expected, the MH algorithm has a slower mixing rate due to the critical
  slowing down effect near the critical inverse temperature:

  <\equation>
    <label|eq:betac>\<beta\><rsub|c>=log <around*|(|1+<sqrt|3>|)>\<approx\>1.00505254\<ldots\>
  </equation>

  For this reason we focus only on the study of the model through the
  implementation of the much more efficient SW algorithm. The thermalization
  time is taken to be <math|1000> Markov steps.

  \;

  <subsection|<label|sect:autocorrelation>Autocorrelation Times>

  We now study the correlations present in the energy density signal produced
  by the Markov process. As we did for the Ising Model, we fit the data using
  the integrated autocorrelation time exact result for a bivariate gaussian
  signal:

  <\equation>
    \<tau\><rsub|int><around*|(|k<rsub|max>|)>=\<tau\><rsub|int><around*|[|1-<frac|2*\<tau\><rsub|exp>|2*\<tau\><rsub|exp>+1>*\<mathe\><rsup|-k<rsub|max>/\<tau\><rsub|exp>>|]>
  </equation>

  <\big-figure|<image|../potts/autocorrelation/img/SW_acr.eps|0.5par|||><image|../potts/autocorrelation/img/SW_fit.eps|0.5par|||>>
    <label|fig:autocorrelation_time>Plots of the autocorrelation of the
    signal for <math|e>. On the left is shown the integrated autocorrelation
    time <math|\<tau\><rsub|int>> as a function <math|k<rsub|max>>. The
    chromatic scale indicates the value of <math|\<beta\>>. On the right is
    shown the plot of <math|\<tau\><rsub|int>> as a function of
    <math|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>. The lattice
    size is <math|L=8>.
  </big-figure>

  As already pointed out, the autocorrelation time of the SW signal is very
  low even near the phase transition because of the dynamical critical
  exponent <math|z\<approx\>0>. Thus we can safely set the bin size to
  <math|50>.

  <big-figure|<image|../potts/autocorrelation/img/SW_3d.eps|0.5par|||>|3d
  plot of <math|\<tau\><rsub|int><around*|(|\<beta\>,k<rsub|max>|)>> for a
  Potts Model of volume <math|8\<times\>8> near <math|\<beta\><rsub|c>>.>

  <subsection|Observables>

  The main observables of interest for this system are the energy density
  <math|e> and the magnetization <math|m>:

  <\equation>
    e=<around*|\<langle\>|\<cal-H\>|\<rangle\>>/V,
  </equation>

  <\equation>
    m=<around*|\<langle\>|<around*|\||\<cal-M\>|\|>|\<rangle\>>,<space|2em>\<cal-M\>=<frac|1|V>*<big|sum><rsub|i>\<sigma\><rsub|i>
  </equation>

  For each inverse temperature we compute the estimate of the generic
  observable <math|\<cal-O\>> from a set of <math|5\<cdot\>10<rsup|4>>
  measurements.

  <big-figure|<image|../potts/observables/img/energy.eps|0.5par|||><image|../potts/observables/img/magnetization.eps|0.5par|||>|Left:
  energy density <math|e> as a function of <math|\<beta\>>. Right:
  magnetization modulus <math|m>. The various colors represent different
  lattice sizes: <math|L=4,8,16,32>.>

  As the lattice volume <math|V=L<rsup|2>> increases, both the energy and
  magnetization curves approach their infinite volume limit.

  \;

  We also plot the heat capacity and the magnetic susceptibility:

  <\equation>
    C=<frac|\<beta\><rsup|2>|V>*<around*|\<langle\>|<around*|(|\<cal-H\>-<around*|\<langle\>|\<cal-H\>|\<rangle\>>|)><rsup|2>|\<rangle\>>
  </equation>

  <\equation>
    \<chi\>=\<beta\>*V*<around*|\<langle\>|<around*|(|<around*|\||\<cal-M\>|\|>-<around*|\<langle\>|<around*|\||\<cal-M\>|\|>|\<rangle\>>|)><rsup|2>|\<rangle\>>
  </equation>

  <big-figure|<image|../potts/observables/img/heat_capacity.eps|0.5par|||><image|../potts/observables/img/susceptibility.eps|0.5par|||>|<label|fig:susceptibility>Left:
  heat capacity as a function of <math|\<beta\>>. Right: magnetic
  susceptibility. The various colors represent different lattice sizes:
  <math|L=4,8,16,32>,64.>

  <subsection|<math|\<beta\>> Critical><label|sec:betafss>

  From a power law fit of the points near the peak of each dataset we obtain
  estimates for the pseudocritical <math|\<beta\>>-values at finite sizes
  <math|L=4,8,16,32,64>.

  <\big-figure>
    <image|../potts/observables/img/4SW1.eps|0.4par|||><image|../potts/observables/img/4SW2.eps|0.4par|||>

    <image|../potts/observables/img/8SW1.eps|0.4par|||><image|../potts/observables/img/8SW2.eps|0.4par|||>

    <image|../potts/observables/img/16SW1.eps|0.4par|||><image|../potts/observables/img/16SW2.eps|0.4par|||>

    <image|../potts/observables/img/32SW1.eps|0.4par|||><image|../potts/observables/img/32SW2.eps|0.4par|||>

    <image|../potts/observables/img/64SW1.eps|0.4par|||><image|../potts/observables/img/64SW2.eps|0.4par|||>
  </big-figure|Fit of the heat capacity and susceptibility peaks.>

  <big-table|<block|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<math|L>>|<cell|<math|\<beta\><rsub|max><around*|(|C|)>>>|<cell|<math|\<beta\><rsub|max><around*|(|\<chi\>|)>>>>|<row|<cell|<math|4>>|<cell|<math|0.93530\<pm\>0.00181>>|<cell|<math|0.85303\<pm\>0.00198>>>|<row|<cell|<math|8>>|<cell|<math|0.96457\<pm\>0.00168>>|<cell|<math|0.93607\<pm\>0.00078>>>|<row|<cell|<math|16>>|<cell|<math|0.98577\<pm\>0.00133>>|<cell|<math|0.97245\<pm\>0.00123>>>|<row|<cell|<math|32>>|<cell|<math|0.99651\<pm\>0.00048>>|<cell|<math|0.99079\<pm\>0.00053>>>|<row|<cell|64>|<cell|<math|1.00092\<pm\>0.00045>>|<cell|<math|0.99917\<pm\>0.00016>>>>>>|Pseudocritical
  <math|\<beta\>>-values obtained by polynomial fit of the peaks of <math|C>
  and <math|\<chi\>>.>

  The polynomial function we used for the fit is:

  <\equation>
    f<around*|(|\<beta\>|)>=A+B*<around*|(|\<beta\>-\<beta\><rsub|max>|)><rsup|2>+C*<around*|(|\<beta\>-\<beta\><rsub|max>|)><rsup|3>
  </equation>

  We can now obtain an estimate of <math|\<beta\><rsub|c>> from a power law
  fit to the location of the maxima <math|\<beta\><rsub|max>>:

  <\equation>
    \<beta\><rsub|max>=\<beta\><rsub|c>-c*L<rsup|-\<nu\>>
  </equation>

  <big-figure|<image|../potts/fss/img/beta_SW.eps|0.5par|||>|Pseudocritical
  inverse temperature fit. The purple lines are relative to the heat capacity
  <math|C> while the green ones to the magnetic susceptibility
  <math|\<chi\>>.>

  The result of the fit are:

  <\equation>
    \<beta\><rsub|c><around*|(|C|)>=1.00777\<pm\>0.00252
  </equation>

  <\equation>
    \<beta\><rsub|c><around*|(|\<chi\>|)>=1.00616\<pm\>0.00043
  </equation>

  As we can see, both values obtained from the fit of <math|C> and
  <math|\<chi\>> are very close to the exact solution of
  (<reference|eq:betac>). We could improve these results further by
  discarding some measurements done at smaller volumes (<math|L=4> and
  <math|L=8> for instance) and repeat the measurement procedure for larger
  lattice sizes.

  <subsection|Probability Distribution Functions>

  We study the probability distribution of the magnetization for a lattice of
  size <math|L=8>. The energy and magnetization levels of a discrete system
  are quantized. In particular, for a Potts Model on a square lattice of size
  <math|L<rsup|2>> with PBC, there are exactly
  <math|<frac|1|2><around*|(|L<rsup|2>+1|)><around*|(|L<rsup|2>+2|)>>
  magnetization levels distributed as in (Fig.<reference|fig:levels>):

  <big-figure|<image|../potts/histograms/img/levels.eps|0.5par|||>|<label|fig:levels>Magnetization
  levels of the Potts Model on a <math|4\<times\>4> lattice. We remark that,
  since the average is a convex function of its arguements, every
  magnetization level must be contained in the convex hull of the three basic
  magnetizations <math|1, <frac|-1+i*<sqrt|3>|2>, <frac|-1-i*<sqrt|3>|2>>
  (<with|font-shape|italic|magnetization domain>).>

  With this consideration one can construct the probability distribution
  function of the magnetization just by counting the number of samples in
  each level (for <math|L> not too large):

  <\big-figure>
    <image|../potts/histograms/img/8_0.750000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.810000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.830000_SW_histogram.eps|0.33par|||>

    <image|../potts/histograms/img/8_0.850000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.870000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.890000_SW_histogram.eps|0.33par|||>

    <image|../potts/histograms/img/8_0.910000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.930000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.950000_SW_histogram.eps|0.33par|||>
  </big-figure|<label|fig:pdfMH>Probability distribution functions of
  <math|\<cal-M\>\<in\>\<bbb-C\>> obtained from <math|10<rsup|6>> sweeps of
  SW on a lattice <math|8\<times\>8>.>

  At low values of <math|\<beta\>> (high temperature <math|T>) the system is
  found most probably in the disordered state <math|\<cal-M\>\<approx\>0> and
  every spin state has equal probability. As the temperature lowers and
  approaches the critical point <math|T<rsub|c>>, the probability
  distribution widens and takes the shape of a triangle oriented as the
  magnetization domain. Finally, as we cross the critical point, the
  distribution becomes peaked around three different points situated along
  the directions of the cubic roots of the unity and representing high
  probabilities for configurations where a large number of spins are aligned.
  In the limit <math|\<beta\>\<rightarrow\>\<infty\>>
  (<math|T\<rightarrow\>0>) these points tend to the vertices of the triangle
  and the peaks of the probability distribution become very narrow.

  <subsection|Spatial Correlations><label|sec:corr>

  The two-point correlation function is defined as:

  <\equation>
    G <around*|(|<wide|r|\<vect\>><rsub|i>-<wide|r|\<vect\>><rsub|j>|)>=<around*|\<langle\>|Re<around*|(|\<sigma\><rsub|i>*\<sigma\><rsup|\<ast\>><rsub|j>|)>|\<rangle\>><space|1em>\<sim\><space|1em>exp<around*|(|-<around*|\||<wide|r|\<vect\>><rsub|i>-<wide|r|\<vect\>><rsub|j>|\|>/\<xi\>|)><space|1em>for
    large<space|1em><around*|\||<wide|r|\<vect\>><rsub|i>-<wide|r|\<vect\>><rsub|j>|\|>
  </equation>

  where <math|\<xi\>> is the correlation length of the system:

  <\equation>
    \<xi\>=-lim<rsub|<around*|\||<wide|r|\<vect\>>|\|>\<rightarrow\>\<infty\>><around*|(|<around*|\||<wide|r|\<vect\>>|\|>/ln
    G<around*|(|<wide|r|\<vect\>>|)>|)>
  </equation>

  <\big-figure>
    <image|../potts/potts_128x128_0.200000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.500000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.700000.ppm|0.3par|||>

    <image|../potts/potts_128x128_0.800000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.900000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.950000.ppm|0.3par|||>

    <image|../potts/potts_128x128_0.970000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.980000.ppm|0.3par|||><space|1em><image|../potts/potts_128x128_0.990000.ppm|0.3par|||>
  </big-figure|Ilustration of the growth of spatial correlations when
  criticality is approached on a lattice <math|128\<times\>128> :
  <math|\<beta\>=0.2, 0.5, 0.7,0.8, 0.9, 0.95, 0.97, 0.98, 0.99>.>

  Analogously to the case of the Ising Model we define observables:

  <\equation>
    S<rsub|x>\<equiv\><frac|1|L>*<big|sum><rsub|y=1><rsup|L>\<sigma\><around*|(|x,y|)>
  </equation>

  <\equation>
    S<rsub|y>\<equiv\><frac|1|L>*<big|sum><rsub|x=1><rsup|L>\<sigma\><around*|(|x,y|)>
  </equation>

  and we compute the correlation function as:

  <\equation>
    G<around*|(|r|)>=<frac|1|2>*<around*|(|<frac|1|L>*<big|sum><rsup|L><rsub|x=1><frac|S<rsub|x>*S<rsup|\<ast\>><rsub|x+r>|S<rsub|x>*S<rsub|x><rsup|\<ast\>>>+<frac|1|L>*<big|sum><rsup|L><rsub|y=1><frac|S<rsub|y>*S<rsup|\<ast\>><rsub|y+r>|S<rsub|y>*S<rsub|y><rsup|\<ast\>>>|)>
  </equation>

  Again the fit is done via the hyperbolic cosine function:

  <\equation>
    <label|eq:cosh>G<around*|(|r|)>\<sim\><frac|1|2>*<around*|(|\<mathe\><rsup|<frac|r|\<xi\>>>+\<mathe\><rsup|<frac|L-r|\<xi\>>>|)>\<sim\>cosh
    <around*|(|<frac|r-<frac|L|2>|\<xi\>>|)>
  </equation>

  <big-figure|<image|../potts/correlation/img/64_green_SW.eps|0.5par|||><image|../potts/correlation/img/64_green_SW_3d.eps|0.5par|||>|<label|fig:corr>Correlation
  functions for various values of <math|\<beta\>>. The lattice size used is
  <math|64\<times\>64>. As a precaution, we considers an interval in
  <math|\<beta\>>-space such that the correlation length is much smaller that
  the size of the lattice (approximately one order of magnitude smaller). >

  The correlation length diverges at the critical point as:

  <\equation>
    \<xi\>\<sim\>A*<around*|\||x|\|><rsup|-\<nu\>>
  </equation>

  We plot the data obained from the previous fit using logarithmic scales on
  both axis and compute the critical exponent <math|\<nu\>> from the linear
  fit:

  <\equation>
    log<around*|(|\<xi\>|)>=log<around*|(|A|)>-\<nu\>*log<around*|(|<around*|\||x|\|>|)>
  </equation>

  <big-figure|<image|../potts/correlation/img/correlation_SW.eps|0.5par|||>|Plot
  of the correlation length dependence on the parameter
  <math|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>> for a lattice of
  size <math|64\<times\>64>. The errors are computed by jackknife binning of
  the fit data from (Fig.<reference|fig:corr>).>

  The result of the fit is:

  <\equation>
    \<nu\><rsub|SW>=0.80839\<pm\>0.00734
  </equation>

  which is comparable with the exact value:

  <\equation*>
    \<nu\>=<frac|5|6>\<approx\>0.83333\<ldots\>
  </equation*>

  <subsection|Finite Size Scaling><label|sect:fss>

  The critical exponents of the model are:

  <big-table|<block|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<math|\<nu\>>>|<cell|<math|5/6>>>|<row|<cell|<math|\<alpha\>>>|<cell|<math|1/3>>>|<row|<cell|<math|\<beta\>>>|<cell|<math|1/9>>>|<row|<cell|<math|\<gamma\>>>|<cell|<math|13/9>>>>>>|Exact
  critical exponents for the Potts model in <math|2d>.>

  We therefore rescale the observables as:

  <\equation>
    m\<rightarrow\>m*L<rsup|\<beta\>/\<nu\>>
  </equation>

  <\equation>
    \<chi\>\<rightarrow\>\<chi\>/L<rsup|\<gamma\>/\<nu\>>
  </equation>

  <\equation>
    C\<rightarrow\>C/L<rsup|\<alpha\>/\<nu\>>
  </equation>

  and plot the data expressed as function of the scaling variable
  <math|x*L<rsup|1/\<nu\>>>:

  <\big-figure>
    <image|../potts/fss/img/magnetization.eps|0.5par|||>

    <image|../potts/fss/img/susceptibility.eps|0.5par|||>

    <image|../potts/fss/img/heat_capacity.eps|0.5par|||>
  </big-figure|<label|fig:fss>Finite Size Scaling study for the lattice sizes
  <math|4<rsup|2>,8<rsup|2>,16<rsup|2>,32<rsup|2>>. The top plot represents
  the scaling of the magnetization, the center one the magnetic
  susceptibility and the bottom one the heat capacity.>

  <with|font-shape|italic|Remark:> the curves obtained by rescaling of the
  magnetization, susceptibility and heat capacity, fit well to the FSS
  functions <math|f<rsub|i><around*|(|x*L<rsup|1/\<nu\>>|)>> when the system
  has a large enough volume that the boundary effects are nigligible.
  However, for smaller volumes (<math|L=4,8>) those effects are more
  important and, as we can se from (Fig.<reference|fig:fss>), the fit becomes
  worse. In particular we see that the value <math|L=4> is too small for the
  scaling hypothesis to apply.
</body>

<\initial>
  <\collection>
    <associate|page-even-footer|>
    <associate|page-even-header|>
    <associate|page-medium|paper>
    <associate|page-odd-footer|>
    <associate|page-odd-header|>
    <associate|page-screen-margin|false>
    <associate|page-width-margin|false>
    <associate|preamble|false>
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|1.4|4>>
    <associate|auto-11|<tuple|6|5>>
    <associate|auto-12|<tuple|1|6>>
    <associate|auto-13|<tuple|7|6>>
    <associate|auto-14|<tuple|1.5|7>>
    <associate|auto-15|<tuple|8|7>>
    <associate|auto-16|<tuple|9|8>>
    <associate|auto-17|<tuple|1.6|9>>
    <associate|auto-18|<tuple|10|9>>
    <associate|auto-19|<tuple|11|10>>
    <associate|auto-2|<tuple|1.1|1>>
    <associate|auto-20|<tuple|12|11>>
    <associate|auto-21|<tuple|1.7|11>>
    <associate|auto-22|<tuple|2|11>>
    <associate|auto-23|<tuple|13|12>>
    <associate|auto-24|<tuple|3|9>>
    <associate|auto-25|<tuple|14|9>>
    <associate|auto-26|<tuple|15|10>>
    <associate|auto-27|<tuple|16|10>>
    <associate|auto-28|<tuple|17|10>>
    <associate|auto-29|<tuple|3|9>>
    <associate|auto-3|<tuple|1|2>>
    <associate|auto-30|<tuple|19|9>>
    <associate|auto-31|<tuple|20|21>>
    <associate|auto-32|<tuple|21|22>>
    <associate|auto-33|<tuple|1.8|23>>
    <associate|auto-34|<tuple|3|23>>
    <associate|auto-35|<tuple|23|24>>
    <associate|auto-36|<tuple|24|?>>
    <associate|auto-4|<tuple|1.2|2>>
    <associate|auto-5|<tuple|2|3>>
    <associate|auto-6|<tuple|3|3>>
    <associate|auto-7|<tuple|1.3|3>>
    <associate|auto-8|<tuple|4|4>>
    <associate|auto-9|<tuple|5|4>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:betac|<tuple|7|2>>
    <associate|eq:cosh|<tuple|22|10>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:corr|<tuple|11|10>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:fss|<tuple|13|12>>
    <associate|fig:heatcapacity|<tuple|5|5>>
    <associate|fig:levels|<tuple|8|7>>
    <associate|fig:pdfMH|<tuple|9|8>>
    <associate|fig:pdfSW|<tuple|13|7>>
    <associate|fig:susceptibility|<tuple|5|4>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:thermalization|<tuple|1|2>>
    <associate|fig:thermalizationMH|<tuple|2|3>>
    <associate|fig:thermalizationSW|<tuple|3|4>>
    <associate|fig:toruseffect|<tuple|1|3>>
    <associate|footnote-1|<tuple|1|?>>
    <associate|footnr-1|<tuple|1|?>>
    <associate|result_box|<tuple|5|?>>
    <associate|sec:betafss|<tuple|1.4|4>>
    <associate|sec:corr|<tuple|1.6|9>>
    <associate|sect:autocorrelation|<tuple|1.2|2>>
    <associate|sect:fss|<tuple|1.7|11>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|Thermalization process of the energy density on a lattice
      <with|mode|<quote|math>|32\<times\>32> in the top two pictures and
      <with|mode|<quote|math>|64\<times\>64> in the bottom two. MH on the
      left, SW on the right.|<pageref|auto-3>>

      <\tuple|normal>
        Plots of the autocorrelation of the signal for
        <with|mode|<quote|math>|e>. On the left is shown the integrated
        autocorrelation time <with|mode|<quote|math>|\<tau\><rsub|int>> as a
        function <with|mode|<quote|math>|k<rsub|max>>. The chromatic scale
        indicates the value of <with|mode|<quote|math>|\<beta\>>. On the
        right is shown the plot of <with|mode|<quote|math>|\<tau\><rsub|int>>
        as a function of <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>.
        The lattice size is <with|mode|<quote|math>|L=8>.
      </tuple|<pageref|auto-5>>

      <tuple|normal|3d plot of <with|mode|<quote|math>|\<tau\><rsub|int><around*|(|\<beta\>,k<rsub|max>|)>>
      for a Potts Model of volume <with|mode|<quote|math>|8\<times\>8> near
      <with|mode|<quote|math>|\<beta\><rsub|c>>.|<pageref|auto-6>>

      <tuple|normal|Left: energy density <with|mode|<quote|math>|e> as a
      function of <with|mode|<quote|math>|\<beta\>>. Right: magnetization
      modulus <with|mode|<quote|math>|m>. The various colors represent
      different lattice sizes: <with|mode|<quote|math>|L=4,8,16,32>.|<pageref|auto-8>>

      <tuple|normal|Left: heat capacity as a function of
      <with|mode|<quote|math>|\<beta\>>. Right: magnetic susceptibility. The
      various colors represent different lattice sizes:
      <with|mode|<quote|math>|L=4,8,16,32>,64.|<pageref|auto-9>>

      <tuple|normal|Fit of the heat capacity and susceptibility
      peaks.|<pageref|auto-11>>

      <tuple|normal|Pseudocritical inverse temperature fit. The purple lines
      are relative to the heat capacity <with|mode|<quote|math>|C> while the
      green ones to the magnetic susceptibility
      <with|mode|<quote|math>|\<chi\>>.|<pageref|auto-13>>

      <tuple|normal|Magnetization levels of the Potts Model on a
      <with|mode|<quote|math>|4\<times\>4> lattice. We remark that, since the
      average is a convex function of its arguements, every magnetization
      level must be contained in the convex hull of the three basic
      magnetizations <with|mode|<quote|math>|1, <frac|-1+i*<sqrt|3>|2>,
      <frac|-1-i*<sqrt|3>|2>> (<with|font-shape|<quote|italic>|magnetization
      domain>).|<pageref|auto-15>>

      <tuple|normal|Probability distribution functions of
      <with|mode|<quote|math>|\<cal-M\>\<in\>\<bbb-C\>> obtained from
      <with|mode|<quote|math>|10<rsup|6>> sweeps of SW on a lattice
      <with|mode|<quote|math>|8\<times\>8>.|<pageref|auto-16>>

      <tuple|normal|Ilustration of the growth of spatial correlations when
      criticality is approached on a lattice
      <with|mode|<quote|math>|128\<times\>128> :
      <with|mode|<quote|math>|\<beta\>=0.2, 0.5, 0.7,0.8, 0.9, 0.95, 0.97,
      0.98, 0.99>.|<pageref|auto-18>>

      <tuple|normal|Correlation functions for various values of
      <with|mode|<quote|math>|\<beta\>>. The lattice size used is
      <with|mode|<quote|math>|64\<times\>64>. As a precaution, we considers
      an interval in <with|mode|<quote|math>|\<beta\>>-space such that the
      correlation length is much smaller that the size of the lattice
      (approximately one order of magnitude smaller). |<pageref|auto-19>>

      <tuple|normal|Plot of the correlation length dependence on the
      parameter <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>
      for a lattice of size <with|mode|<quote|math>|64\<times\>64>. The
      errors are computed by jackknife binning of the fit data from
      (Fig.<reference|fig:corr>).|<pageref|auto-20>>

      <tuple|normal|Finite Size Scaling study for the lattice sizes
      <with|mode|<quote|math>|4<rsup|2>,8<rsup|2>,16<rsup|2>,32<rsup|2>>. The
      top plot represents the scaling of the magnetization, the center one
      the magnetic susceptibility and the bottom one the heat
      capacity.|<pageref|auto-23>>
    </associate>
    <\associate|table>
      <tuple|normal|Pseudocritical <with|mode|<quote|math>|\<beta\>>-values
      obtained by polynomial fit of the peaks of <with|mode|<quote|math>|C>
      and <with|mode|<quote|math>|\<chi\>>.|<pageref|auto-12>>

      <tuple|normal|Exact critical exponents for the Potts model in
      <with|mode|<quote|math>|2d>.|<pageref|auto-22>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Potts
      Model <with|mode|<quote|math>|2d>> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Autocorrelation Times
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-4>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Observables
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-7>>

      <with|par-left|<quote|1tab>|1.4<space|2spc><with|mode|<quote|math>|\<beta\>>
      Critical <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-10>>

      <with|par-left|<quote|1tab>|1.5<space|2spc>Probability Distribution
      Functions <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-14>>

      <with|par-left|<quote|1tab>|1.6<space|2spc>Spatial Correlations
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-17>>

      <with|par-left|<quote|1tab>|1.7<space|2spc>Finite Size Scaling
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-21>>
    </associate>
  </collection>
</auxiliary>