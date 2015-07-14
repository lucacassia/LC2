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
    <no-break><pageref|auto-12>>

    <with|par-left|1tab|1.5<space|2spc>Probability Distribution Functions
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-18>>

    <with|par-left|1tab|1.6<space|2spc>Spatial Correlations
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-22>>

    <with|par-left|1tab|1.7<space|2spc>Finite Size Scaling
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-26>>
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
    H=-<big|sum><rsub|<around*|\<langle\>|i,j|\<rangle\>>>\<delta\><rsub|\<sigma\><rsub|i>,\<sigma\><rsub|j>>
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
    \<beta\><rsub|c>=log <around*|(|1+<sqrt|3>|)>\<approx\>1.00505254\<ldots\>
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

  \;

  As we can see, near the phase transition the autocorrelation time for the
  MH process becomes very large compared to the autocorrelation time of the
  SW process (Fig.<reference|fig:autocorrelation_time>). In fact due to the
  critical slowing down of the MH algorithm, we have
  <math|\<tau\><rsub|int><rsup|MH>\<sim\>100> compared to an autocorrelation
  time <math|\<tau\><rsub|int><rsup|SW>\<sim\>5> for SW.

  <\big-figure|<image|../potts/autocorrelation/img/SW_acr.eps|0.5par|||><image|../potts/autocorrelation/img/SW_fit.eps|0.5par|||>>
    <label|fig:autocorrelation_time>Plots of the autocorrelation of the
    signal for <math|e>. On the left is shown the integrated autocorrelation
    time <math|\<tau\><rsub|int>> as a function <math|k<rsub|max>>. The
    chromatic key indicates the value of <math|\<beta\>>. On the left is
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
    e=E/V,<space|2em>E=<around*|\<langle\>|\<cal-H\>|\<rangle\>>,<space|2em>V=L<rsup|d>
  </equation>

  <\equation>
    m=M/V,<space|2em>M=<around*|\<langle\>|\<cal-M\>|\<rangle\>>,<space|2em>\<cal-M\>=<around*|\||<big|sum><rsub|i>\<sigma\><rsub|i>|\|>
  </equation>

  Thanks to the analytical solution of the <math|2d> Ising model, first
  obtained by Onsager, we are able to compare the estimators computed by
  numerical simulations with their exact values obtained analytically.

  The samples and the errors are collected employing the binning procedure of
  the previous section. For each inverse temperature we compute the estimate
  of the generic observable <math|\<cal-O\>> from <math|10<rsup|5>>
  measurements for MH and <math|10<rsup|4>> for SW.

  <big-figure||Energy density as a function of <math|\<beta\>>. MH on the
  left and SW on the right.>

  <big-figure||Magnetization as a function of <math|\<beta\>>. MH on the left
  and SW on the right.>

  We find that the simulation data are remarkably close to the exact solution
  both for the energy density and for the magnetization expecially for large
  sizes of the lattice. The only departure from Onsager's solution is in the
  paramagnetic phase of the magnetization plot: there we observe that the
  exact solution goes abruptly to zero before the critical point, while the
  numerical data seems to interpolate a smooth function. This is imputable to
  the finite size of the lattice used for the simulation. It is indeed a well
  known fact that discontinuities and divergences only appear in the
  thermodinamic limit of infinite size, which is precisely the premise of
  Onsager's solution. In fact, the numerical solution approaches more and
  more the exact one as the size of the lattice increases.

  \;

  We also plot the heat capacity:

  <\equation>
    C=<frac|\<beta\><rsup|2>|V>*<around*|\<langle\>|<around*|(|\<cal-H\>-<around*|\<langle\>|\<cal-H\>|\<rangle\>>|)><rsup|2>|\<rangle\>>
  </equation>

  <big-figure||<label|fig:heatcapacity>Heat capacity as a function of
  <math|\<beta\>>. MH on the left and SW on the right.>

  \ and the magnetic susceptibility:

  <\equation>
    \<chi\>=<frac|\<beta\>|V>*<around*|\<langle\>|<around*|(|\<cal-M\>-<around*|\<langle\>|\<cal-M\>|\<rangle\>>|)><rsup|2>|\<rangle\>>
  </equation>

  <big-figure||<label|fig:susceptibility>Magnetic susceptibility as a
  function of <math|\<beta\>>. MH on the left and SW on the right.>

  As we immediately see from (Fig.<reference|fig:heatcapacity>) and
  (Fig.<reference|fig:susceptibility>) the peak of the curve is progressively
  shifted to the infinite-size limit value <math|\<beta\><rsub|c>> as we
  approach larger and larger sizes of the lattice:

  <\equation>
    lim<rsub|L\<rightarrow\>\<infty\>>\<beta\><rsub|max><around*|(|L|)>=\<beta\><rsub|c>=ln<around*|(|1+<sqrt|2>|)>/2
  </equation>

  <subsection|<math|\<beta\>> Critical><label|sec:betafss>

  From a power law fit of the points near the peak of each dataset we obtain
  estimates for the pseudocritical <math|\<beta\>>-values at finite sizes
  <math|L=8,16,32,64>.

  <\big-figure>
    \;
  </big-figure|Fit of the heat capacity and susceptibility peaks (MH).>

  <big-table|<block|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<math|L>>|<cell|<math|\<beta\><rsub|max><around*|(|C|)>>>|<cell|<math|\<beta\><rsub|max><around*|(|\<chi\>|)>>>>|<row|<cell|<math|8>>|<cell|<math|0.42400\<pm\>0.00043>>|<cell|<math|0.39448\<pm\>0.00051>>>|<row|<cell|<math|16>>|<cell|<math|0.43086\<pm\>0.00086>>|<cell|<math|0.41541\<pm\>0.00055>>>|<row|<cell|<math|32>>|<cell|<math|0.43613\<pm\>0.00103>>|<cell|<math|0.42620\<pm\>0.00141>>>|<row|<cell|<math|64>>|<cell|<math|0.43718\<pm\>0.00065>>|<cell|<math|0.43405\<pm\>0.00075>>>>>>|Pseudocritical
  <math|\<beta\>>-values obtained by polynomial fit of the peaks of <math|C>
  and <math|\<chi\>> (MH).>

  The polynomial function we used for the fit is:

  <\equation>
    f<around*|(|\<beta\>|)>=A+B*<around*|(|\<beta\>-\<beta\><rsub|max>|)><rsup|2>+C*<around*|(|\<beta\>-\<beta\><rsub|max>|)><rsup|3>
  </equation>

  where we omitted the term of order one since it should be zero near the
  maximum of the function.

  <\big-figure>
    \;
  </big-figure|Fit of the heat capacity and susceptibility peaks (SW).>

  <big-table|<block|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<math|L>>|<cell|<math|\<beta\><rsub|max><around*|(|C|)>>>|<cell|<math|\<beta\><rsub|max><around*|(|\<chi\>|)>>>>|<row|<cell|<math|8>>|<cell|<math|0.42296\<pm\>0.00073>>|<cell|<math|0.39295\<pm\>0.00059>>>|<row|<cell|<math|16>>|<cell|<math|0.43174\<pm\>0.00090>>|<cell|<math|0.41729\<pm\>0.00061>>>|<row|<cell|<math|32>>|<cell|<math|0.43524\<pm\>0.00078>>|<cell|<math|0.42686\<pm\>0.00078>>>|<row|<cell|<math|64>>|<cell|<math|0.43788\<pm\>0.00040>>|<cell|<math|0.43481\<pm\>0.00042>>>>>>|Pseudocritical
  <math|\<beta\>>-values obtained by polynomial fit of the peaks of <math|C>
  and <math|\<chi\>> (SW).>

  <with|font-shape|italic|Remark:> the estimates of the heat capacity and
  magnetic susceptibility of the MH algorithm are very accurate for small
  values of <math|L> where we employed a large dataset of <math|10<rsup|5>>
  measurements and the autocorrelation time is relatively small. For large
  values of <math|L> the autocorrelation time grows very large compared to
  the size of the dataset and the estimates become less accurate.

  The situation for the SW algorithm is different since the autocorrelation
  time in this case is always under control. However the smaller size of the
  dataset results in less accurate estimates expecially at small lattice
  sizes where the MH algorithm is most efficient.

  \;

  We can now obtain an estimate of <math|\<beta\><rsub|c>> from a power law
  fit to the location of the maxima <math|\<beta\><rsub|max>>:

  <\equation>
    \<beta\><rsub|max>=\<beta\><rsub|c>-c*L<rsup|-\<nu\>>
  </equation>

  <big-figure||Pseudocritical inverse temperature fit. MH on the left, SW on
  the right. The purple lines are relative to the heat capacity <math|C>
  while the green ones to the magnetic susceptibility <math|\<chi\>>.>

  The result of the fit are:

  \;

  <center|<block*|<tformat|<table|<row|<cell|>|<cell|<math|\<beta\><rsub|c><around*|(|C|)>>>|<cell|<math|\<beta\><rsub|c><around*|(|\<chi\>|)>>>>|<row|<cell|MH>|<cell|<math|0.43986\<pm\>0.00234>>|<cell|<math|0.44287\<pm\>0.00173>>>|<row|<cell|SW>|<cell|<math|0.44007\<pm\>0.00105>>|<cell|<math|0.44071\<pm\>0.00322>>>>>>>

  \;

  \;

  These results are very close to the exact solution but still they could be
  greatly improved by taking more points expecially at larger values of
  <math|L> for which <math|C> and <math|\<chi\>> are more peaked.

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
  magnetizations <math|1, <frac|-1+i*<sqrt|3>|2>, <frac|-1-i*<sqrt|3>|2>>.>

  With this consideration one can construct the probability distribution
  function of the magnetization just by counting the number of samples in
  each level (for <math|L> not too large):

  <\big-figure>
    <image|../potts/histograms/img/8_0.750000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.810000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.830000_SW_histogram.eps|0.33par|||>

    <image|../potts/histograms/img/8_0.850000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.870000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.890000_SW_histogram.eps|0.33par|||>

    <image|../potts/histograms/img/8_0.910000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.930000_SW_histogram.eps|0.33par|||><image|../potts/histograms/img/8_0.950000_SW_histogram.eps|0.33par|||>
  </big-figure|<label|fig:pdfMH>Probability distribution functions of
  <math|m\<in\>\<bbb-C\>> obtained from <math|10<rsup|6>> sweeps of SW on a
  lattice <math|8\<times\>8>.>

  By looking at the PDFs of <math|m> we can witness the formation of a 2-fold
  degeneracy of the ground state of the system for
  <math|\<beta\>\<gtr\>\<beta\><rsub|c>>. Moreover, if we get close to the
  phase transition, we see that the distribution
  <math|P<around*|(|m,\<beta\>|)>> becomes almost flat at <math|m=0> before
  ``splitting'' into the sum of two PDFs for the two degenerate vacua. This
  implies that near <math|\<beta\><rsub|c>> the distribution does not have a
  well defined second cumulant, which is precisely the magnetic
  susceptibility.

  <subsection|Spatial Correlations><label|sec:corr>

  The two-point correlation function is defined as:

  <\equation>
    G <around*|(|<wide|r|\<vect\>><rsub|i>-<wide|r|\<vect\>><rsub|j>|)>=<around*|\<langle\>|\<sigma\><rsub|i>*\<sigma\><rsub|j>|\<rangle\>><space|1em>\<sim\><space|1em>exp<around*|(|-<around*|\||<wide|r|\<vect\>><rsub|i>-<wide|r|\<vect\>><rsub|j>|\|>/\<xi\>|)><space|1em>for
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

  \;

  Since our system is finite and lives on a lattice, the rotational symmetry
  <math|SO<around*|(|2|)>> of <math|\<bbb-R\><rsup|2>> is broken down to the
  discrete subgroup <math|\<bbb-Z\><rsub|4>> of <math|<frac|\<pi\>|2>>
  rotations. We take advantage of this and the translational symmetry of the
  system to compute an improved version of the correlation function
  <math|G<around*|(|<wide|r|\<vect\>>|)>> by defining the observables:

  <\equation>
    S<rsub|x>\<equiv\><frac|1|L>*<big|sum><rsub|y=1><rsup|L>\<sigma\><around*|(|x,y|)>
  </equation>

  <\equation>
    S<rsub|y>\<equiv\><frac|1|L>*<big|sum><rsub|x=1><rsup|L>\<sigma\><around*|(|x,y|)>
  </equation>

  where <math|x> and <math|y> are the two orthogonal directions in the
  lattice.

  \;

  We can compute the correlation function as:

  <\equation>
    G<around*|(|r|)>=<frac|1|2>*<around*|(|<frac|1|L>*<big|sum><rsup|L><rsub|x=1>S<rsub|x>*S<rsub|x+r>+<frac|1|L>*<big|sum><rsup|L><rsub|y=1>S<rsub|y>*S<rsub|y+r>|)>
  </equation>

  Because of the periodic boundary conditions on the lattice we also have
  that:

  <\equation>
    \<sigma\><around*|(|x+a*L,y+b*L|)>=\<sigma\><around*|(|x,y|)><space|2em>\<forall\>
    <around*|(|a,b|)>\<in\>\<bbb-Z\><rsup|2>
  </equation>

  and therefore, the exponential form of <math|G> is modified to that of a
  hyperbolic cosine:

  <\equation>
    <label|eq:cosh>G<around*|(|r|)>\<sim\><frac|1|2>*<around*|(|\<mathe\><rsup|<frac|r|\<xi\>>>+\<mathe\><rsup|<frac|L-r|\<xi\>>>|)>\<sim\>cosh
    <around*|(|<frac|r-<frac|L|2>|\<xi\>>|)>
  </equation>

  In (Fig.<reference|fig:corr>) we can see the exponential decay of the
  correlation function at large distances.\ 

  <big-figure||<label|fig:corr>Correlation functions for various values of
  <math|\<beta\>>. The lattice size used is <math|128\<times\>128> in order
  to reduce finite-size effects. As a precaution, we considers an interval in
  <math|\<beta\>>-space such that the correlation length is much smaller that
  the size of the lattice (approximately one order of magnitude smaller). >

  The correlation length diverges at the critical point as:

  <\equation>
    \<xi\>\<sim\>A*<around*|\||x|\|><rsup|-\<nu\>>
  </equation>

  where <math|\<nu\>> is an example of critical exponent of the model. We
  plot the data obained from the previous fit using logarithmic scales on
  both axis. This way we can easily obtain the critical exponent
  <math|\<nu\>> from a linear fit:

  <\equation>
    log<around*|(|\<xi\>|)>=log<around*|(|A|)>-\<nu\>*log<around*|(|<around*|\||x|\|>|)>
  </equation>

  <big-figure||Plot of the correlation length dependence on the parameter
  <math|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>> for a lattice of
  size <math|128\<times\>128>. MH on the left and SW on the right. The errors
  are computed by jackknife binning of the fit data from
  (Fig.<reference|fig:corr>) through (<reference|eq:cosh>).>

  The results are:

  <\equation>
    \<nu\><rsub|MH>=1.017\<pm\>0.029
  </equation>

  <\equation>
    \<nu\><rsub|SW>=1.045\<pm\>0.014
  </equation>

  Both results are compatible with the known exact value <math|\<nu\>=1>.

  <subsection|Finite Size Scaling><label|sect:fss>

  The main results of the finite size scaling (FSS) study are usually
  estimates of the critical temperature and the critical exponents
  characterizing the universality class of the transition. In the
  infinite-volume limit most of the expectation values one can compute from
  <math|e> and <math|m> exhibit singularities at the transition point. In
  finite systems, though, the singularities are smeared out and the standard
  observables scale according to:

  <\equation>
    m=L<rsup|-\<beta\>/\<nu\>>*f<rsub|m> <around*|(|y|)>+\<ldots\>
  </equation>

  <\equation>
    C=C<rsub|reg>+L<rsup|\<alpha\>/\<nu\>>f<rsub|C> <around*|(|y|)>+\<ldots\>
  </equation>

  <\equation>
    \<chi\>=L<rsup|\<gamma\>/\<nu\>>*f<rsub|\<chi\>><around*|(|y|)>+\<ldots\>
  </equation>

  where <math|\<alpha\>,\<beta\>,\<gamma\>> and <math|\<nu\>> are the
  critical exponents, <math|f<rsub|i>(x)> are FSS functions and <math|y> is
  the scaling variable. Near the phase transition the correlation length
  <math|\<xi\>\<sim\>x<rsup|-\<nu\>>> is the only length scale with which to
  describe the physics of the system, therefore the only adimensional
  quantity we can contruct from it is:

  <\equation>
    y=L/\<xi\>\<sim\>L*x<rsup|\<nu\>>=<around*|(|L<rsup|1/\<nu\>>*x|)><rsup|\<nu\>>=L*x
  </equation>

  We now can remove any dependence on the scale of the system by rescaling
  the observables by the appropriate power of <math|L> given by the relative
  critical exponent. This way we expect each observable, expressed as
  functions of the scaling variable <math|y>, to collapses on the same curve
  <math|f<rsub|i> <around*|(|y|)>> regardless of the value of <math|L> (at
  least in the vicinity of <math|\<beta\><rsub|c>>).

  <big-table|<block|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<math|\<nu\>>>|<cell|<math|1>>>|<row|<cell|<math|\<alpha\>>>|<cell|<math|0>>>|<row|<cell|<math|\<beta\>>>|<cell|<math|1/8>>>|<row|<cell|<math|\<gamma\>>>|<cell|<math|7/4>>>>>>|Exact
  critical exponents for the Ising model in <math|2d>.>

  With a precedure completely analogous to that of
  (Sect.<reference|sec:betafss>), one could also obtain estimates for the
  crtical exponents <math|\<alpha\>,\<beta\>,\<gamma\>> and <math|\<nu\>> by
  extrapolating the infinite size limit.

  \;

  <with|font-shape|italic|Remark:> we observe that since the exact value of
  exponent <math|\<alpha\>> of the model is zero, the quantity <math|C>
  should, in principle, not scale with the lattice size. In reality <math|C>
  has a logarithmic divergence at the critical point, hence we adopt the
  scaling law:

  <\equation>
    C\<sim\>log <around*|(|L<rsup|1/\<nu\>>|)>
  </equation>

  <\big-figure>
    \;
  </big-figure|Finite Size Scaling study for the lattice sizes
  <math|8<rsup|2>,16<rsup|2>,32<rsup|2>,64<rsup|2>>. Left MH, right SW. The
  top plot represents the scaling of the magnetization, the center one the
  magnetic susceptibility and the bottom one the heat capacity.>
</body>

<\initial>
  <\collection>
    <associate|page-even-footer|>
    <associate|page-even-header|>
    <associate|page-medium|papyrus>
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
    <associate|auto-10|<tuple|6|5>>
    <associate|auto-11|<tuple|7|5>>
    <associate|auto-12|<tuple|1.4|5>>
    <associate|auto-13|<tuple|8|5>>
    <associate|auto-14|<tuple|1|5>>
    <associate|auto-15|<tuple|9|5>>
    <associate|auto-16|<tuple|2|5>>
    <associate|auto-17|<tuple|10|6>>
    <associate|auto-18|<tuple|1.5|6>>
    <associate|auto-19|<tuple|11|6>>
    <associate|auto-2|<tuple|1.1|2>>
    <associate|auto-20|<tuple|12|7>>
    <associate|auto-21|<tuple|1.6|7>>
    <associate|auto-22|<tuple|13|8>>
    <associate|auto-23|<tuple|14|8>>
    <associate|auto-24|<tuple|15|9>>
    <associate|auto-25|<tuple|1.7|9>>
    <associate|auto-26|<tuple|3|9>>
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
    <associate|auto-4|<tuple|1.2|3>>
    <associate|auto-5|<tuple|2|3>>
    <associate|auto-6|<tuple|3|4>>
    <associate|auto-7|<tuple|1.3|4>>
    <associate|auto-8|<tuple|4|4>>
    <associate|auto-9|<tuple|5|4>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:cosh|<tuple|22|9>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:corr|<tuple|14|9>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:heatcapacity|<tuple|6|5>>
    <associate|fig:levels|<tuple|11|6>>
    <associate|fig:pdfMH|<tuple|12|7>>
    <associate|fig:pdfSW|<tuple|13|7>>
    <associate|fig:susceptibility|<tuple|7|5>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:thermalization|<tuple|1|2>>
    <associate|fig:thermalizationMH|<tuple|2|3>>
    <associate|fig:thermalizationSW|<tuple|3|4>>
    <associate|fig:toruseffect|<tuple|1|3>>
    <associate|footnote-1|<tuple|1|?>>
    <associate|footnr-1|<tuple|1|?>>
    <associate|result_box|<tuple|5|?>>
    <associate|sec:betafss|<tuple|1.4|5>>
    <associate|sec:corr|<tuple|1.6|8>>
    <associate|sect:autocorrelation|<tuple|1.2|3>>
    <associate|sect:fss|<tuple|1.7|9>>
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
        function <with|mode|<quote|math>|k<rsub|max>>. The chromatic key
        indicates the value of <with|mode|<quote|math>|\<beta\>>. On the left
        is shown the plot of <with|mode|<quote|math>|\<tau\><rsub|int>> as a
        function of <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>.
        The lattice size is <with|mode|<quote|math>|L=8>.
      </tuple|<pageref|auto-5>>

      <tuple|normal|3d plot of <with|mode|<quote|math>|\<tau\><rsub|int><around*|(|\<beta\>,k<rsub|max>|)>>
      for a Potts Model of volume <with|mode|<quote|math>|8\<times\>8> near
      <with|mode|<quote|math>|\<beta\><rsub|c>>.|<pageref|auto-6>>

      <tuple|normal|Energy density as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-8>>

      <tuple|normal|Magnetization as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-9>>

      <tuple|normal|Heat capacity as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-10>>

      <tuple|normal|Magnetic susceptibility as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-11>>

      <tuple|normal|Fit of the heat capacity and susceptibility peaks
      (MH).|<pageref|auto-13>>

      <tuple|normal|Fit of the heat capacity and susceptibility peaks
      (SW).|<pageref|auto-15>>

      <tuple|normal|Pseudocritical inverse temperature fit. MH on the left,
      SW on the right. The purple lines are relative to the heat capacity
      <with|mode|<quote|math>|C> while the green ones to the magnetic
      susceptibility <with|mode|<quote|math>|\<chi\>>.|<pageref|auto-17>>

      <tuple|normal|Magnetization levels of the Potts Model on a
      <with|mode|<quote|math>|4\<times\>4> lattice. We remark that, since the
      average is a convex function of its arguements, every magnetization
      level must be contained in the convex hull of the three basic
      magnetizations <with|mode|<quote|math>|1, <frac|-1+i*<sqrt|3>|2>,
      <frac|-1-i*<sqrt|3>|2>>.|<pageref|auto-19>>

      <tuple|normal|Probability distribution functions of
      <with|mode|<quote|math>|m\<in\>\<bbb-C\>> obtained from
      <with|mode|<quote|math>|10<rsup|6>> sweeps of SW on a lattice
      <with|mode|<quote|math>|8\<times\>8>.|<pageref|auto-20>>

      <tuple|normal|Probability distribution functions of
      <with|mode|<quote|math>|m> obtained from
      <with|mode|<quote|math>|10<rsup|6>> sweeps of SW on a lattice
      <with|mode|<quote|math>|8\<times\>8>.|<pageref|auto-21>>

      <tuple|normal|Ilustration of the growth of spatial correlations when
      criticality is approached on a lattice
      <with|mode|<quote|math>|128\<times\>128> :
      <with|mode|<quote|math>|\<beta\>=0.2, 0.5, 0.7,0.8, 0.9, 0.95, 0.97,
      0.98, 0.99>.|<pageref|auto-23>>

      <tuple|normal|Correlation functions for various values of
      <with|mode|<quote|math>|\<beta\>>. The lattice size used is
      <with|mode|<quote|math>|128\<times\>128> in order to reduce finite-size
      effects. As a precaution, we considers an interval in
      <with|mode|<quote|math>|\<beta\>>-space such that the correlation
      length is much smaller that the size of the lattice (approximately one
      order of magnitude smaller). |<pageref|auto-24>>

      <tuple|normal|Plot of the correlation length dependence on the
      parameter <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>
      for a lattice of size <with|mode|<quote|math>|128\<times\>128>. MH on
      the left and SW on the right. The errors are computed by jackknife
      binning of the fit data from (Fig.<reference|fig:corr>) through
      (<reference|eq:cosh>).|<pageref|auto-25>>

      <tuple|normal|Finite Size Scaling study for the lattice sizes
      <with|mode|<quote|math>|8<rsup|2>,16<rsup|2>,32<rsup|2>,64<rsup|2>>.
      Left MH, right SW. The top plot represents the scaling of the
      magnetization, the center one the magnetic susceptibility and the
      bottom one the heat capacity.|<pageref|auto-28>>
    </associate>
    <\associate|table>
      <tuple|normal|Pseudocritical <with|mode|<quote|math>|\<beta\>>-values
      obtained by polynomial fit of the peaks of <with|mode|<quote|math>|C>
      and <with|mode|<quote|math>|\<chi\>> (MH).|<pageref|auto-14>>

      <tuple|normal|Pseudocritical <with|mode|<quote|math>|\<beta\>>-values
      obtained by polynomial fit of the peaks of <with|mode|<quote|math>|C>
      and <with|mode|<quote|math>|\<chi\>> (SW).|<pageref|auto-16>>

      <tuple|normal|Exact critical exponents for the Ising model in
      <with|mode|<quote|math>|2d>.|<pageref|auto-27>>
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
      <no-break><pageref|auto-12>>

      <with|par-left|<quote|1tab>|1.5<space|2spc>Probability Distribution
      Functions <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-18>>

      <with|par-left|<quote|1tab>|1.6<space|2spc>Spatial Correlations
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-22>>

      <with|par-left|<quote|1tab>|1.7<space|2spc>Finite Size Scaling
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-26>>
    </associate>
  </collection>
</auxiliary>