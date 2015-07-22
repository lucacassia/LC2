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
    <vspace*|1fn><with|font-series|bold|math-font-series|bold|1<space|2spc>Hard-Core
    Molecular Dynamics in <with|mode|math|3d>>
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-2>>

    <with|par-left|1tab|1.2<space|2spc>Phase Transition
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-5>>

    <with|par-left|1tab|1.3<space|2spc>Mean Squared Displacement
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-7>>

    <with|par-left|1tab|1.4<space|2spc>Thermodynamic Limit
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-10>>
  </table-of-contents>

  <section|Hard-Core Molecular Dynamics in <math|3d>>

  In this section we repeat the study of molecular dynamics with hard-core
  central potential for <math|3d> systems. As for the <math|2>-dimensional
  case, we work with identical particles enclosed in a box with PBCs and use
  adimensional units of length, time and mass:

  <\equation>
    L=1,<space|1em>m=1,<space|1em>k<rsub|b>T=1
  </equation>

  <subsection|Thermalization>

  The system is initialized in a BCC lattice (Fig.<reference|fig:packing>).
  This type of sphere packing has a packing density:

  <\equation>
    \<eta\>=<frac|N*\<pi\>*\<sigma\><rsup|3>|6L<rsup|3>>,<space|3em>\<sigma\>=<sqrt|<frac|6\<eta\>|\<pi\>N>|3>*L
  </equation>

  which takes its maximum value for <math|\<sigma\><rsup|3>=<around*|(|3<sqrt|3>L<rsup|3>|)>/4N>:

  <\equation>
    \<eta\><rsub|max>=<frac|\<pi\><sqrt|3>|8>\<approx\>0.68017476158\<ldots\>
  </equation>

  \ The momenta of the particles are initializated with uniform distribution
  inside the range <math|<around*|[|-1,1|]>> with total momentum equal to
  zero (center of mass reference frame). After the initialization the momenta
  are rescaled in order to obtain the desired temperature. As before, we have
  the relation between kinetic energy and temperature:

  <\equation>
    K=<frac|d|2>*N*k<rsub|b>*T,<space|1em>T=<frac|2|d*N*k<rsub|b>>*K
  </equation>

  \;

  We now study the mixing properties of this type of system. We evolve a
  system of <math|N=100> particles from its initial configuration, for
  <math|10<rsup|4>> collisions and measure the pressure
  (Fig.<reference|fig:therm1>) and the mean free path
  (Fig.<reference|fig:therm2>) every <math|10> collisions. This procedure is
  also repeated for <math|N=400>.

  <\big-figure>
    <image|../hardcore3d/thermalization/img/thermalization2.eps|0.5par|||><image|../hardcore3d/thermalization/img/thermalization6.eps|0.5par|||>
  </big-figure|<label|fig:therm1>Plot of the thermalization process of an
  hard-core interacting gas of <math|N=128> particles. On the left is the
  pressure as a function of the number of collisions, while on the right is
  the mean free path of the particles. Different colors represent the
  different values of <math|\<eta\>=0.25,0.35,0.45,0.55,0.65> used for the
  simulations. >

  \;

  We consider the system thermalized after <math|5\<cdot\>10<rsup|4>>
  collisions where we expect a momentum distribution of the Maxwell-Boltzmann
  type. The distribution obtained from the simulation confirms our choice of
  thermalization time:

  \;

  <\big-figure|<image|../hardcore3d/distribution/img/mdistribution.eps|0.75par|||>>
    <label|fig:hist1>Histogram of the modulus of the momenta for <math|N=128>
    particles at <math|\<eta\>=0.5>. The measurements are taken after
    <math|5\<cdot\>10<rsup|4>> collisions from the start of the simulation,
    and after that every <math|500> collisions for a total of
    <math|10<rsup|4>> datasets each containing the momenta of <math|N>
    particles.
  </big-figure>

  By fitting the histogram we obtain the result:

  <\equation>
    k<rsub|b>T=1.00922\<pm\>0.00559
  </equation>

  which is remarkably close to the numerical value <math|k<rsub|b>T=1> that
  was set at the beginning of the simulation.

  <subsection|Phase Transition>

  In this section we study the <math|\<eta\>> dependence of the pressure
  <math|P> for a system of <math|N=250> particles. As for the
  <math|2>-dimensional case we use the formula:

  <\equation>
    <frac|P*V|N*k<rsub|b>T>=1+<frac|1|2K*t><big|sum><rsub|c=1><rsup|N<rsub|c>>m*\<sigma\><around*|\||\<Delta\><wide|v|\<vect\>><rsub|i*j><around*|(|t<rsub|c>|)>|\|>
  </equation>

  Again the measurements are taken by averaging over independent simulation
  runs in order to reduce autocorrelation effects. Every point of in
  (Fig.<reference|fig:pressure>) is the mean value of 10 independent
  simulation thermalized for a time corresponding to
  <math|5\<cdot\>10<rsup|4>> collisions.

  <big-figure|<image|../hardcore3d/collision_data/img/pressure.eps|0.75par|||>|<label|fig:pressure>Plot
  of <math|<frac|P*V|N*T>-1> as a function of <math|\<eta\>> for a system of
  250 particles. Every measurement is taken form the average of <math|10>
  independent runs each collected after an initial thermalization time of
  <math|5\<cdot\>10<rsup|4>> collisions. \ The errorbars represent the
  standard errors of the averages.>

  For the 3<nbsp>dimensional case at study, we notice a discontinuity of the
  pressure around the value <math|\<eta\>\<sim\>0.5>. Near the transition
  point the measurements are averaged over the two metastable branches of the
  curve, thus forming almost a plateau, which is a typical property of first
  order phase transitions.

  <subsection|Mean Squared Displacement>

  Informations about the phase of the system and about its diffusive/confined
  properties are also found by looking at the mean squared displacement:

  <\equation>
    <label|eq:msd>MSD=<around*|\<langle\>|<around*|(|<wide|r|\<vect\>><rsub|i><around*|(|t|)>-<wide|r|\<vect\>><rsub|i><around*|(|t<rsub|0>|)>|)><rsup|2>|\<rangle\>>=<around*|\<langle\>|\<Delta\><wide|r|\<vect\>><around*|(|t,t<rsub|0>|)><rsup|2>|\<rangle\>>
  </equation>

  which, for a 3<nbsp>dimensional system enclosed in a box with edge
  <math|L=1>, has a plateau at:

  <\equation>
    lim<rsub|\<Delta\>t\<rightarrow\>\<infty\>>MSD<rsub|3d>=<frac|L<rsup|2>|4>=0.25
  </equation>

  <big-figure|<image|../hardcore3d/msd/img/MSD.eps|0.75par|||>|<label|fig:msd>Mean
  squared displacement from a simulation of <math|N=250> particles. The
  measurements are taken for a simulation time <math|t<rsub|S>=50> with a
  time step of <math|0.005> after a thermalization of
  <math|5\<cdot\>10<rsup|4>> collisions. The color palette represents
  different values of <math|\<eta\>>. The solid line in black is the exact
  result for <math|\<Delta\>t\<rightarrow\>\<infty\>>.>

  From the growth of the MSD with time, we note a similar behavior to that of
  the 2<nbsp>dimensional case. This time, though, the discontinuity in the
  rate of change of the coefficient <math|D> with respect to <math|\<eta\>>
  is even more drastic. For <math|\<eta\>\<less\>0.5> the particles have an
  initial diffusive dynamics that becomes confined when the plateau value
  0.25 is reached. Immediately after <math|\<eta\>\<sim\>0.5> the diffusion
  coefficient drops almost to zero and we witness a transition to a solid
  phase of the system where the particles are strongly confined by the small
  space available.

  <\big-figure>
    <image|../hardcore3d/msd/img/trajectory_0.30.eps|0.5par|||><image|../hardcore3d/msd/img/trajectory_0.35.eps|0.5par|||>

    <image|../hardcore3d/msd/img/trajectory_0.40.eps|0.5par|||><image|../hardcore3d/msd/img/trajectory_0.45.eps|0.5par|||>

    <image|../hardcore3d/msd/img/trajectory_0.50.eps|0.5par|||><image|../hardcore3d/msd/img/trajectory_0.55.eps|0.5par|||>
  </big-figure|Points visited by individual particles in a system of
  <math|N=250> total particles, at different values of the packing density
  <math|\<eta\>>. The first five picture represent the typical trajectories
  of diffusion processes such as random walks (liquid phase). In the last
  picture is evident the confining property of the solid phase of the
  system.>

  <subsection|Thermodynamic Limit>

  Finally we study the thermodynamic limit of the pressure by taking several
  measurements at growing values of <math|V> and <math|N> keeping the density
  <math|\<eta\>> fixed (instead of actually scaling the volume <math|V> we
  increase the number of particles and reduce their diameter so that
  <math|\<eta\>=const>).

  \;

  We consider systems with <math|N=32,64,128,256,512> and measure the
  quantity:

  <\equation>
    <frac|P*V|N*k<rsub|b>T>-1=<frac|m*\<sigma\>|2K*t><big|sum><around*|\||\<Delta\><wide|v|\<vect\>><rsub|i*j><rsup|>|\|>
  </equation>

  at the fixed value <math|\<eta\>=0.3>. We then plot the results against
  <math|1/L> and perform a linear fit of the form:

  <\equation>
    y=p<rsub|0>+p<rsub|1>x
  </equation>

  <big-figure|<image|../hardcore3d/thermo_limit/img/TL.eps|0.75par|||>|Plot
  of <math|<frac|P*V|N*k<rsub|b>T>-1> as a funtction of <math|1/L>. Each
  point is taken after thermalization and averaged over 10 independent
  simulation runs. The errors are computed as the standar error on the mean
  values.>

  \ The result of the fit indicates that:

  <\equation>
    lim<rsub|N\<rightarrow\>\<infty\>><frac|P*V|N*k<rsub|b>T>-1=4.4662\<pm\>0.0044
  </equation>
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
    <associate|auto-10|<tuple|1.4|5>>
    <associate|auto-11|<tuple|6|6>>
    <associate|auto-12|<tuple|1.4|8>>
    <associate|auto-13|<tuple|8|8>>
    <associate|auto-14|<tuple|9|9>>
    <associate|auto-15|<tuple|10|9>>
    <associate|auto-16|<tuple|10|9>>
    <associate|auto-17|<tuple|11|11>>
    <associate|auto-18|<tuple|12|12>>
    <associate|auto-19|<tuple|13|12>>
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
    <associate|auto-4|<tuple|2|2>>
    <associate|auto-5|<tuple|1.2|3>>
    <associate|auto-6|<tuple|3|3>>
    <associate|auto-7|<tuple|1.3|4>>
    <associate|auto-8|<tuple|4|4>>
    <associate|auto-9|<tuple|5|5>>
    <associate|cwos|<tuple|3|?>>
    <associate|diffusion|<tuple|11|?>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:betac|<tuple|7|?>>
    <associate|eq:cosh|<tuple|22|10>>
    <associate|eq:diffusion|<tuple|8|10>>
    <associate|eq:msd|<tuple|7|4>>
    <associate|eq:msd0|<tuple|12|10>>
    <associate|eq:plateau|<tuple|13|10>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:temp|<tuple|5|2>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:collision_time|<tuple|6|9>>
    <associate|fig:corr|<tuple|11|10>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:fss|<tuple|13|12>>
    <associate|fig:heatcapacity|<tuple|5|5>>
    <associate|fig:hist1|<tuple|2|2>>
    <associate|fig:hist2|<tuple|3|6>>
    <associate|fig:lattice|<tuple|1|?>>
    <associate|fig:levels|<tuple|8|7>>
    <associate|fig:msd|<tuple|4|4>>
    <associate|fig:msd1|<tuple|5|12>>
    <associate|fig:packing|<tuple|1|2>>
    <associate|fig:pdfMH|<tuple|9|8>>
    <associate|fig:pdfSW|<tuple|13|7>>
    <associate|fig:pressure|<tuple|3|3>>
    <associate|fig:susceptibility|<tuple|5|4>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:therm1|<tuple|1|2>>
    <associate|fig:therm2|<tuple|2|4>>
    <associate|fig:thermalization|<tuple|1|2>>
    <associate|fig:thermalizationMH|<tuple|2|3>>
    <associate|fig:thermalizationSW|<tuple|3|4>>
    <associate|fig:times|<tuple|7|9>>
    <associate|fig:toruseffect|<tuple|1|3>>
    <associate|fig:trajectory|<tuple|6|12>>
    <associate|footnote-1|<tuple|1|11>>
    <associate|footnr-1|<tuple|1|11>>
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
      <tuple|normal|Plot of the thermalization process of an hard-core
      interacting gas of <with|mode|<quote|math>|N=128> particles. On the
      left is the pressure as a function of the number of collisions, while
      on the right is the mean free path of the particles. Different colors
      represent the different values of <with|mode|<quote|math>|\<eta\>=0.25,0.35,0.45,0.55,0.65>
      used for the simulations. |<pageref|auto-3>>

      <\tuple|normal>
        Histogram of the modulus of the momenta for
        <with|mode|<quote|math>|N=128> particles at
        <with|mode|<quote|math>|\<eta\>=0.5>. The measurements are taken
        after <with|mode|<quote|math>|5\<cdot\>10<rsup|4>> collisions from
        the start of the simulation, and after that every
        <with|mode|<quote|math>|500> collisions for a total of
        <with|mode|<quote|math>|10<rsup|4>> datasets each containing the
        momenta of <with|mode|<quote|math>|N> particles.
      </tuple|<pageref|auto-4>>

      <tuple|normal|Plot of <with|mode|<quote|math>|<frac|P*V|N*T>-1> as a
      function of <with|mode|<quote|math>|\<eta\>> for a system of 250
      particles. Every measurement is taken form the average of
      <with|mode|<quote|math>|10> independent runs each collected after an
      initial thermalization time of <with|mode|<quote|math>|5\<cdot\>10<rsup|4>>
      collisions. \ The errorbars represent the standard errors of the
      averages.|<pageref|auto-6>>

      <tuple|normal|Mean squared displacement from a simulation of
      <with|mode|<quote|math>|N=250> particles. The measurements are taken
      for a simulation time <with|mode|<quote|math>|t<rsub|S>=50> with a time
      step of <with|mode|<quote|math>|0.005> after a thermalization of
      <with|mode|<quote|math>|5\<cdot\>10<rsup|4>> collisions. The color
      palette represents different values of
      <with|mode|<quote|math>|\<eta\>>. The solid line in black is the exact
      result for <with|mode|<quote|math>|\<Delta\>t\<rightarrow\>\<infty\>>.|<pageref|auto-8>>

      <tuple|normal|Points visited by individual particles in a system of
      <with|mode|<quote|math>|N=250> total particles, at different values of
      the packing density <with|mode|<quote|math>|\<eta\>>. The first five
      picture represent the typical trajectories of diffusion processes such
      as random walks (liquid phase). In the last picture is evident the
      confining property of the solid phase of the system.|<pageref|auto-9>>

      <tuple|normal|Plot of <with|mode|<quote|math>|<frac|P*V|N*k<rsub|b>T>-1>
      as a funtction of <with|mode|<quote|math>|1/L>. Each point is taken
      after thermalization and averaged over 10 independent simulation runs.
      The errors are computed as the standar error on the mean
      values.|<pageref|auto-11>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Hard-Core
      Molecular Dynamics in <with|mode|<quote|math>|3d>>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Phase Transition
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Mean Squared Displacement
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-7>>

      <with|par-left|<quote|1tab>|1.4<space|2spc>Thermodynamic Limit
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-10>>
    </associate>
  </collection>
</auxiliary>