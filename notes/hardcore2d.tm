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
    Molecular Dynamics in <with|mode|math|2d>>
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-1><vspace|0.5fn>

    <with|par-left|1tab|1.1<space|2spc>Thermalization
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-2>>

    <with|par-left|1tab|1.2<space|2spc>Momentum Distribution
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-6>>
  </table-of-contents>

  <section|Hard-Core Molecular Dynamics in <math|2d>>

  In this section we simulate the dynamics of a system of <math|N> identical
  spherical particles in two dimensions, subject to the hard-core central
  potential:

  <\equation>
    V<around*|(|r|)>=<choice|<tformat|<table|<row|<cell|0>|<cell|r\<gtr\>R>>|<row|<cell|\<infty\>>|<cell|r\<leq\>R>>>>>
  </equation>

  with <math|\<sigma\>=2R> being the diameter of the particles. For
  convenience we decide to work with adimensional quantities and rescale all
  lengths by the size <math|L> of the box. In these units the volume of the
  box itself is rescaled to 1. For the same reason we take the mass of the
  particles to be the reference unit of mass. Periodic boundary conditions in
  both directions are implemented in order to reduce boundary effects due to
  the finite size of the system. This turns our box in a toroidal surface.

  <subsection|Thermalization>

  First we initialize the system positioning the particles (disks) on the
  sites of a regular square lattice as in (Fig.<reference|fig:packing>). This
  type of circle packing has a <em|packing density> <math|\<eta\>> (i.e., the
  proportion of the surface covered by the circles) of:

  <\equation>
    \<eta\>=<frac|N*\<pi\>*\<sigma\><rsup|2>|4L<rsup|2>>
  </equation>

  which takes its maximum value for <math|\<sigma\>=L/<sqrt|N>>:

  <\equation>
    \<eta\><rsub|max>=<frac|\<pi\>|4>\<approx\>0.78539816339\<ldots\>
  </equation>

  The highest-density lattice arrangement of circles in the plane is actually
  the hexagonal packing arrangement, with a maximal packing density of
  <math|\<eta\><rsub|h>=<frac|\<pi\>|2<sqrt|3>>\<approx\>0.9069>. In fact we
  see that, a system with large <math|\<eta\>>, spontaneously tends to
  arrange itself in such a way (Fig.<reference|fig:packing>).

  \ 

  <big-figure|<image|../hardcore2d/thermalization/img/pack1.ppm|0.45par|||><space|2em><image|../hardcore2d/thermalization/img/pack2.ppm|0.45par|||>|<label|fig:packing>On
  the left we illustrate the initial spatial configuration of a system of
  <math|100> particles at temperature <math|T=1> and <math|\<eta\>=0.75>. On
  the right we show the same system after <math|2\<cdot\>10<rsup|5>>
  collisions. The red disks indicate two particles colliding.>

  The momenta of the particles are initializated with uniform distribution
  inside the range <math|<around*|[|-1,1|]>> with total momentum equal to
  zero (center of mass reference frame). After the initialization the momenta
  are rescaled in order to obtain the desired temperature. Kinetic energy and
  temperature are related by:

  <\equation>
    K=<frac|d|2>*N*k<rsub|b>*T,<space|1em>K=<frac|1|2>*m*<big|sum><rsub|i=1><rsup|N><around*|\||<wide|v|\<vect\>><rsub|i>|\|><rsup|2>
  </equation>

  <\equation>
    <label|eq:temp>\<Rightarrow\><space|1em>T=<frac|1|d*N>*<big|sum><rsub|i=1><rsup|N><around*|\||<wide|v|\<vect\>><rsub|i>|\|><rsup|2>
  </equation>

  where we set <math|k<rsub|b>=1=m>.

  \;

  We now study the mixing properties of this type of system. We evolve a
  system of <math|N=100> particles from its initial configuration, for
  <math|10<rsup|4>> collisions and measure the pressure
  (Fig.<reference|fig:therm1>) and the mean free path
  (Fig.<reference|fig:therm2>) every <math|10> collisions. This procedure is
  also repeated for <math|N=400>.

  <\big-figure>
    <image|../hardcore2d/thermalization/img/thermalization1.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization2.eps|0.5par|||>
  </big-figure|<label|fig:therm1>Plot of the pressure of an hard-core
  interacting gas of <math|N=100> particles on the left, and <math|N=400> on
  the right. The various colors of the curves represent the value of
  <math|\<eta\>> of the simulation. The mixing rate of the system (as a
  function of the number of collisions) grows with <math|\<eta\>> and the
  number of particles.>

  <big-figure|<image|../hardcore2d/thermalization/img/thermalization3.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization4.eps|0.5par|||>|<label|fig:therm2>Plot
  of the mean free path of an hard-core interacting gas of <math|N=100>
  particles on the left, and <math|N=400> on the right.>

  A many-body system reaches thermalization only when every particle has
  interacted with every other particle at least once. Since hard-core
  particles interact only when they collide with each other, the mixing of
  this type of systems depends only on the number of collisions and not
  directly on the elapsed time.

  \;

  We see that larger systems (system with a large number of particles) need
  more collisions to mix completely, expecially at high densities
  <math|\<eta\>>, while smaller systems mix faster. At high densities we also
  note a peak in the pressure curve near the start of the simulation. This is
  due to the fact that we used an initial arrangement not ideal for the close
  packing of particles. The particles are initially very close to each other
  and interact frequently, but after a few collisions they rearrange in such
  a way as to maximize the distance between them, therefore reducing the
  pressure (Fig.<reference|fig:packing>).

  <subsection|Momentum Distribution>

  After thermalization is reached, the system acquires time translation
  invariance and the distribution of the momenta of the particles converge to
  the Boltzmann distribution:

  <\equation>
    f<around*|(|v|)>=<sqrt|<around*|(|<frac|m|2\<pi\>k<rsub|b>T>|)><rsup|3>>*4\<pi\>*v<rsup|2>*exp<around*|[|<frac|-m*v<rsup|2>|2k<rsub|b>T>|]>
  </equation>

  and for the single components:

  <\equation>
    f<around*|(|v<rsub|i>|)>=<sqrt|<frac|m|2\<pi\>k<rsub|b>T>>*exp<around*|[|<frac|-m*v<rsub|i><rsup|2>|2k<rsub|b>T>|]>
  </equation>

  <\big-figure|<image|../hardcore2d/distribution/img/mdistribution.pdf|0.5par|||>>
    <label|fig:hist1>Histogram of the module of the momenta for <math|N=100>
    particles. The measurements are taken after <math|10<rsup|5>> collisions
    from the start of the simulation, and after that every <math|500>
    collisions for a total of <math|10<rsup|4>> datasets each containing the
    momenta of <math|N> particles. The system is initialized at temperatures
    <math|T=1,4,16>.
  </big-figure>

  We repeat the simulation for three different values of the temperature
  (<math|T=1,4,16>) which we set by hand at the beginning. The temperature
  can now be read from a fit of the histograms of (Fig.<reference|fig:hist1>)
  and compared with the one obtained from (<reference|eq:temp>):

  \;

  <center|<block*|<tformat|<table|<row|<cell|<math|T>>|<cell|<math|T<rsub|fit>>>>|<row|<cell|<math|1>>|<cell|<math|1.011343\<pm\>0.005696>>>|<row|<cell|<math|4>>|<cell|<math|4.028977\<pm\>0.007747>>>|<row|<cell|<math|16>>|<cell|<math|16.134445\<pm\>0.023048>>>>>>>

  \;

  \;

  <\big-figure>
    <image|../hardcore2d/distribution/img/xdistribution.pdf|0.5par|||><image|../hardcore2d/distribution/img/ydistribution.pdf|0.5par|||>
  <|big-figure>
    <label|fig:hist1>Histograms of the <math|x> and <math|y> components of
    the momenta for <math|N=100> particles.

    \;
  </big-figure>

  <subsection|Phase Transition>

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
    <associate|auto-4|<tuple|2|2>>
    <associate|auto-5|<tuple|3|3>>
    <associate|auto-6|<tuple|1.2|3>>
    <associate|auto-7|<tuple|4|3>>
    <associate|auto-8|<tuple|5|4>>
    <associate|auto-9|<tuple|1.3|4>>
    <associate|cwos|<tuple|3|?>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:betac|<tuple|7|?>>
    <associate|eq:cosh|<tuple|22|10>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:temp|<tuple|5|?>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:corr|<tuple|11|10>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:fss|<tuple|13|12>>
    <associate|fig:heatcapacity|<tuple|5|5>>
    <associate|fig:hist1|<tuple|5|?>>
    <associate|fig:lattice|<tuple|1|?>>
    <associate|fig:levels|<tuple|8|7>>
    <associate|fig:packing|<tuple|1|2>>
    <associate|fig:pdfMH|<tuple|9|8>>
    <associate|fig:pdfSW|<tuple|13|7>>
    <associate|fig:susceptibility|<tuple|5|4>>
    <associate|fig:termalization|<tuple|1|2>>
    <associate|fig:termalizationMH|<tuple|1|?>>
    <associate|fig:therm1|<tuple|2|?>>
    <associate|fig:therm2|<tuple|3|?>>
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
      <tuple|normal|On the left we illustrate the initial spatial
      configuration of a system of <with|mode|<quote|math>|100> particles at
      temperature <with|mode|<quote|math>|T=1> and
      <with|mode|<quote|math>|\<eta\>=0.75>. On the right we show the same
      system after <with|mode|<quote|math>|2\<cdot\>10<rsup|5>> collisions.
      The red disks indicate two particles colliding.|<pageref|auto-3>>

      <tuple|normal|Plot of the pressure of an hard-core interacting gas of
      <with|mode|<quote|math>|N=100> particles on the left, and
      <with|mode|<quote|math>|N=400> on the right. The various colors of the
      curves represent the value of <with|mode|<quote|math>|\<eta\>> of the
      simulation. The mixing rate of the system (as a function of the number
      of collisions) grows with <with|mode|<quote|math>|\<eta\>> and the
      number of particles.|<pageref|auto-4>>

      <tuple|normal|Plot of the mean free path of an hard-core interacting
      gas of <with|mode|<quote|math>|N=100> particles on the left, and
      <with|mode|<quote|math>|N=400> on the right.|<pageref|auto-5>>

      <\tuple|normal>
        \;

        \;
      </tuple|<pageref|auto-7>>

      <\tuple|normal>
        \;
      </tuple|<pageref|auto-8>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Hard-Core
      Molecular Dynamics in <with|mode|<quote|math>|2d>>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Thermalization
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Momentum Distribution
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-6>>
    </associate>
  </collection>
</auxiliary>