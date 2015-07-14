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
    <vspace*|1fn><with|font-series|bold|math-font-series|bold|1<space|2spc>Ising
    Model <with|mode|math|2d>> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-2>>

    <with|par-left|1tab|1.2<space|2spc>Autocorrelation Times
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-6>>

    <with|par-left|1tab|1.3<space|2spc>Binning Analysis
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-11>>

    <with|par-left|1tab|1.4<space|2spc>Observables
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-14>>

    <with|par-left|1tab|1.5<space|2spc><with|mode|math|\<beta\>> Critical
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-19>>

    <with|par-left|1tab|1.6<space|2spc>Probability Distribution Functions
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-25>>

    <with|par-left|1tab|1.7<space|2spc>Spatial Correlations
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-29>>

    <with|par-left|1tab|1.8<space|2spc>Finite Size Scaling
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-33>>
  </table-of-contents>

  <section|Ising Model <math|2d>>

  In this section we study the statistical properties of a <math|2d> Ising
  Model. We consider a system of <math|L\<times\>L> spins situated on the
  points of a regular square lattice with periodic boundary conditions (PBC)
  in both directions. Each spin interacts with its nearest neighbours inside
  the lattice, with an Hamiltonian:

  <\equation>
    H=-<big|sum><rsub|<around*|\<langle\>|i,j|\<rangle\>>>\<sigma\><rsub|i>*\<sigma\><rsub|j>
  </equation>

  where the sum is taken only over the set of unordered pairs
  <math|<around*|\<langle\>|i,j|\<rangle\>>> such that
  <math|\<sigma\><rsub|i>> and <math|\<sigma\><rsub|j>> are nearest
  neighbours.

  In order to obtain expectation values for physical quantities of the system
  we should be able to sum over the space of all the spin configurations, or
  at least to sample configurations from this space with probability:

  <\equation>
    P<around*|(|<around*|{|\<sigma\>|}>|)>\<sim\>\<mathe\><rsup|-\<beta\>*H<around*|(|<around*|{|\<sigma\>|}>|)>>
  </equation>

  which reproduces the integration measure of the functional integral. The
  obvious choice for numerical simulations is the second one, which we
  implement through Monte Carlo (MC) algorithms. In particular we focus on
  the Metropolis-Hastings (MH) and the Swendsen-Wang (SW) algorithms.

  <subsection|Thermalization>

  Since we do not know where to start in our Markov process, we first
  initialize the system in a disordered configuration (hot start) and then
  evolve for a certain Markov time until the system reaches equilibrium. This
  process is usually called <with|font-shape|italic|thermalization>.

  After a few run we decided to opt for a cold start approach (i.e., all the
  spins are initially aligned). The reason for this choice is that, when
  using MH in <math|2>-dimensional finite-size systems with periodic boundary
  conditions, the non trivial topology of the lattice allows the existence of
  stable configurations of the type depicted in
  (Fig.<reference|fig:toruseffect>), that often arise when the system is
  rapidly cooled from a disordered configuration. Those configurations would
  invalidate the mixing process and the sampling of relevant configurations
  at low temperatures. Therefore, by using a cold start, we exclude this
  possibility.

  <big-figure|<image|../ising/ising_128x128_0.610000.ppm|0.35par|||><space|2em><image|../ising/ising_128x128_0.690000.ppm|0.35par|||>|<label|fig:toruseffect>Illustration
  of two topologically non-trivial configurations obtained with the MH
  algorithm on a lattice <math|128\<times\>128>.>

  We expect the MH algorithm to be slower to thermalize because of the local
  update it employes as opposed to the cluster update of the SW algorithm.

  <\big-figure>
    <image|../ising/thermalization/img/MH_thermalization_e_0.300000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_e_0.400000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_e_0.440687.eps|0.33par|||>

    <image|../ising/thermalization/img/MH_thermalization_m_0.300000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_m_0.400000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_m_0.440687.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationMH>Plot of the energy density and
  magnetization for the MH markov process at different values of
  <math|\<beta\>>.>

  <\big-figure>
    <image|../ising/thermalization/img/SW_thermalization_e_0.300000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_e_0.400000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_e_0.440687.eps|0.33par|||>

    <image|../ising/thermalization/img/SW_thermalization_m_0.300000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_m_0.400000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_m_0.440687.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationSW>Plot of the energy density and
  magnetization for the SW markov process at different values of
  <math|\<beta\>>.>

  The MH algorithm reaches thermalization very rapidly for inverse
  temperatures <math|\<beta\>> far from the critical value
  <math|\<beta\><rsub|c>>, while for values of <math|\<beta\>> near the phase
  transition it becomes much slower (Fig.<reference|fig:thermalizationMH>).\ 

  This effect is called <with|font-shape|italic|critical slowing down> and it
  tells us that, when using local update algorithms, successive steps in the
  Markov chain are strongly correlated and therefore only approximately every
  <math|L<rsup|2>> sweeps through the lattice, a statistically independent
  measurement can be taken. Close to a critical point, in fact, the
  autocorrelation time (in the infinite-volume limit) typically scales as:

  <\equation>
    <label|eq:scalingtau>\<tau\><rsub|\<cal-O\>,exp>\<propto\>\<xi\><rsup|z>
  </equation>

  where <math|z \<geq\> 0> is the so-called dynamical critical exponent. The
  spatial correlation length <math|\<xi\>> would diverge at the critical
  point, but in a finite system it is limited by the size <math|L> of the
  system and the scaling law (<reference|eq:scalingtau>) becomes:

  <\equation>
    \<tau\><rsub|\<cal-O\>,exp>\<propto\>L<rsup|z>
  </equation>

  where <math|z\<approx\>2> for local dynamics (MH) and <math|z\<approx\>0>
  for SW.

  We also remark that for smaller values of <math|\<beta\>>, the energy of
  the system can have larger fluctuations around its average and therfore
  thermal equilibrium is reached faster.

  \;

  On the other hand the SW algorithm mixes very fast even at the phase
  transition (Fig.<reference|fig:thermalizationSW>) being a multicluster
  update algorithm (Fig.<reference|fig:thermalizationSW>).

  \;

  For the rest of the simulations we considered the system to be at
  equilibrium after a thermalization time <math|t\<approx\>1000<rsup|>> both
  for MH and for SW.

  <subsection|<label|sect:autocorrelation>Autocorrelation Times>

  We now study the correlations present between consecutive configurations
  sampled by the two algorithms in order to obtain the characteristic time
  after which we can consider two configurations to be statistically
  independent. This is called <with|font-shape|italic|integrated
  autocorrelation time> and is computed in the following way:

  <\equation>
    <label|eq:tint>\<tau\><rsub|\<cal-O\>,int>=<frac|1|2>+<big|sum><rsub|k=1><rsup|k<rsub|max>>R
    <around*|(|k|)>
  </equation>

  where <math|\<cal-O\>> is the physical observable for which we compute
  autocorrelation and <math|R<around*|(|k|)>> is defined as:

  <\equation>
    R <around*|(|k|)> = <frac|1|<around*|(|n-k|)>*\<sigma\><rsup|2>>*<big|sum><rsup|n-k><rsub|t=1><around*|(|\<cal-O\><rsub|t>-\<mu\>|)>*<around*|(|\<cal-O\><rsub|t+k>-\<mu\>|)>
  </equation>

  here <math|n> is the total number of samples of <math|\<cal-O\>> and
  <math|\<mu\>,\<sigma\><rsup|2>> are the mean and variance of the process.
  For large time separations <math|k>, <math|R(k)> decays exponentially:

  <\equation>
    R<around*|(|k|)><long-arrow|\<rubber-rightarrow\>|k\<rightarrow\>\<infty\>>r\<mathe\><rsup|-k/\<tau\><rsub|\<cal-O\>,exp>>
  </equation>

  which defines the exponential autocorrelation time
  <math|\<tau\><rsub|\<cal-O\>,exp>>.

  \;

  We immediately see from (Fig.<reference|fig:autocorrelation1>) that the MC
  process is strongly correlated in time particularly near the phase
  transition:

  <big-figure|<image|../ising/thermalization/img/MH_energy.eps|0.5par|||><image|../ising/thermalization/img/SW_energy.eps|0.5par|||>|<label|fig:autocorrelation1>Comparison
  of the energy for the two algorithms at <math|\<beta\>=\<beta\><rsub|c>>
  and <math|L=32>. (Left) MH (Right) SW.>

  We now compute the autocorrelation time <math|\<tau\><rsub|int>> for the
  observable <math|e=E/V> using formula (<reference|eq:tint>):

  <\big-figure>
    <image|../ising/autocorrelation/img/32_0.410000_MH.eps|0.33par|||><image|../ising/autocorrelation/img/32_0.430000_MH.eps|0.33par|||><image|../ising/autocorrelation/img/32_0.450000_MH.eps|0.33par|||>
  </big-figure|Plot of the integrated autocorrelation time near the phase
  transition for the MH algorithm. The raw data was obtained from a
  simulation of <math|10<rsup|6>> measurements on a lattice
  <math|32\<times\>32>. The fit in the center is not very accurate because
  near <math|\<beta\><rsub|c>> the autocorrelation time becomes very large
  and the interval <math|<around*|[|0,2000|]>> becomes too small for a
  reliable estimate of <math|\<tau\><rsub|int>>.>

  <\big-figure>
    <image|../ising/autocorrelation/img/32_0.410000_SW.eps|0.33par|||><image|../ising/autocorrelation/img/32_0.430000_SW.eps|0.33par|||><image|../ising/autocorrelation/img/32_0.450000_SW.eps|0.33par|||>
  </big-figure|Plot of the integrated autocorrelation time near the phase
  transition for the SW algorithm. The raw data was obtained from a
  simulation of <math|10<rsup|5>> measurements on a lattice
  <math|32\<times\>32>.>

  The data is fitted using the function:

  <\equation>
    \<tau\><rsub|int><around*|(|k<rsub|max>|)>=\<tau\><rsub|int><around*|[|1-<frac|2*\<tau\><rsub|exp>|2*\<tau\><rsub|exp>+1>*\<mathe\><rsup|-k<rsub|max>/\<tau\><rsub|exp>>|]>
  </equation>

  which is the exact solution for a bivariate gaussian process.

  \;

  As we can see, near the phase transition the autocorrelation time for the
  MH process becomes very large compared to the autocorrelation time of the
  SW process (Fig.<reference|fig:autocorrelation_time>). In fact due to the
  critical slowing down of the MH algorithm, we have
  <math|\<tau\><rsub|int><rsup|MH>\<sim\>100> compared to an autocorrelation
  time <math|\<tau\><rsub|int><rsup|SW>\<sim\>5> for SW.

  <big-figure|<image|../ising/autocorrelation/img/autocorrelation_time.eps|0.5par|||>|<label|fig:autocorrelation_time>Plot
  of the integrated autocorrelation time as a function of
  <math|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>> for
  <math|L=32>.>

  We remark that the peak is slightly off centered because of the finite size
  of the lattice (pseudocritical point <math|\<beta\><rsub|c><around*|(|V|)>\<less\>\<beta\><rsub|c><around*|(|\<infty\>|)>>).

  <subsection|Binning Analysis>

  In order to have a statistical ensamble of uncorrelated data we need to
  address the issue of autocorrelation in the Markov process. An easy and
  efficient way to do so is to split the data in non-overlapping blocks of
  the same size and then average over each block to obtain
  (almost)uncorrelated data for the observable <math|\<cal-O\>> of interest.
  The blocks are also called <with|font-shape|italic|bins> and this method is
  called binning.

  \;

  Consider an ensamble of <math|N=N<rsub|B>\<cdot\>k> samples divided in
  <math|N<rsub|B>> blocks of size <math|k>. For each block <math|n> we take
  the average of the observables <math|\<cal-O\><rsub|i>> it contains and
  then obtain a block-observable <math|\<cal-O\><rsub|B,n>>:

  <\equation>
    \<cal-O\><rsub|B,n>=<frac|1|k>*<big|sum><rsup|k-1><rsub|i=0>\<cal-O\><rsub|n*k+i><space|2em>n=0,\<ldots\>
    ,N<rsub|B>-1
  </equation>

  From a simple calculation we obtain that the error estimate on the mean
  value is:

  <\equation>
    \<epsilon\><rsup|2><rsub|<wide|\<cal-O\>|\<bar\>>>\<equiv\>\<sigma\><rsup|2><rsub|<wide|\<cal-O\>|\<bar\>>>=<frac|\<sigma\><rsup|2><rsub|B>|N<rsub|B>>=2*\<tau\><rsub|\<cal-O\>,int>*<frac|\<sigma\><rsup|2><rsub|\<cal-O\><rsub|i>>|N>
  </equation>

  hence:

  <\equation>
    2*\<tau\><rsub|\<cal-O\>,int>=k*\<sigma\><rsup|2><rsub|B>/\<sigma\><rsup|2><rsub|\<cal-O\><rsub|i>>
  </equation>

  We study the dependence of the variance <math|\<sigma\><rsup|2><rsub|B>> on
  the block size <math|k>. The observable we consider is the energy density
  <math|e>.

  <\big-figure>
    <image|../ising/binning/img/binning_MH_0.35.eps|0.5par|||><image|../ising/binning/img/binning_MH_0.40.eps|0.5par|||>

    <image|../ising/binning/img/binning_MH_0.43.eps|0.5par|||><image|../ising/binning/img/binning_MH_0.44.eps|0.5par|||>

    <image|../ising/binning/img/binning_MH_0.45.eps|0.5par|||><image|../ising/binning/img/binning_MH_0.50.eps|0.5par|||>
  </big-figure|Binning analysis for the MH algorithm at various values of
  <math|\<beta\>> (<math|L=32>).>

  <\big-figure>
    <image|../ising/binning/img/binning_SW_0.35.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.40.eps|0.5par|||>

    <image|../ising/binning/img/binning_SW_0.43.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.44.eps|0.5par|||>

    <image|../ising/binning/img/binning_SW_0.45.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.50.eps|0.5par|||>
  </big-figure|Binning analysis for the SW algorithm at various values of
  <math|\<beta\>> (<math|L=32>).>

  Where we fitted the data using the formula:

  <\equation>
    k*\<sigma\><rsup|2><rsub|B>\<approx\>
    2*\<tau\><rsub|exp>*<around*|(|1-<frac|\<tau\><rsub|exp>|k>*<around*|(|1-\<mathe\><rsup|-k/\<tau\><rsub|exp>>|)>|)>
  </equation>

  The lowest value of <math|k> for which we can consider the binned data to
  be uncorrelated is obtained by looking at the point for which the signal
  for <math|k*\<sigma\><rsup|2><rsub|B>/\<sigma\><rsup|2><rsub|\<cal-O\><rsub|i>>>
  stabilizes and its first derivarive tends to zero. We call this point
  <math|k<rsup|\<ast\>><around*|(|\<beta\>|)>>. Since
  <math|\<tau\><rsub|exp>> has a local maximum at the critical point, we take
  <math|k<rsup|\<ast\>><around*|(|\<beta\><rsub|c>|)>> as the block size for
  the following simulations.

  \;

  With the block sizes set to:

  <\eqnarray>
    <tformat|<table|<row|<cell|k<rsup|\<ast\>><rsub|MH>>|<cell|=>|<cell|1000>>|<row|<cell|k<rsup|\<ast\>><rsub|SW>>|<cell|=>|<cell|50>>>>
  </eqnarray>

  we should now able to sample data without having to worry about
  autocorrelation in the signal.

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

  <big-figure|<image|../ising/observables/img/energy_MH.eps|0.5par|||><image|../ising/observables/img/energy_SW.eps|0.5par|||>|Energy
  density as a function of <math|\<beta\>>. MH on the left and SW on the
  right.>

  <big-figure|<image|../ising/observables/img/magnetization_MH.eps|0.5par|||><image|../ising/observables/img/magnetization_SW.eps|0.5par|||>|Magnetization
  as a function of <math|\<beta\>>. MH on the left and SW on the right.>

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

  <big-figure|<image|../ising/observables/img/heat_capacity_MH.eps|0.5par|||><image|../ising/observables/img/heat_capacity_SW.eps|0.5par|||>|<label|fig:heatcapacity>Heat
  capacity as a function of <math|\<beta\>>. MH on the left and SW on the
  right.>

  \ and the magnetic susceptibility:

  <\equation>
    \<chi\>=<frac|\<beta\>|V>*<around*|\<langle\>|<around*|(|\<cal-M\>-<around*|\<langle\>|\<cal-M\>|\<rangle\>>|)><rsup|2>|\<rangle\>>
  </equation>

  <big-figure|<image|../ising/observables/img/susceptibility_MH.eps|0.5par|||><image|../ising/observables/img/susceptibility_SW.eps|0.5par|||>|<label|fig:susceptibility>Magnetic
  susceptibility as a function of <math|\<beta\>>. MH on the left and SW on
  the right.>

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
    <image|../ising/observables/img/8MH1.eps|0.5par|||><image|../ising/observables/img/8MH2.eps|0.5par|||>

    <image|../ising/observables/img/16MH1.eps|0.5par|||><image|../ising/observables/img/16MH2.eps|0.5par|||>

    <image|../ising/observables/img/32MH1.eps|0.5par|||><image|../ising/observables/img/32MH2.eps|0.5par|||>

    <image|../ising/observables/img/64MH1.eps|0.5par|||><image|../ising/observables/img/64MH2.eps|0.5par|||>
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
    <image|../ising/observables/img/8SW1.eps|0.5par|||><image|../ising/observables/img/8SW2.eps|0.5par|||>

    <image|../ising/observables/img/16SW1.eps|0.5par|||><image|../ising/observables/img/16SW2.eps|0.5par|||>

    <image|../ising/observables/img/32SW1.eps|0.5par|||><image|../ising/observables/img/32SW2.eps|0.5par|||>

    <image|../ising/observables/img/64SW1.eps|0.5par|||><image|../ising/observables/img/64SW2.eps|0.5par|||>
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

  <big-figure|<image|../ising/fss/img/beta_MH.eps|0.5par|||><image|../ising/fss/img/beta_SW.eps|0.5par|||>|Pseudocritical
  inverse temperature fit. MH on the left, SW on the right. The purple lines
  are relative to the heat capacity <math|C> while the green ones to the
  magnetic susceptibility <math|\<chi\>>.>

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
  are quantized. In particular, for an Ising model on a square lattice of
  size <math|L<rsup|2>> with PBC, there are exactly <math|L<rsup|2>+1>
  magnetization levels equidistributed in the interval
  <math|<around*|[|-1,+1|]>>.

  With this consideration one can construct the probability distribution
  function of the magnetization just by counting the number of samples in
  each level (for <math|L> not too large). In (Fig.<reference|fig:pdfMH>) and
  (Fig.<reference|fig:pdfSW>) we show the PDFs of <math|m> for both of the
  algorithms and for various values of <math|\<beta\>>:

  <\big-figure>
    <image|../ising/histograms/img/8_0.340000_MH_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.350000_MH_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.360000_MH_histogram.eps|0.33par|||>

    <image|../ising/histograms/img/8_0.370000_MH_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.380000_MH_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.390000_MH_histogram.eps|0.33par|||>
  </big-figure|<label|fig:pdfMH>Probability distribution functions of
  <math|m> obtained from <math|10<rsup|6>> sweeps of MH on a lattice
  <math|8\<times\>8>.>

  By looking at the PDFs of <math|m> we can witness the formation of a 2-fold
  degeneracy of the ground state of the system for
  <math|\<beta\>\<gtr\>\<beta\><rsub|c>>. Moreover, if we get close to the
  phase transition, we see that the distribution
  <math|P<around*|(|m,\<beta\>|)>> becomes almost flat at <math|m=0> before
  ``splitting'' into the sum of two PDFs for the two degenerate vacua. This
  implies that near <math|\<beta\><rsub|c>> the distribution does not have a
  well defined second cumulant, which is precisely the magnetic
  susceptibility.

  <\big-figure>
    <image|../ising/histograms/img/8_0.340000_SW_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.350000_SW_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.360000_SW_histogram.eps|0.33par|||>

    <image|../ising/histograms/img/8_0.370000_SW_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.380000_SW_histogram.eps|0.33par|||><image|../ising/histograms/img/8_0.390000_SW_histogram.eps|0.33par|||>
  </big-figure|<label|fig:pdfSW>Probability distribution functions of
  <math|m> obtained from <math|10<rsup|6>> sweeps of SW on a lattice
  <math|8\<times\>8>.>

  Since we used a cold start initialization, all our simulations of MH at
  temperatures lower than <math|T<rsub|c>> spontaneously broke the
  <math|\<bbb-Z\><rsub|2>> symmetry of the ground state to some value
  <math|m<rsub|0>\<gtr\>0>. Having used a hot start initialization instead,
  we would have ended up with <math|m<rsub|0>=\<pm\><around*|\||m<rsub|0>|\|>>
  with probability <math|<frac|1|2>> each. For the SW algorithm this is not
  an issue since it can easily tunnel between ground states by flipping large
  numbers of spins in a single sweep. In both cases, though, we measured the
  unsigned magnetization thus obtaining only histograms for the range
  <math|<around*|[|0,1|]>>. In (Fig.<reference|fig:pdfMH>) and
  (Fid.<reference|fig:pdfSW>) we computed the histograms for the negative
  range by assuming the <math|\<bbb-Z\><rsub|2>> symmetry:

  <\equation>
    P<around*|(|-m|)>=P<around*|(|m|)>
  </equation>

  <big-figure|<image|../ising/histograms/img/8_MH_histogram3d.eps||||>|3d
  plot of <math|P<around*|(|m,\<beta\>|)>> as computed from <math|10<rsup|6>>
  measurements of <math|m> obtained on a <math|8\<times\>8> lattice with the
  MH algorithm.>

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
    <image|../ising/ising_100x100_0.220000.ppm|0.35par|||><space|2em><image|../ising/ising_100x100_0.310000.ppm|0.35par|||>

    \;

    <image|../ising/ising_100x100_0.370000.ppm|0.35par|||><space|2em><image|../ising/ising_100x100_0.390000.ppm|0.35par|||>

    \;

    <image|../ising/ising_100x100_0.410000.ppm|0.35par|||><space|2em><image|../ising/ising_100x100_0.430000.ppm|0.35par|||>
  <|big-figure>
    Ilustration of the growth of spatial correlations when criticality is
    approached on a lattice <math|100\<times\>100> : <math|\<beta\>=0.22 ,
    0.31, 0.37, 0.39, 0.42, 0.43>.
  </big-figure>

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

  <big-figure|<image|../ising/correlation/img/green_MH.eps|0.5par|||><image|../ising/correlation/img/green_SW.eps|0.5par|||>|<label|fig:corr>Correlation
  functions for various values of <math|\<beta\>>. The lattice size used is
  <math|128\<times\>128> in order to reduce finite-size effects. As a
  precaution, we considers an interval in <math|\<beta\>>-space such that the
  correlation length is much smaller that the size of the lattice
  (approximately one order of magnitude smaller). >

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

  <big-figure|<image|../ising/correlation/img/correlation_MH.eps|0.5par|||><image|../ising/correlation/img/correlation_SW.eps|0.5par|||>|Plot
  of the correlation length dependence on the parameter
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
    <image|../ising/fss/img/magnetization_MH.eps|0.5par|||><image|../ising/fss/img/magnetization_SW.eps|0.5par|||>

    <image|../ising/fss/img/susceptibility_MH.eps|0.5par|||><image|../ising/fss/img/susceptibility_SW.eps|0.5par|||>

    <image|../ising/fss/img/heat_capacity_MH.eps|0.5par|||><image|../ising/fss/img/heat_capacity_SW.eps|0.5par|||>
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
    <associate|auto-10|<tuple|7|6>>
    <associate|auto-11|<tuple|1.3|6>>
    <associate|auto-12|<tuple|8|7>>
    <associate|auto-13|<tuple|9|8>>
    <associate|auto-14|<tuple|1.4|9>>
    <associate|auto-15|<tuple|10|10>>
    <associate|auto-16|<tuple|11|10>>
    <associate|auto-17|<tuple|12|11>>
    <associate|auto-18|<tuple|13|11>>
    <associate|auto-19|<tuple|1.5|11>>
    <associate|auto-2|<tuple|1.1|1>>
    <associate|auto-20|<tuple|14|12>>
    <associate|auto-21|<tuple|1|13>>
    <associate|auto-22|<tuple|15|14>>
    <associate|auto-23|<tuple|2|15>>
    <associate|auto-24|<tuple|16|15>>
    <associate|auto-25|<tuple|1.6|16>>
    <associate|auto-26|<tuple|17|16>>
    <associate|auto-27|<tuple|18|17>>
    <associate|auto-28|<tuple|19|18>>
    <associate|auto-29|<tuple|1.7|19>>
    <associate|auto-3|<tuple|1|2>>
    <associate|auto-30|<tuple|20|19>>
    <associate|auto-31|<tuple|21|20>>
    <associate|auto-32|<tuple|22|21>>
    <associate|auto-33|<tuple|1.8|22>>
    <associate|auto-34|<tuple|3|22>>
    <associate|auto-35|<tuple|23|23>>
    <associate|auto-36|<tuple|23|?>>
    <associate|auto-4|<tuple|2|2>>
    <associate|auto-5|<tuple|3|3>>
    <associate|auto-6|<tuple|1.2|4>>
    <associate|auto-7|<tuple|4|4>>
    <associate|auto-8|<tuple|5|5>>
    <associate|auto-9|<tuple|6|5>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:cosh|<tuple|27|20>>
    <associate|eq:scalingtau|<tuple|3|3>>
    <associate|eq:tint|<tuple|5|4>>
    <associate|fig:autocorrelation1|<tuple|4|4>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|7|6>>
    <associate|fig:corr|<tuple|21|20>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:heatcapacity|<tuple|12|11>>
    <associate|fig:pdfMH|<tuple|17|16>>
    <associate|fig:pdfSW|<tuple|18|17>>
    <associate|fig:susceptibility|<tuple|13|11>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:thermalizationMH|<tuple|2|2>>
    <associate|fig:thermalizationSW|<tuple|3|3>>
    <associate|fig:toruseffect|<tuple|1|2>>
    <associate|footnote-1|<tuple|1|?>>
    <associate|footnr-1|<tuple|1|?>>
    <associate|result_box|<tuple|5|?>>
    <associate|sec:betafss|<tuple|1.5|11>>
    <associate|sec:corr|<tuple|1.7|19>>
    <associate|sect:autocorrelation|<tuple|1.2|4>>
    <associate|sect:fss|<tuple|1.8|22>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|Illustration of two topologically non-trivial
      configurations obtained with the MH algorithm on a lattice
      <with|mode|<quote|math>|128\<times\>128>.|<pageref|auto-3>>

      <tuple|normal|Plot of the energy density and magnetization for the MH
      markov process at different values of
      <with|mode|<quote|math>|\<beta\>>.|<pageref|auto-4>>

      <tuple|normal|Plot of the energy density and magnetization for the SW
      markov process at different values of
      <with|mode|<quote|math>|\<beta\>>.|<pageref|auto-5>>

      <tuple|normal|Comparison of the energy for the two algorithms at
      <with|mode|<quote|math>|\<beta\>=\<beta\><rsub|c>> and
      <with|mode|<quote|math>|L=32>. (Left) MH (Right) SW.|<pageref|auto-7>>

      <tuple|normal|Plot of the integrated autocorrelation time near the
      phase transition for the MH algorithm. The raw data was obtained from a
      simulation of <with|mode|<quote|math>|10<rsup|6>> measurements on a
      lattice <with|mode|<quote|math>|32\<times\>32>. The fit in the center
      is not very accurate because near <with|mode|<quote|math>|\<beta\><rsub|c>>
      the autocorrelation time becomes very large and the interval
      <with|mode|<quote|math>|<around*|[|0,2000|]>> becomes too small for a
      reliable estimate of <with|mode|<quote|math>|\<tau\><rsub|int>>.|<pageref|auto-8>>

      <tuple|normal|Plot of the integrated autocorrelation time near the
      phase transition for the SW algorithm. The raw data was obtained from a
      simulation of <with|mode|<quote|math>|10<rsup|5>> measurements on a
      lattice <with|mode|<quote|math>|32\<times\>32>.|<pageref|auto-9>>

      <tuple|normal|Plot of the integrated autocorrelation time as a function
      of <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>
      for <with|mode|<quote|math>|L=32>.|<pageref|auto-10>>

      <tuple|normal|Binning analysis for the MH algorithm at various values
      of <with|mode|<quote|math>|\<beta\>>
      (<with|mode|<quote|math>|L=32>).|<pageref|auto-12>>

      <tuple|normal|Binning analysis for the SW algorithm at various values
      of <with|mode|<quote|math>|\<beta\>>
      (<with|mode|<quote|math>|L=32>).|<pageref|auto-13>>

      <tuple|normal|Energy density as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-15>>

      <tuple|normal|Magnetization as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-16>>

      <tuple|normal|Heat capacity as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-17>>

      <tuple|normal|Magnetic susceptibility as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-18>>

      <tuple|normal|Fit of the heat capacity and susceptibility peaks
      (MH).|<pageref|auto-20>>

      <tuple|normal|Fit of the heat capacity and susceptibility peaks
      (SW).|<pageref|auto-22>>

      <tuple|normal|Pseudocritical inverse temperature fit. MH on the left,
      SW on the right. The purple lines are relative to the heat capacity
      <with|mode|<quote|math>|C> while the green ones to the magnetic
      susceptibility <with|mode|<quote|math>|\<chi\>>.|<pageref|auto-24>>

      <tuple|normal|Probability distribution functions of
      <with|mode|<quote|math>|m> obtained from
      <with|mode|<quote|math>|10<rsup|6>> sweeps of MH on a lattice
      <with|mode|<quote|math>|8\<times\>8>.|<pageref|auto-26>>

      <tuple|normal|Probability distribution functions of
      <with|mode|<quote|math>|m> obtained from
      <with|mode|<quote|math>|10<rsup|6>> sweeps of SW on a lattice
      <with|mode|<quote|math>|8\<times\>8>.|<pageref|auto-27>>

      <tuple|normal|3d plot of <with|mode|<quote|math>|P<around*|(|m,\<beta\>|)>>
      as computed from <with|mode|<quote|math>|10<rsup|6>> measurements of
      <with|mode|<quote|math>|m> obtained on a
      <with|mode|<quote|math>|8\<times\>8> lattice with the MH
      algorithm.|<pageref|auto-28>>

      <\tuple|normal>
        Ilustration of the growth of spatial correlations when criticality is
        approached on a lattice <with|mode|<quote|math>|100\<times\>100> :
        <with|mode|<quote|math>|\<beta\>=0.22 , 0.31, 0.37, 0.39, 0.42,
        0.43>.
      </tuple|<pageref|auto-30>>

      <tuple|normal|Correlation functions for various values of
      <with|mode|<quote|math>|\<beta\>>. The lattice size used is
      <with|mode|<quote|math>|128\<times\>128> in order to reduce finite-size
      effects. As a precaution, we considers an interval in
      <with|mode|<quote|math>|\<beta\>>-space such that the correlation
      length is much smaller that the size of the lattice (approximately one
      order of magnitude smaller). |<pageref|auto-31>>

      <tuple|normal|Plot of the correlation length dependence on the
      parameter <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>
      for a lattice of size <with|mode|<quote|math>|128\<times\>128>. MH on
      the left and SW on the right. The errors are computed by jackknife
      binning of the fit data from (Fig.<reference|fig:corr>) through
      (<reference|eq:cosh>).|<pageref|auto-32>>

      <tuple|normal|Finite Size Scaling study for the lattice sizes
      <with|mode|<quote|math>|8<rsup|2>,16<rsup|2>,32<rsup|2>,64<rsup|2>>.
      Left MH, right SW. The top plot represents the scaling of the
      magnetization, the center one the magnetic susceptibility and the
      bottom one the heat capacity.|<pageref|auto-35>>
    </associate>
    <\associate|table>
      <tuple|normal|Pseudocritical <with|mode|<quote|math>|\<beta\>>-values
      obtained by polynomial fit of the peaks of <with|mode|<quote|math>|C>
      and <with|mode|<quote|math>|\<chi\>> (MH).|<pageref|auto-21>>

      <tuple|normal|Pseudocritical <with|mode|<quote|math>|\<beta\>>-values
      obtained by polynomial fit of the peaks of <with|mode|<quote|math>|C>
      and <with|mode|<quote|math>|\<chi\>> (SW).|<pageref|auto-23>>

      <tuple|normal|Exact critical exponents for the Ising model in
      <with|mode|<quote|math>|2d>.|<pageref|auto-34>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Ising
      Model <with|mode|<quote|math>|2d>> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Autocorrelation Times
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-6>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Binning Analysis
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-11>>

      <with|par-left|<quote|1tab>|1.4<space|2spc>Observables
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-14>>

      <with|par-left|<quote|1tab>|1.5<space|2spc><with|mode|<quote|math>|\<beta\>>
      Critical <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-19>>

      <with|par-left|<quote|1tab>|1.6<space|2spc>Probability Distribution
      Functions <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-25>>

      <with|par-left|<quote|1tab>|1.7<space|2spc>Spatial Correlations
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-29>>

      <with|par-left|<quote|1tab>|1.8<space|2spc>Finite Size Scaling
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-33>>
    </associate>
  </collection>
</auxiliary>