<TeXmacs|1.99.2>

<style|article>

<\body>
  <doc-data|<doc-title|Laboratory of Computational
  Physics>|<doc-author|<author-data|<author-name|Luca
  Cassia>|<\author-affiliation>
    Dipartimento di Fisica, UniversitÓ di Milano-Bicocca, I-20126 Milano,
    Italy
  </author-affiliation>|<\author-email>
    l.cassia@campus.unimib.it
  </author-email>>>>

  <\table-of-contents|toc>
    <vspace*|1fn><with|font-series|bold|math-font-series|bold|1<space|2spc>Ising
    Model> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-2>>

    <with|par-left|1tab|1.2<space|2spc>Autocorrelation
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-5>>
  </table-of-contents>

  <section|Ising Model>

  In this section we study the statistical properties of a <math|2d> Ising
  Model. We consider a system of <math|32\<times\>32> spins situated on the
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
  initialize the system in a random configuration (hot start) and then evolve
  for a certain Markov time until thermalization is reached. We expect the MH
  algorithm to be slower to thermalize because of the local update it
  employes as opposed to the cluster update of the SW algorithm.

  <\big-figure>
    <image|../ising/thermalization/img/thermalization_MH_0.2.eps|0.33par|||><image|../ising/thermalization/img/thermalization_MH_0.3.eps|0.33par|||><image|../ising/thermalization/img/thermalization_MH_0.4.eps|0.33par|||>

    <image|../ising/thermalization/img/thermalization_MH_0.45.eps|0.33par|||><image|../ising/thermalization/img/thermalization_MH_0.5.eps|0.33par|||><image|../ising/thermalization/img/thermalization_MH_0.6.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationMH>Plot of the energy density for the
  MH markov process at different values of <math|\<beta\>>. The first
  <math|3.5\<cdot\>10<rsup|6>> steps are drawn to show the thermalization
  process of the system.>

  <\big-figure>
    <image|../ising/thermalization/img/thermalization_SW_0.2.eps|0.33par|||><image|../ising/thermalization/img/thermalization_SW_0.3.eps|0.33par|||><image|../ising/thermalization/img/thermalization_SW_0.4.eps|0.33par|||>

    <image|../ising/thermalization/img/thermalization_SW_0.45.eps|0.33par|||><image|../ising/thermalization/img/thermalization_SW_0.5.eps|0.33par|||><image|../ising/thermalization/img/thermalization_SW_0.6.eps|0.33par|||>
  </big-figure|<label|fig:thermalizationSW>Plot of the energy density for the
  SW markov process at different values of <math|\<beta\>>. This time we only
  present the first <math|500> steps.>

  As we can see from (Fig.<reference|fig:thermalizationMH>) the MH algorithm
  reaches thermalization after a Markov time two orders of magnitude larger
  than the lattice size <math|32\<times\>32> while the SW algorithm
  (Fig.<reference|fig:thermalizationSW>) takes only <math|\<sim\> 500> steps.
  The reason for this discrepancy is that the MH update algorithm is local
  and therefore successive steps in the chain are strogly correlated, as we
  will see in section (<reference|sect:autocorrelation>).

  This effect is called <with|font-shape|italic|critical slowing down> and it
  tells us that when using local update algorithms only approximately every
  <math|N\<times\>N> sweeps through the lattice, a statistically independent
  measurement can be taken.

  We also remark that for smaller values of <math|\<beta\>>, the system
  energy can have larger fluctuations around its average and therfore thermal
  equilibrium is reached faster. For the rest of the simulations we used a
  thermalization time of <math|5\<cdot\>10<rsup|6>> for MH and
  <math|5\<cdot\>10<rsup|2>> for SW.

  <subsection|<label|sect:autocorrelation>Autocorrelation>

  We now study the correlations present between consecutive configurations
  sampled by the two algorithms in order to obtain the characteristic time
  after which we can consider two configurations as statistically
  independent. This is called <with|font-shape|italic|integrated
  autocorrelation time> and is computed in the following way:

  <\equation>
    \<tau\><rsub|\<cal-O\>>=<frac|1|2>+<big|sum><rsub|k=1><rsup|k<rsub|max>>R
    <around*|(|k|)>
  </equation>

  where <math|\<cal-O\>> is the physical observable for which we compute
  autocorrelation and <math|R<around*|(|k|)>> is defined as:

  <\equation>
    R <around*|(|k|)> = <frac|1|<around*|(|n-k|)>*\<sigma\><rsup|2>>*<big|sum><rsup|n-k><rsub|t=1><around*|(|\<cal-O\><rsub|t>-\<mu\>|)>*<around*|(|\<cal-O\><rsub|t+k>-\<mu\>|)>
  </equation>

  here <math|n> is the total number of samples of <math|\<cal-O\><rsub|t>>
  and <math|\<mu\>,\<sigma\><rsup|2>> are the mean and variance of the
  process.

  \;

  We immediately see from (Fig.<reference|fig:autocorrelation1>) that the MH
  process is strongly correlated in time even for small values of the
  temperature:

  <big-figure|<image|../ising/thermalization/img/magnetization_MH_0.3.eps|0.5par|||><image|../ising/thermalization/img/magnetization_SW_0.3.eps|0.5par|||>|<label|fig:autocorrelation1>Comparison
  of the magnetization for the two algorithms at <math|\<beta\>=0.3>. (Left)
  MH (Right) SW.>

  Only on a larger time scale, the MH process can be regarded as weakly
  correlated (Fig.<reference|fig:autocorrelation2>):

  <big-figure|<image|../ising/thermalization/img/magnetization_MH2_0.3.eps|0.5par|||>|<label|fig:autocorrelation2>Average
  magnetization for the MH process observed on a larger time interval.>

  We compute the autocorrelation time <math|\<tau\><rsub|e>> for the
  observable <math|e> (energy density).
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
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-2|<tuple|1.1|2>>
    <associate|auto-3|<tuple|1|2>>
    <associate|auto-4|<tuple|2|3>>
    <associate|auto-5|<tuple|1.2|3>>
    <associate|auto-6|<tuple|3|4>>
    <associate|auto-7|<tuple|4|4>>
    <associate|auto-8|<tuple|1.4|?>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|fig:autocorrelation1|<tuple|3|4>>
    <associate|fig:autocorrelation2|<tuple|4|4>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:thermalizationMH|<tuple|1|2>>
    <associate|fig:thermalizationSW|<tuple|2|3>>
    <associate|sect:autocorrelation|<tuple|1.2|3>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|Plot of the energy density for the MH markov process at
      different values of <with|mode|<quote|math>|\<beta\>>. The first
      <with|mode|<quote|math>|3.5\<cdot\>10<rsup|6>> steps are drawn to show
      the thermalization process of the system.|<pageref|auto-3>>

      <tuple|normal|Plot of the energy density for the SW markov process at
      different values of <with|mode|<quote|math>|\<beta\>>. This time we
      only present the first <with|mode|<quote|math>|500>
      steps.|<pageref|auto-4>>

      <tuple|normal|Comparison of the magnetization for the two algorithms at
      <with|mode|<quote|math>|\<beta\>=0.3>. (Left) MH (Right)
      SW.|<pageref|auto-6>>

      <tuple|normal|Average magnetization for the MH process observed on a
      larger time interval.|<pageref|auto-7>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Ising
      Model> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Autocorrelation
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5>>
    </associate>
  </collection>
</auxiliary>