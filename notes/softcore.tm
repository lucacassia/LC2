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
    <vspace*|1fn><with|font-series|bold|math-font-series|bold|1<space|2spc>Soft-Core
    Molecular Dynamics in <with|mode|math|3d>>
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-3>>

    <with|par-left|1tab|1.2<space|2spc>Momentum Distribution
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-5>>

    <with|par-left|1tab|1.3<space|2spc>Potential Energy and Fluctuations
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-7>>

    <with|par-left|1tab|1.4<space|2spc>Energy, Temperature and Pressure
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-9>>

    <with|par-left|1tab|1.5<space|2spc>Mean Squared Displacement
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-10>>

    <with|par-left|1tab|1.6<space|2spc>Thermodynamic Limit
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-11>>
  </table-of-contents>

  <section|Soft-Core Molecular Dynamics in <math|3d>>

  We now consider a system of <math|N> particles enclosed in a box with PBC
  and interacting through a smooth central potential which is repulsive at
  short range and attractive at large distances. The most common form of this
  kind of potential is the <strong|Lennard-Jones> (L-J) potential:

  <\equation>
    U<around*|(|r|)>=4*\<varepsilon\>*<around*|[|<around*|(|<frac|\<sigma\>|r>|)><rsup|12>-<around*|(|<frac|\<sigma\>|r>|)><rsup|6>|]>,<space|3em>r=<around*|\||<wide|x|\<vect\>>|\|>
  </equation>

  where <with|font-shape|italic|\<varepsilon\>> is the depth of the potential
  well, <with|font-shape|italic|\<sigma\>> is the finite distance at which
  the inter-particle potential is zero and <with|font-shape|italic|r> is the
  distance between the particles. Upon differentiation we obtain the force
  acting between pair of particles:

  <\equation>
    F<around*|(|r|)>=-<frac|\<partial\>|\<partial\>*r>*U<around*|(|r|)>=24*<frac|\<varepsilon\>|\<sigma\>>*<around*|[|2<around*|(|<frac|\<sigma\>|r>|)><rsup|13>-<around*|(|<frac|\<sigma\>|r>|)><rsup|7>|]>
  </equation>

  To save computational time and satisfy the minimum image convention, the
  Lennard-Jones potential is often truncated at a cut-off distance of
  <math|r<rsub|c>=2.5*\<sigma\>>, where:

  <\equation>
    U<around*|(|r<rsub|c>|)>=4*\<varepsilon\>*<around*|[|<around*|(|<frac|1|2.5>|)><rsup|12>-<around*|(|<frac|1|2.5>|)><rsup|6>|]>\<approx\>-0.0163*\<varepsilon\>
  </equation>

  At distances larger than <math|r<rsub|c>> the potential is less than
  <math|<frac|1|60>> the minimum value <math|\<varepsilon\>>, therefore the
  truncation gives us a good approximation of the full potential. As a
  consistency measure, we assume <math|r<rsub|c>\<less\>L>, with <math|L>
  being the size of the box (<math|L<rsup|d>=V>).

  \;

  Since the truncation introduces a jump discontinuity at the cut-off
  distance, we need to shift the potential upward so that
  <math|U<around*|(|r<rsub|c>|)>=0> and also impose that the first derivative
  is continuous in the interval <math|<around*|(|0,\<infty\>|)>>. The
  truncated and shifted potential is defined as follows:

  <\equation>
    U<rsub|trunc><around*|(|r|)>=<choice|<tformat|<table|<row|<cell|U<around*|(|r|)>-U<around*|(|r<rsub|c>|)>+<around*|(|r-r<rsub|c>|)>*F<around*|(|r<rsub|c>|)>>|<cell|for>|<cell|r\<leq\>r<rsub|c>>>|<row|<cell|0>|<cell|for>|<cell|r\<gtr\>r<rsub|c>>>>>>
  </equation>

  where <math|F<around*|(|r<rsub|c>|)>> is the value of the force at the
  cut-off:

  <\equation>
    F<around*|(|r<rsub|c>|)>=24*<frac|\<varepsilon\>|\<sigma\>>*<around*|[|<around*|(|<frac|1|2.5>|)><rsup|13>-<around*|(|<frac|1|2.5>|)><rsup|7>|]>\<approx\>-0.039*<frac|\<varepsilon\>|\<sigma\>>
  </equation>

  <big-figure|<image|../softcore/LJ.eps|0.75par|||>|Plot of the truncated L-J
  potential.>

  Since the L-J potential depends only upon the two parameters
  <math|\<sigma\>> and <math|\<varepsilon\>>, which determine the length and
  energy scales of the system, we can choose to work in adimensional units
  where:

  <\equation>
    m=1,<space|1em>\<sigma\>=1,<space|1em>\<varepsilon\>=1,<space|1em>L\<neq\>1
  </equation>

  \;

  \;

  The time evolution of the system is obtained by numerical integration of
  the equations of motion. The method employed is the <strong|Velocity
  Verlet> algorithm, which consists of the four steps:

  <\enumerate>
    <item>half step velocity update: \ <math|<wide|v|\<vect\>>
    <around*|(|t+<frac|1|2>\<Delta\>t|)>=<wide|v|\<vect\>><around*|(|t|)>+><math|<frac|1|2>*<wide|a|\<vect\>>
    <around*|(|t|)>*\<Delta\>t>

    <item>full step position update: <math|<wide|x|\<vect\>>
    <around*|(|t+\<Delta\>t|)>=<wide|x|\<vect\>>
    <around*|(|t|)>+<wide|v|\<vect\>> <around*|(|t+<frac|1|2>\<Delta\>t|)>*\<Delta\>t>

    <item>recompute accelerations: <math|<wide|a|\<vect\>>
    <around*|(|t+\<Delta\>t|)>=<frac|1|m>*<wide|F|\<vect\>><around*|(|t+\<Delta\>t|)>>

    <item>half step velocity update: <math|<wide|v|\<vect\>>
    <around*|(|t+\<Delta\>t|)>=<wide|v|\<vect\>>
    <around*|(|t+<frac|1|2>\<Delta\>t|)>+<frac|1|2>*<wide|a|\<vect\>>
    <around*|(|t+\<Delta\>t|)>>
  </enumerate>

  where in step (2) we must apply periodic boundary conditions in each of the
  <math|d> directions. The unit time interval is chosen to be
  <math|\<Delta\>t=0.001>.

  \;

  For conservative systems, it can be shown that the energy of the Verlet
  approximation essentially oscillates around the constant energy of the
  exactly solved system, with a global error bound of order
  <math|\<cal-O\><around*|(|\<Delta\>t<rsup|2>|)>>.

  \;

  <with|font-shape|italic|Technical Note:> in order to further reduce the
  computational cost of the algorithm, we construct a table
  <math|T<rsub|i*j>> in which we save, for each particle <math|i>, the list
  of neighbouring particles <math|j> at distances
  <math|r<rsub|i*j>\<less\>2.8*\<sigma\>=r<rsub|m>>. Only the particles
  inside the neighbour list are taken into account in the calculations of the
  accelerations. The list itself is then updated once every 10 evolution
  steps to keep up with the movement of the particles.

  <subsection|Thermalization>

  Particles are initialized in a regular BCC lattice structure with momenta
  randomly assigned in the multi<nbsp>interval
  <math|<around*|[|-1,1|]><rsup|d>>. The istantaneous temperature
  <math|k*T=<frac|2|d>K> can then be set to a desired value
  <math|k*T<rprime|'>> by rescaling the momenta as:

  <\equation>
    <label|eq:rescale>p<rsub|i>\<rightarrow\>p<rsub|i><rprime|'>=p<rsub|i>*<sqrt|<frac|k*T<rprime|'>|k*T>>
  </equation>

  While the mechanical energy <math|H=K+U> is conserved in time, the kinetic
  energy <math|K> and the temperature <math|k*T> are not, hence the rescaling
  of (<reference|eq:rescale>) must be repeated at regular intervals until
  thermalization is reached.

  <big-figure|<image|../softcore/thermalization/img/thermalizationU.eps|0.5par|||><image|../softcore/thermalization/img/thermalizationH.eps|0.5par|||>|Thermalization
  of a system of softcore particles at density <math|\<rho\>=0.7>,
  <math|k*T=1.19> for <math|N=108,250,500>. On the left we show the evolution
  of the density of potential energy <math|U/N> in the first 5000 integration
  steps. On the right is the total energy density <math|H/N>, first during
  the thermalization phase (<math|0\<less\>t\<less\>10>), in which the
  temperature is kept constant, and then in the measurement phase
  (<math|t\<gtr\>10>) when the energy <math|H> is constant.>

  \;

  We define the <em|density> of the system as:

  <\equation>
    \<rho\>=<frac|N*\<sigma\><rsup|d>|L<rsup|d>><space|1em>\<Longrightarrow\><space|1em>L=\<sigma\>*<around*|(|<frac|N|\<rho\>>|)><rsup|<frac|1|d>>
  </equation>

  and, since <math|\<sigma\>=1>, we can choose to define the properties of
  the system by setting some values for <math|N> and <math|\<rho\>>, thus
  automatically fixing the value of <math|L>.

  <subsection|Momentum Distribution>

  Because the system in exam is not an ideal gas, the probability
  distribution of the momenta could in principle be quite different from the
  Maxwell-Boltzmann distribution. However, the L-J potential is still a good
  approximation of that of an ideal gas expecially at low densities where the
  gas is very rarefied.

  \;

  In (Fig.<reference|fig:dist>) we show that a gas of <math|N=250> particles
  at <math|\<rho\>=0.5> and <math|k*T=1>, reaches thermal equilibrium with a
  Maxwell<nbsp>Boltzmann distribution:

  <big-figure|<image|../softcore/distribution/img/xdistribution.eps|0.5par|||><image|../softcore/distribution/img/mdistribution.eps|0.5par|||>|<label|fig:dist>Momentum
  distributions for a system of <math|N=250> particles at <math|\<rho\>=0.5>
  and <math|k<rsub|b>T=1.0>. On the left is the <math|v<rsub|x>> distribution
  and on the right is the distribution of the modulus of the momentum. The
  measurements were taken every 100 evolution steps for <math|10<rsup|5>>
  steps, each time collecting the momenta of every particle thus giving a
  total of <math|250000<rsup|>> samples. The simulation was preceded by a
  thermalization phase of <math|t<rsub|therm>=5000*\<Delta\>t=5>. The red
  lines represent fits with Maxwell-Boltzmann distributions.>

  \;

  We can compare the initial temperature of the simulation with the widths of
  the distributions to establish if the system has reached equilibrium at the
  right temperature. The results of the fit are in fact in good accordance
  with the chosen value <math|k*T=1.0> :

  <\eqnarray>
    <tformat|<table|<row|<cell|k*T>|<cell|=>|<cell|0.997\<pm\>0.003<space|1em><around*|(|v<rsub|x><space|0.5em>fit
    |)>>>|<row|<cell|k*T>|<cell|=>|<cell|0.995\<pm\>0.002<space|1em><around*|(|<around*|\||<wide|v|\<vect\>>|\|><space|0.5em>fit
    |)>>>>>
  </eqnarray>

  <subsection|Potential Energy and Fluctuations>

  We define the density of potential (internal) energy:

  <\equation>
    u=<frac|U|N>
  </equation>

  as the average potential energy associated to each particle, and study its
  fluctuations around the mean value <math|<around*|\<langle\>|u|\<rangle\>>>,
  since, as pointed out before, the quantities <math|K> and <math|U> are not
  conserved individually but only as the sum <math|H=K+U>.

  \;

  We compute the time evolution of the observable <math|u> for systems of
  <math|N=108,250,500> particles at density <math|\<rho\>=0.7> and initial
  temperature <math|k*T=1.19>.

  <big-figure|<image|../softcore/thermalization/img/fluctuationsU.eps|0.75par|||>|Internal
  energy density <math|u> for <math|N=108,250,500> at <math|\<rho\>=0.7> and
  <math|k*T=1.19>. Thermalization time <math|t<rsub|term>=10> and total time
  of the simulation <math|t=100> (<math|\<Delta\>t=0.001>). During the
  thermalization phase the momenta were rescaled every 10 steps in order to
  fix the temperature to the desired value.>

  <center|<block*|<tformat|<table|<row|<cell|<math|N>>|<cell|<math|<around*|\<langle\>|u|\<rangle\>>>>|<cell|<math|\<Delta\>u>>>|<row|<cell|<math|108>>|<cell|<math|-3.5141>>|<cell|<math|0.0760>>>|<row|<cell|<math|250>>|<cell|<math|-3.4948>>|<cell|<math|0.0501>>>|<row|<cell|<math|500>>|<cell|<math|-3.5066>>|<cell|<math|0.0358>>>>>>>

  \;

  \;

  These results were obtained by averaging over a set of <math|10<rsup|3>>
  measurements taken once every 100 evolution steps in order to reduce
  autocorrelation effects. The measurement phase was also preceded by a
  thermalization time <math|t<rsub|therm>=10>.

  \;

  \;

  We immediately notice that the amplitude of the fluctuations decreases as
  the number of particle <math|N> gets larger. In fact, for a macroscopic
  system, we expect both the variance and the mean of the energy to scale as
  <math|N>, hence:

  <\equation>
    <frac|\<Delta\>U<rsup|2>|<around*|\<langle\>|U|\<rangle\>><rsup|2>>=<frac|<around*|\<langle\>|U<rsup|2>|\<rangle\>>-<around*|\<langle\>|U|\<rangle\>><rsup|2>|<around*|\<langle\>|U|\<rangle\>><rsup|2>>\<sim\><frac|1|N><long-arrow|\<rubber-rightarrow\>||N\<rightarrow\>\<infty\>>0
  </equation>

  As a consequence, if we consider the density <math|u>, we have:

  <\equation>
    u=<frac|U|N>\<sim\><frac|N|N>=1,<space|2em>\<Delta\>u=<sqrt|<around*|\<langle\>|<around*|(|u-<around*|\<langle\>|u|\<rangle\>>|)><rsup|2>|\<rangle\>>>=<frac|\<Delta\>U|N>\<sim\><frac|<sqrt|N>|N>=<frac|1|<sqrt|N>><long-arrow|\<rubber-rightarrow\>||N\<rightarrow\>\<infty\>>0
  </equation>

  which implies:

  <\equation*>
    \<Delta\>u*\<cdot\><sqrt|N>\<sim\>const.<space|2em><choice|<tformat|<table|<row|<cell|0.0760\<cdot\><sqrt|108>>|<cell|\<approx\>>|<cell|0.789815\<ldots\>>>|<row|<cell|0.0501\<cdot\><sqrt|250>>|<cell|\<approx\>>|<cell|0.792151\<ldots\>>>|<row|<cell|0.0358\<cdot\><sqrt|500>>|<cell|\<approx\>>|<cell|0.800512\<ldots\>>>>>>
  </equation*>

  This is actually the well known result that, in the thermodynamic limit,
  the energy of a grand-canonical ensamble converges to its expectation
  value, thus giving a physically equivalent description to that of a
  micro-canonical ensamble.

  <subsection|Energy, Temperature and Pressure>

  <subsection|Mean Squared Displacement>

  <subsection|Thermodynamic Limit>

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
    <associate|preamble|false>
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|1.5|6>>
    <associate|auto-11|<tuple|1.6|6>>
    <associate|auto-12|<tuple|6|8>>
    <associate|auto-13|<tuple|7|8>>
    <associate|auto-14|<tuple|8|9>>
    <associate|auto-15|<tuple|9|9>>
    <associate|auto-16|<tuple|10|9>>
    <associate|auto-17|<tuple|11|11>>
    <associate|auto-18|<tuple|12|12>>
    <associate|auto-19|<tuple|13|12>>
    <associate|auto-2|<tuple|1|2>>
    <associate|auto-20|<tuple|14|11>>
    <associate|auto-21|<tuple|15|11>>
    <associate|auto-22|<tuple|2|11>>
    <associate|auto-23|<tuple|13|12>>
    <associate|auto-24|<tuple|3|9>>
    <associate|auto-25|<tuple|14|9>>
    <associate|auto-26|<tuple|15|10>>
    <associate|auto-27|<tuple|16|10>>
    <associate|auto-28|<tuple|17|10>>
    <associate|auto-29|<tuple|3|9>>
    <associate|auto-3|<tuple|1.1|3>>
    <associate|auto-30|<tuple|19|9>>
    <associate|auto-31|<tuple|20|21>>
    <associate|auto-32|<tuple|21|22>>
    <associate|auto-33|<tuple|1.8|23>>
    <associate|auto-34|<tuple|3|23>>
    <associate|auto-35|<tuple|23|24>>
    <associate|auto-36|<tuple|24|?>>
    <associate|auto-4|<tuple|2|3>>
    <associate|auto-5|<tuple|1.2|3>>
    <associate|auto-6|<tuple|3|4>>
    <associate|auto-7|<tuple|1.3|4>>
    <associate|auto-8|<tuple|4|5>>
    <associate|auto-9|<tuple|1.4|6>>
    <associate|cwos|<tuple|3|?>>
    <associate|diffusion|<tuple|11|?>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:betac|<tuple|7|?>>
    <associate|eq:cosh|<tuple|22|10>>
    <associate|eq:diffusion|<tuple|2|10>>
    <associate|eq:msd|<tuple|1|9>>
    <associate|eq:msd0|<tuple|6|10>>
    <associate|eq:plateau|<tuple|7|10>>
    <associate|eq:rescale|<tuple|7|3>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:temp|<tuple|4|2>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:collision_time|<tuple|4|9>>
    <associate|fig:corr|<tuple|11|10>>
    <associate|fig:dist|<tuple|3|4>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:fss|<tuple|13|12>>
    <associate|fig:heatcapacity|<tuple|5|5>>
    <associate|fig:hist1|<tuple|1|5>>
    <associate|fig:hist2|<tuple|2|6>>
    <associate|fig:lattice|<tuple|1|?>>
    <associate|fig:levels|<tuple|8|7>>
    <associate|fig:msd|<tuple|1|11>>
    <associate|fig:msd1|<tuple|2|12>>
    <associate|fig:msd3|<tuple|5|?>>
    <associate|fig:packing|<tuple|1|2>>
    <associate|fig:pdfMH|<tuple|9|8>>
    <associate|fig:pdfSW|<tuple|13|7>>
    <associate|fig:susceptibility|<tuple|5|4>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:therm1|<tuple|2|3>>
    <associate|fig:therm2|<tuple|3|4>>
    <associate|fig:thermalization|<tuple|1|2>>
    <associate|fig:thermalizationMH|<tuple|2|3>>
    <associate|fig:thermalizationSW|<tuple|3|4>>
    <associate|fig:times|<tuple|5|9>>
    <associate|fig:toruseffect|<tuple|1|3>>
    <associate|fig:trajectory|<tuple|3|12>>
    <associate|fig:trajectory2|<tuple|4|?>>
    <associate|footnote-1|<tuple|1|11>>
    <associate|footnote-2|<tuple|2|?>>
    <associate|footnr-1|<tuple|1|11>>
    <associate|footnr-2|<tuple|2|?>>
    <associate|result_box|<tuple|8|?>>
    <associate|sec:betafss|<tuple|1.4|4>>
    <associate|sec:corr|<tuple|1.6|9>>
    <associate|sect:autocorrelation|<tuple|1.2|2>>
    <associate|sect:fss|<tuple|1.7|11>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|Plot of the truncated L-J potential.|<pageref|auto-2>>

      <tuple|normal|Thermalization of a system of softcore particles at
      density <with|mode|<quote|math>|\<rho\>=0.7>,
      <with|mode|<quote|math>|k*T=1.19> for
      <with|mode|<quote|math>|N=108,250,500>. On the left we show the
      evolution of the density of potential energy
      <with|mode|<quote|math>|U/N> in the first 5000 integration steps. On
      the right is the total energy density <with|mode|<quote|math>|H/N>,
      first during the thermalization phase
      (<with|mode|<quote|math>|0\<less\>t\<less\>10>), in which the
      temperature is kept constant, and then in the measurement phase
      (<with|mode|<quote|math>|t\<gtr\>10>) when the energy
      <with|mode|<quote|math>|H> is constant.|<pageref|auto-4>>

      <tuple|normal|Momentum distributions for a system of
      <with|mode|<quote|math>|N=250> particles at
      <with|mode|<quote|math>|\<rho\>=0.5> and
      <with|mode|<quote|math>|k<rsub|b>T=1.0>. On the left is the
      <with|mode|<quote|math>|v<rsub|x>> distribution and on the right is the
      distribution of the modulus of the momentum. The measurements were
      taken every 100 evolution steps for <with|mode|<quote|math>|10<rsup|5>>
      steps, each time collecting the momenta of every particle thus giving a
      total of <with|mode|<quote|math>|250000<rsup|>> samples. The simulation
      was preceded by a thermalization phase of
      <with|mode|<quote|math>|t<rsub|therm>=5000*\<Delta\>t=5>. The red lines
      represent fits with Maxwell-Boltzmann distributions.|<pageref|auto-6>>

      <tuple|normal|Internal energy density <with|mode|<quote|math>|u> for
      <with|mode|<quote|math>|N=108,250,500> at
      <with|mode|<quote|math>|\<rho\>=0.7> and
      <with|mode|<quote|math>|k*T=1.19>. Thermalization time
      <with|mode|<quote|math>|t<rsub|term>=10> and total time of the
      simulation <with|mode|<quote|math>|t=100>
      (<with|mode|<quote|math>|\<Delta\>t=0.001>). During the thermalization
      phase the momenta were rescaled every 10 steps in order to fix the
      temperature to the desired value.|<pageref|auto-8>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Soft-Core
      Molecular Dynamics in <with|mode|<quote|math>|3d>>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-3>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Momentum Distribution
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Potential Energy and
      Fluctuations <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-7>>

      <with|par-left|<quote|1tab>|1.4<space|2spc>Energy, Temperature and
      Pressure <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-9>>

      <with|par-left|<quote|1tab>|1.5<space|2spc>Mean Squared Displacement
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-10>>

      <with|par-left|<quote|1tab>|1.6<space|2spc>Thermodynamic Limit
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-11>>
    </associate>
  </collection>
</auxiliary>