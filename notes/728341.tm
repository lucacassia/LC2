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

    <with|par-left|1tab|1.2<space|2spc>Estimators and Autocorrelation Times
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-5>>

    <with|par-left|1tab|1.3<space|2spc>Binning Analysis
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-9>>

    <with|par-left|1tab|1.4<space|2spc>Observables
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-13>>

    <with|par-left|1tab|1.5<space|2spc>Probability Distribution Functions
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-18>>

    <with|par-left|1tab|1.6<space|2spc>Spatial Correlations
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-20>>

    <with|par-left|1tab|1.7<space|2spc>Finite size scaling
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-22>>
  </table-of-contents>

  <section|Ising Model <math|2d>>

  In this section we study the statistical properties of a <math|2d> Ising
  Model. We consider a system of <math|L\<times\>L> spins situated on the
  points of a regular square lattice with periodic boundary conditions in
  both directions. Each spin interacts with its nearest neighbours inside the
  lattice, with an Hamiltonian:

  <\equation>
    H=<big|sum><rsub|<around*|\<langle\>|i,j|\<rangle\>>>\<sigma\><rsub|i>*\<sigma\><rsub|j>
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
  implement through Monte Carlo algorithms. In particular we focus on the
  Metropolis-Hastings (MH) and the Swendsen-Wang (SW) algorithms.

  <subsection|Thermalization>

  Since we do not know where to start in our Markov process, we first
  initialize the system in a disordered configuration (hot start) and then
  evolve for a certain Markov time until the system reaches equilibrium. This
  process is usually called <with|font-shape|italic|thermalization>.

  After a few run we decided to opt for a cold start approach (i.e., all the
  spins are initially aligned). The reason for this choice is that in
  <math|2>-dimensional finite-size systems with periodic boundary conditions
  the non trivial topology of the lattice allows the existence of stable
  configurations of the type depicted in (Fig.<reference|fig:toruseffect>),
  that often arise when the system is rapidly cooled from a disordered
  configuration. Those configurations would invalidate the mixing process and
  the sampling of relevant configurations at low temperatures. Therefore, by
  using a cold start, we exclude this possibility.

  <big-figure|<image|../ising/ising_128x128_0.610000.ppm|0.35par|||><space|2em><image|../ising/ising_128x128_0.690000.ppm|0.35par|||>|<label|fig:toruseffect>Illustration
  of two topologically non-trivial configurations on a lattice
  <math|128\<times\>128>.>

  We expect the MH algorithm to be slower to thermalize because of the local
  update it employes as opposed to the cluster update of the SW algorithm.

  <\big-figure>
    <image|../ising/thermalization/img/MH_thermalization_0.300000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_0.400000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_0.430000.eps|0.33par|||>

    <image|../ising/thermalization/img/MH_thermalization_0.500000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_0.600000.eps|0.33par|||><image|../ising/thermalization/img/MH_thermalization_0.800000.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationMH>Plot of the energy density for the
  MH markov process at different values of <math|\<beta\>> (<math|L=32>).>

  <\big-figure>
    <image|../ising/thermalization/img/SW_thermalization_0.300000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_0.400000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_0.430000.eps|0.33par|||>

    <image|../ising/thermalization/img/SW_thermalization_0.500000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_0.600000.eps|0.33par|||><image|../ising/thermalization/img/SW_thermalization_0.800000.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationSW>Plot of the energy density for the
  SW markov process at different values of <math|\<beta\>> (<math|L=32>).>

  The MH algorithm reaches thermalization very rapidly for inverse
  temperatures <math|\<beta\>> far from the critical value
  <math|\<beta\><rsub|c>>, while for values of <math|\<beta\>> near the phase
  transition it becomes much slower (Fig.<reference|fig:thermalizationMH>).
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

  where <math|z\<approx\>2> for local dynamics (MH).

  We also remark that for smaller values of <math|\<beta\>>, the energy of
  the system can have larger fluctuations around its average and therfore
  thermal equilibrium is reached faster.

  \;

  On the other hand the SW algorithm mixes very fast even at the phase
  transition (Fig.<reference|fig:thermalizationSW>) being a multicluster
  update algorithm (Fig.<reference|fig:thermalizationSW>).

  \;

  For the rest of the simulations we used a thermalization time
  <math|t<rsub|thermalization>=1000<rsup|>> both for MH and for SW.

  <subsection|<label|sect:autocorrelation>Estimators and Autocorrelation
  Times>

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

  here <math|n> is the total number of samples of <math|\<cal-O\><rsub|t>>
  and <math|\<mu\>,\<sigma\><rsup|2>> are the mean and variance of the
  process. For large time separations <math|k>, <math|R(k)> decays
  exponentially:

  <\equation>
    R<around*|(|k|)><long-arrow|\<rubber-rightarrow\>|k\<rightarrow\>\<infty\>>r\<mathe\><rsup|-k/\<tau\><rsub|\<cal-O\>,exp>>
  </equation>

  which defines the exponential autocorrelation time
  <math|\<tau\><rsub|\<cal-O\>,exp>>.

  \;

  We immediately see from (Fig.<reference|fig:autocorrelation1>) that the MH
  process is strongly correlated in time particularly near the phase
  transition:

  <big-figure|<image|../ising/thermalization/img/MH_energy_0.43.eps|0.5par|||><image|../ising/thermalization/img/SW_energy_0.43.eps|0.5par|||>|<label|fig:autocorrelation1>Comparison
  of the energy for the two algorithms at <math|\<beta\>=0.43>. (Left) MH
  (Right) SW.>

  We now compute the autocorrelation time <math|\<tau\><rsub|int>> for the
  observable <math|e> using formula (<reference|eq:tint>).

  <big-figure|<image|../ising/autocorrelation/img/MH_autocorrelation.eps|0.5par|||><image|../ising/autocorrelation/img/SW_autocorrelation.eps|0.5par|||>|Plot
  of the integrated autocorrelation time near the phase transition. (Left) MH
  (Right) SW.>

  The data is fitted using the function:

  <\equation>
    \<tau\><rsub|int><around*|(|k<rsub|max>|)>=\<tau\><rsub|int><around*|[|1-<frac|2*\<tau\><rsub|exp>|2*\<tau\><rsub|exp>+1>*\<mathe\><rsup|-k<rsub|max>/\<tau\><rsub|exp>>|]>
  </equation>

  As we can see, near the phase transition the autocorrelation time for the
  MH process becomes very large compared to the autocorrelation time of the
  SW process. In fact due to the critical slowing down of the MH algorithm,
  we have <math|\<tau\><rsub|int><rsup|MH>\<sim\>100> compared to an
  autocorrelation time <math|\<tau\><rsub|int><rsup|SW>\<sim\>5> for SW
  (Fig.<reference|fig:autocorrelation_time>).

  <big-figure|<image|../ising/autocorrelation/img/autocorrelation_time.eps|0.5par|||>|<label|fig:autocorrelation_time>Plot
  of the integrated autocorrelation time as a function of
  <math|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>.>

  We remark that the peak is slightly off centered because of the finite size
  of the lattice (<math|L=32>).

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
  <math|\<beta\>>.>

  <\big-figure>
    <image|../ising/binning/img/binning_SW_0.35.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.40.eps|0.5par|||>

    <image|../ising/binning/img/binning_SW_0.43.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.44.eps|0.5par|||>

    <image|../ising/binning/img/binning_SW_0.45.eps|0.5par|||><image|../ising/binning/img/binning_SW_0.50.eps|0.5par|||>
  </big-figure|Binning analysis for the SW algorithm at various values of
  <math|\<beta\>>.>

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

  we are now able to sample data without worrying about autocorrelation in
  the signal.

  <\big-figure>
    <image|../ising/binning/img/magnetization_bin_1000_MH.eps|0.5par|||><image|../ising/binning/img/magnetization_bin_1000_SW.eps|0.5par|||>
  </big-figure|<label|fig:energy_bin>Sampled data after the binning. MH on
  the left and SW on the right. As we can see the signal loses almost all of
  its autocorrelation after the binning.>

  <subsection|Observables>

  The main observables of interest for this system are the energy density
  <math|e> and the magnetization <math|m>:

  <\equation>
    e=E/V,<space|2em>E=<around*|\<langle\>|\<cal-H\>|\<rangle\>>,<space|2em>V=L<rsup|d>
  </equation>

  <\equation>
    m=M/V=<around*|\<langle\>|<around*|\||\<mu\>|\|>|\<rangle\>>,<space|2em>\<mu\>=<big|sum><rsub|i>\<sigma\><rsub|i>/V
  </equation>

  Thanks to the analytical solution of the <math|2d> Ising model, first
  obtained by Onsager, we are able to compare the estimators obtained by
  numerical simulations with their exact values obtained analytically.

  The samples are collected employing the binning procedure of the previous
  section.

  <big-figure|<image|../ising/observables/img/energy_plot_MH.eps|0.5par|||><image|../ising/observables/img/energy_plot_SW.eps|0.5par|||>|Energy
  density as a function of <math|\<beta\>>. MH on the left and SW on the
  right. The energy and the errors are computed from a sample of <math|100>
  blocks of binned data on a <math|32\<times\>32> lattice.>

  <big-figure|<image|../ising/observables/img/magnetization_plot_MH.eps|0.5par|||><image|../ising/observables/img/magnetization_plot_SW.eps|0.5par|||>|Magnetization
  as a function of <math|\<beta\>>. MH on the left and SW on the right.>

  We find that the simulation data are remarkably close to the exact solution
  both for the energy density and for the magnetization. The only departure
  from Onsager's solution is in the paramagnetic phase of the magnetization
  plot: there we observe that the exact solution goes abruptly to zero before
  the critical point, while the numerical data seems to interpolate a smooth
  function. This is imputable to the finite size of the lattice used for the
  simulation. It is indeed a well known fact that discontinuities and
  divergences only appear in the thermodinamic limit of infinite size, which
  is precisely the premise of Onsager's solution.

  In section (<reference|sect:fss>) we will see that as we scale the size of
  the lattice the numerical solution will approach more and more the exact
  one.

  \;

  We also plot the variance of <math|e> and <math|m> which are respectively
  proportional to the heat capacity <math|c> and the magnetic susceptibility
  <math|\<chi\>>:

  <\equation>
    c=V*<around*|(|<around*|\<langle\>|<around*|(|<frac|\<cal-H\>|V>|)><rsup|2>|\<rangle\>>-<around*|\<langle\>|<around*|(|<frac|\<cal-H\>|V>|)>|\<rangle\>><rsup|2>|)>
  </equation>

  <\equation>
    \<chi\>=V*<around*|(|<around*|\<langle\>|\<mu\><rsup|2>|\<rangle\>>-<around*|\<langle\>|<around*|\||\<mu\>|\|>|\<rangle\>><rsup|2>|)>
  </equation>

  <big-figure|<image|../ising/observables/img/variance_e_plot_MH.eps|0.5par|||><image|../ising/observables/img/variance_e_plot_SW.eps|0.5par|||>|Heat
  capacity as a function of <math|\<beta\>>. MH on the left and SW on the
  right.>

  <big-figure|<image|../ising/observables/img/variance_m_plot_MH.eps|0.5par|||><image|../ising/observables/img/variance_m_plot_SW.eps|0.5par|||>|Magnetic
  susceptibility as a function of <math|\<beta\>>. MH on the left and SW on
  the right.>

  <subsection|Probability Distribution Functions>

  We study the probability distribution of the magnetization:

  <\big-figure>
    <image|../ising/observables/img/pdf_m_0.30_MH.eps|0.33par|||><image|../ising/observables/img/pdf_m_0.42_MH.eps|0.33par|||><image|../ising/observables/img/pdf_m_0.43_MH.eps|0.33par|||>

    \;

    <image|../ising/observables/img/pdf_m_0.44_MH.eps|0.33par|||><image|../ising/observables/img/pdf_m_0.46_MH.eps|0.33par|||><image|../ising/observables/img/pdf_m_0.80_MH.eps|0.33par|||>
  </big-figure|<label|fig:pdfMH>Probability distribution function of <math|m>
  for various values of <math|\<beta\>> (<math|L=32>).>

  We see from (Fig.<reference|fig:pdfMH>) that the width of the distribution
  gets larger as <math|\<beta\>> approaches the critical value
  <math|\<beta\><rsub|c>>. This is in fact what we expect, knowing that the
  susceptibility diverges at a second order phase transition.

  <subsection|Spatial Correlations>

  Correlation functions are defined as:

  <\equation>
    G <around*|(|<wide|x|\<vect\>><rsub|i>-<wide|x|\<vect\>><rsub|j>|)>=<around*|\<langle\>|\<sigma\><rsub|i>*\<sigma\><rsub|j>|\<rangle\>><space|1em>\<sim\><space|1em>exp<around*|(|-<around*|\||<wide|x|\<vect\>><rsub|i>-<wide|x|\<vect\>><rsub|j>|\|>/\<xi\>|)><space|1em>for
    large<space|1em><around*|\||<wide|x|\<vect\>><rsub|i>-<wide|x|\<vect\>><rsub|j>|\|>
  </equation>

  where <math|\<xi\>> is the correlation length of the system:

  <\equation>
    \<xi\>=-lim<rsub|<around*|\||<wide|x|\<vect\>>|\|>\<rightarrow\>\<infty\>><around*|(|<around*|\||<wide|x|\<vect\>>|\|>/ln
    G<around*|(|<wide|x|\<vect\>>|)>|)>
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
    0.31, 0.37, 0.39, 0.42, 0.43>
  </big-figure>

  <subsection|Finite size scaling><label|sect:fss>

  \;
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
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|1.3|7>>
    <associate|auto-11|<tuple|7|8>>
    <associate|auto-12|<tuple|8|9>>
    <associate|auto-13|<tuple|9|9>>
    <associate|auto-14|<tuple|1.4|10>>
    <associate|auto-15|<tuple|10|10>>
    <associate|auto-16|<tuple|11|11>>
    <associate|auto-17|<tuple|12|11>>
    <associate|auto-18|<tuple|13|12>>
    <associate|auto-19|<tuple|1.5|12>>
    <associate|auto-2|<tuple|1.1|2>>
    <associate|auto-20|<tuple|14|12>>
    <associate|auto-21|<tuple|1.6|13>>
    <associate|auto-22|<tuple|15|13>>
    <associate|auto-23|<tuple|1.7|?>>
    <associate|auto-3|<tuple|1|2>>
    <associate|auto-4|<tuple|2|3>>
    <associate|auto-5|<tuple|3|4>>
    <associate|auto-6|<tuple|1.2|5>>
    <associate|auto-7|<tuple|4|5>>
    <associate|auto-8|<tuple|5|6>>
    <associate|auto-9|<tuple|6|6>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:scalingtau|<tuple|3|?>>
    <associate|eq:tint|<tuple|5|4>>
    <associate|fig:autocorrelation1|<tuple|4|5>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|6|6>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:pdfMH|<tuple|14|12>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:thermalizationMH|<tuple|2|2>>
    <associate|fig:thermalizationSW|<tuple|3|3>>
    <associate|fig:toruseffect|<tuple|1|?>>
    <associate|sect:autocorrelation|<tuple|1.2|4>>
    <associate|sect:fss|<tuple|1.7|13>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|Plot of the energy density for the MH markov process at
      different values of <with|mode|<quote|math>|\<beta\>>
      (<with|mode|<quote|math>|L=32>).|<pageref|auto-3>>

      <tuple|normal|Plot of the energy density for the SW markov process at
      different values of <with|mode|<quote|math>|\<beta\>>
      (<with|mode|<quote|math>|L=32>).|<pageref|auto-4>>

      <tuple|normal|Comparison of the energy for the two algorithms at
      <with|mode|<quote|math>|\<beta\>=0.43>. (Left) MH (Right)
      SW.|<pageref|auto-6>>

      <tuple|normal|Plot of the integrated autocorrelation time near the
      phase transition. (Left) MH (Right) SW.|<pageref|auto-7>>

      <tuple|normal|Plot of the integrated autocorrelation time as a function
      of <with|mode|<quote|math>|x=<frac|\<beta\>-\<beta\><rsub|c>|\<beta\><rsub|c>>>.|<pageref|auto-8>>

      <tuple|normal|Binning analysis for the MH algorithm at various values
      of <with|mode|<quote|math>|\<beta\>>.|<pageref|auto-10>>

      <tuple|normal|Binning analysis for the SW algorithm at various values
      of <with|mode|<quote|math>|\<beta\>>.|<pageref|auto-11>>

      <tuple|normal|Sampled data after the binning. MH on the left and SW on
      the right. As we can see the signal loses almost all of its
      autocorrelation after the binning.|<pageref|auto-12>>

      <tuple|normal|Energy density as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the right.
      The energy and the errors are computed from a sample of
      <with|mode|<quote|math>|100> blocks of binned data on a
      <with|mode|<quote|math>|32\<times\>32> lattice.|<pageref|auto-14>>

      <tuple|normal|Magnetization as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-15>>

      <tuple|normal|Heat capacity as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-16>>

      <tuple|normal|Magnetic susceptibility as a function of
      <with|mode|<quote|math>|\<beta\>>. MH on the left and SW on the
      right.|<pageref|auto-17>>

      <tuple|normal|Probability distribution function of
      <with|mode|<quote|math>|m> for various values of
      <with|mode|<quote|math>|\<beta\>> (<with|mode|<quote|math>|L=32>).|<pageref|auto-19>>

      <\tuple|normal>
        Ilustration of the growth of spatial correlations when criticality is
        approached on a lattice <with|mode|<quote|math>|100\<times\>100> :
        <with|mode|<quote|math>|\<beta\>=0.22 , 0.31, 0.37, 0.39, 0.42, 0.43>
      </tuple|<pageref|auto-21>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Ising
      Model <with|mode|<quote|math>|2d>> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Estimators and
      Autocorrelation Times <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Binning Analysis
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-9>>

      <with|par-left|<quote|1tab>|1.4<space|2spc>Observables
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-13>>

      <with|par-left|<quote|1tab>|1.5<space|2spc>Probability Distribution
      Functions <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-18>>

      <with|par-left|<quote|1tab>|1.6<space|2spc>Spatial Correlations
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-20>>

      <with|par-left|<quote|1tab>|1.7<space|2spc>Finite size scaling
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-22>>
    </associate>
  </collection>
</auxiliary>