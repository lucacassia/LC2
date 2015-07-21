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

    <with|par-left|1tab|1.3<space|2spc>Phase Transition
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-9>>

    <with|par-left|1tab|1.4<space|2spc>Collision Times
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-13>>

    <with|par-left|1tab|1.5<space|2spc>Mean Squared Displacement
    <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
    <no-break><pageref|auto-16>>
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
    <label|eq:temp>\<Rightarrow\><space|1em>k<rsub|b>T=<frac|m|d*N>*<big|sum><rsub|i=1><rsup|N><around*|\||<wide|v|\<vect\>><rsub|i>|\|><rsup|2>
  </equation>

  \;

  We now study the mixing properties of this type of system. We evolve a
  system of <math|N=100> particles from its initial configuration, for
  <math|10<rsup|4>> collisions and measure the pressure
  (Fig.<reference|fig:therm1>) and the mean free path
  (Fig.<reference|fig:therm2>) every <math|10> collisions. This procedure is
  also repeated for <math|N=400>.

  <\big-figure>
    <image|../hardcore2d/thermalization/img/thermalization1.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization2.eps|0.5par|||>

    <image|../hardcore2d/thermalization/img/thermalization5.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization6.eps|0.5par|||>
  </big-figure|<label|fig:therm1>Plot of the thermalization process of an
  hard-core interacting gas of <math|N=100> particles. The top two figures
  illustrate the pressure as a function of the number of collisions, while
  the bottom two show the mean free path of the particles. Different colors
  represent the different values of <math|\<eta\>=0.15,0.30,0.45,0.60,0.75>
  used for the simulations. On the right is the same process, after a larger
  number of collisions. The mixing rate of the system (as a function of the
  number of collisions) grows with <math|\<eta\>> and the number of
  particles.>

  <\big-figure>
    <image|../hardcore2d/thermalization/img/thermalization3.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization4.eps|0.5par|||>

    <image|../hardcore2d/thermalization/img/thermalization7.eps|0.5par|||><image|../hardcore2d/thermalization/img/thermalization8.eps|0.5par|||>
  </big-figure|<label|fig:therm2>Plot of the thermalization process of an
  hard-core interacting gas of <math|N=400> particles. The mixing of this
  larger system is much slower.>

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

  \;

  If we work with <math|N=100> particles, we can consider the system
  thermalized after <math|5\<cdot\>10<rsup|5>> collisions.

  <subsection|Momentum Distribution>

  After thermalization is reached, the system acquires time translation
  invariance and the distribution of the momenta of the particles converge to
  the <strong|Maxwell-Boltzmann distribution>:

  <\equation>
    f<around*|(|v|)>=<sqrt|<around*|(|<frac|m|2\<pi\>k<rsub|b>T>|)><rsup|3>>*4\<pi\>*v<rsup|2>*exp<around*|[|<frac|-m*v<rsup|2>|2k<rsub|b>T>|]>
  </equation>

  and for the single components:

  <\equation>
    f<around*|(|v<rsub|i>|)>=<sqrt|<frac|m|2\<pi\>k<rsub|b>T>>*exp<around*|[|<frac|-m*v<rsub|i><rsup|2>|2k<rsub|b>T>|]>
  </equation>

  <\big-figure|<image|../hardcore2d/distribution/img/mdistribution.pdf|0.75par|||>>
    <label|fig:hist1>Histogram of the modulus of the momenta for <math|N=100>
    particles. The measurements are taken after <math|10<rsup|5>> collisions
    from the start of the simulation, and after that every <math|500>
    collisions for a total of <math|10<rsup|4>> datasets each containing the
    momenta of <math|N> particles. The system is initialized at temperatures
    <math|T=1,4,16>.
  </big-figure>

  We repeat the simulation for three different values of the temperature
  (<math|T=1,4,16>) which we set by hand at the beginning. The temperature
  can then be read from a fit of the histograms of
  (Fig.<reference|fig:hist1>) and compared with the one obtained from
  (<reference|eq:temp>):

  \;

  <center|<block*|<tformat|<table|<row|<cell|<math|T>>|<cell|<math|T<rsub|fit>>>>|<row|<cell|<math|1>>|<cell|<math|1.011343\<pm\>0.005696>>>|<row|<cell|<math|4>>|<cell|<math|4.028977\<pm\>0.007747>>>|<row|<cell|<math|16>>|<cell|<math|16.134445\<pm\>0.023048>>>>>>>

  \;

  \;

  We also plot the distribution for the single components <math|v<rsub|x>>
  and <math|v<rsub|y>>:

  <\big-figure>
    <image|../hardcore2d/distribution/img/xdistribution.pdf|0.5par|||><image|../hardcore2d/distribution/img/ydistribution.pdf|0.5par|||>
  <|big-figure>
    <label|fig:hist2>Histograms of the <math|x> (left) and <math|y> (right)
    components of the momenta for <math|N=100> particles.

    \;
  </big-figure>

  <with|font-shape|italic|Remark:> in this section we decide not to use
  adimensional units for time <math|t> and temperature <math|k<rsub|b>T>
  otherwise we would end up with only one distribution with
  <math|k<rsub|b>T=1>. What we do is to set only <math|k<rsub|b>=1>, this way
  we still have the freedom to set the temperature <math|T> by rescaling all
  the momenta (and hence rescale time <math|t> of the right amount in order
  to balance the change in <math|T>). For all the following sections we use
  the rescaling <math|L=1,m=1> and <math|k<rsub|b>T=1> such that:

  <\equation>
    K=<frac|d|2>*N
  </equation>

  <subsection|Phase Transition>

  In this section we study the <math|\<eta\>> dependence of some interesting
  quantities describing the system. First we look at the pressure <math|P> as
  the packing density is increased. For a system such as those in
  consideration, we define the pressure <math|P> using the formula:

  <\equation>
    <frac|P*V|N*k<rsub|b>T>=1+<frac|1|2K*t><big|sum><rsub|c=1><rsup|N<rsub|c>>m*\<sigma\><around*|\||\<Delta\><wide|v|\<vect\>><rsub|i*j><around*|(|t<rsub|c>|)>|\|>
  </equation>

  with <math|m\<Delta\><wide|v|\<vect\>><rsub|i*j><around*|(|t<rsub|c>|)>>
  being the exchanged momentum in the collision taking place at time
  <math|t<rsub|c>>, <math|N<rsub|c>> the total number of collisions and
  <math|t> the runtime of the simulation.

  \;

  <em|Remark:> as a measure against autocorrelation effects we decide to
  sample data each from an independent run and then take the average over all
  runs (at the same <math|\<eta\>>).

  <big-figure|<image|../hardcore2d/collision_data/img/pressure.eps|0.75par|||>|Plot
  of <math|<frac|P*V|N*k<rsub|b>T>-1> as a function of <math|\<eta\>> for a
  system of 100 particles. Every measurement is taken form the average of
  <math|50> independent runs each collected after an initial thermalization
  time of <math|5\<cdot\>10<rsup|5>> collisions. \ The errorbars represent
  the standard errors of the averages.>

  Near <math|\<eta\>=0.7> we observe a first order phase transition
  characterized by a discontinuity in the pressure with respect to the
  thermodynamic variable <math|\<eta\>>. The system is found in a liquid
  phase for values of the density <math|\<eta\>\<less\>0.7> and in a solid
  phase for <math|\<eta\>\<gtr\>0.7>. This kind of phase transition displays
  a plateau region where the transition takes place. In fact there is no well
  defined critical point since multiple phases can coexist near the
  transition.

  \;

  We also note that, since the hard-core potential has no attractive effect
  on the particles, there cannot be a phase transition with respect to the
  temperature. The order-disorder transition we observe is purely of
  geometrical nature.

  \;

  Another thermodynamic quantity that shows discontinuity at the phase
  transition is the mean free path, i.e., the average distance traveled by a
  particle between successive impacts:

  <\equation>
    l<rsub|c>=<big|sum><rsub|c=1><rsup|N<rsup|i><rsub|c>><frac|<around*|\||\<Delta\><wide|r|\<vect\>><rsub|i><around*|(|t<rsub|c>,t<rsub|c-1>|)>|\|>|N<rsup|i><rsub|c>>
  </equation>

  To compute <math|l<rsub|c>>, we save the total distance travelled by every
  particle <math|<big|sum><around*|\||\<Delta\><wide|r|\<vect\>><rsub|i>|\|>\<sim\><big|int><around*|\||d*<wide|r|\<vect\>><rsub|i>|\|>>
  and the total number <math|N<rsup|i><rsub|c>> of collisions it had during
  its path.

  <big-figure|<image|../hardcore2d/collision_data/img/mfp.eps|0.75par|||>|Plot
  of the mean free path against <math|\<eta\>> for <math|N=100>.>

  We also plot the distribution of the mean free path:

  <big-figure|<image|../hardcore2d/mean_free_path/img/mean_free_path.pdf|0.75par|||>|Distribution
  of the mean free path <math|l<rsub|c>> for <math|N=100> and
  <math|\<eta\>=0.30,0.45,0.60,0.75>. The histograms are obtained from a
  sample of <math|10<rsup|6>> measurements and after a thermalization time of
  <math|5\<cdot\>10<rsup|5>> collisions.>

  \;

  <subsection|Collision Times>

  Yet another interesting quantity to look at is the collision time
  <math|t<rsub|c>>, i.e., the time between two consecutive collisions. In
  (Fig.<reference|fig:collision_time>) we present the distribution of
  <math|t<rsub|c>> for increasing values of <math|\<eta\>>:

  <big-figure|<image|../hardcore2d/collision_time/img/collision_time.pdf|0.75par|||>|<label|fig:collision_time>Distribution
  of the collision time <math|t<rsub|c>> for <math|N=100> and
  <math|\<eta\>=0.30,0.45,0.60,0.75>. The histograms are obtained from a
  sample of <math|10<rsup|6>> measurements and after a thermalization time of
  <math|5\<cdot\>10<rsup|5>> collisions.>

  As the density of particles increases, the collisions become more frequent
  because of the decrease in free space available for the particles to freely
  travel. This implies that the distribution of the collision times must
  become narrower for larger values of <math|\<eta\>>
  (Fig.<reference|fig:collision_time>).

  \;

  Similarly to the case of the pressure and the mean free path,
  <math|t<rsub|c>> also has a discontinuity at the phase transition, as we
  can see from (Fig.<reference|fig:times>):

  <big-figure|<image|../hardcore2d/collision_data/img/mct.eps|0.75par|||>|<label|fig:times>Plot
  of the mean collision time <math|<around*|\<langle\>|t<rsub|c>|\<rangle\>>>
  against <math|\<eta\>> for <math|N=100>.>

  <subsection|Mean Squared Displacement>

  The mean squared displacement (MSD), defined as:

  <\equation>
    <label|eq:msd>MSD=<around*|\<langle\>|<around*|(|<wide|r|\<vect\>><rsub|i><around*|(|t|)>-<wide|r|\<vect\>><rsub|i><around*|(|t<rsub|0>|)>|)><rsup|2>|\<rangle\>>=<around*|\<langle\>|\<Delta\><wide|r|\<vect\>><around*|(|t,t<rsub|0>|)><rsup|2>|\<rangle\>>
  </equation>

  is a very common measure of the amount of the system ``explored'' by a
  particle as the time passes. For diffusion precesses (random walks), the
  MSD grows linearly with time:

  <\equation>
    <label|eq:diffusion>MSD\<simeq\>2*d*D*\<Delta\>t<space|3em><text|<em|Einstein's
    relation>>
  </equation>

  where <math|d> is the dimension of the space and <math|D> is the
  self-diffusion constant. Usually one would plot the MSD as a function of
  time and, in the limit of large times, a linear fit of the curve would
  yield the diffusion coefficient of the precess. However, we will see that
  the use of periodic boundary conditions will affect the linearity of
  (<reference|eq:diffusion>). In fact, when a particle travels around a
  closed loop of non trivial homology, the total displacement computed by
  (<reference|eq:msd>) is approximately zero, while actually the particle has
  travelled a distance of the order of the size <math|L> of the system. This
  phenomenon will effectively confine the particle to a finite volume, and as
  a consequence, the MSD will reach a plateau value. It is this plateau value
  that provides the definition of <math|D> for a finite system.

  For large <math|\<Delta\>t> this value can be computed exactly: let
  <math|f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,<wide|r|\<vect\>>,t<rsub|0>,t|)>>
  be the probability of a particle to go from
  <math|<wide|r|\<vect\>><rsub|0>> to <math|<wide|r|\<vect\>>> after a time
  <math|\<Delta\>t=t-t<rsub|0>>, then:

  <\equation>
    <around*|\<langle\>|<around*|(|<wide|r|\<vect\>><rsub|i><around*|(|t|)>-<wide|r|\<vect\>><rsub|i><around*|(|t<rsub|0>|)>|)><rsup|2>|\<rangle\>>=<big|int><rsub|V>d*<wide|r|\<vect\>>*<big|int><rsub|V>d*<wide|r|\<vect\>><rsub|0>
    <around*|(|<wide|r|\<vect\>>-<wide|r|\<vect\>><rsub|0>|)><rsup|2>*f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,<wide|r|\<vect\>>,t<rsub|0>,t|)>
  </equation>

  <\equation>
    f<around*|(|<wide|r|\<vect\>>,t|)>=<big|int><rsub|V>f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,<wide|r|\<vect\>>,t<rsub|0>,t|)>
    d*<wide|r|\<vect\>><rsub|0>,<space|2em>f<around*|(|<wide|r|\<vect\>>,t|)>=<big|int><rsub|V>f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,<wide|r|\<vect\>>,t<rsub|0>,t|)>
    d*<wide|r|\<vect\>><rsub|0>,<space|2em>f<around*|(|<wide|r|\<vect\>><rsub|0>,t<rsub|0>|)>=f<around*|(|<wide|r|\<vect\>>,t|)>=<frac|1|V>
  </equation>

  where the first two equalities are just the definitions of the marginal
  probability distributions and the last is a consequence of spatial and
  temporal homogeneity at thermal equilibrium.

  After a long time has passed, the particle loses every information about
  its past, and the joint probability distribution factorizes:

  <\equation>
    f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,<wide|r|\<vect\>>,t<rsub|0>,t|)><long-arrow|\<rubber-rightarrow\>||\<Delta\>t\<rightarrow\>\<infty\>>f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,t<rsub|0>|)>*f<rsub|i><around*|(|<wide|r|\<vect\>>,t|)>
  </equation>

  \;

  The <math|MSD> can then be computed for large time separations as:

  <\eqnarray>
    <tformat|<table|<row|<cell|<around*|\<langle\>|\<Delta\><wide|r|\<vect\>><around*|(|t,t<rsub|0>|)><rsup|2>|\<rangle\>>>|<cell|=>|<cell|<big|int><rsub|V>d*<wide|r|\<vect\>>*<big|int><rsub|V>d*<wide|r|\<vect\>><rsub|0>
    <around*|(|<wide|r|\<vect\>>-<wide|r|\<vect\>><rsub|0>|)><rsup|2>
    f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,t<rsub|0>|)>*f<rsub|i><around*|(|<wide|r|\<vect\>>,t|)>>>|<row|<cell|>|<cell|=>|<cell|<big|int><rsub|V>d*<wide|r|\<vect\>>*<big|int><rsub|V>d*<wide|r|\<vect\>><rsub|0>
    <around*|(|<around*|\||<wide|r|\<vect\>>|\|><rsup|2>-2*<wide|r|\<vect\>>\<cdot\><wide|r|\<vect\>><rsub|0>+<around*|\||<wide|r|\<vect\>><rsub|0>|\|><rsup|2>|)>
    f<rsub|i><around*|(|<wide|r|\<vect\>><rsub|0>,t<rsub|0>|)>*f<rsub|i><around*|(|<wide|r|\<vect\>>,t|)>>>|<row|<cell|>|<cell|=>|<cell|*<frac|1|V><big|int><rsub|V>d*<wide|r|\<vect\>>
    <around*|\||<wide|r|\<vect\>>|\|><rsup|2>-2*<around*|\<langle\>|<wide|r|\<vect\>><around*|(|t|)>|\<rangle\>>\<cdot\><around*|\<langle\>|<wide|r|\<vect\>><rsub|0><around*|(|t<rsub|0>|)>|\<rangle\>>+<frac|1|V><big|int><rsub|V>d*<wide|r|\<vect\>><rsub|0>
    <around*|\||<wide|r|\<vect\>><rsub|0>|\|><rsup|2>>>|<row|<cell|>|<cell|=>|<cell|<frac|2|V><big|int><rsub|V>d*<wide|r|\<vect\>>
    <around*|\||<wide|r|\<vect\>>|\|><rsup|2><eq-number><label|eq:msd0>>>>>
  </eqnarray>

  Where the factor 2 in the last step, counts both the displacement of
  <math|<wide|r|\<vect\>>> and <math|<wide|r|\<vect\>><rsub|0>>, since they
  are independent. We can fix the inital position of the particle to be 0 for
  convenince and then look only at the displacement with respect to that
  position. This is equivalent to considering only the final position
  contribution, which is half the MSD of (<reference|eq:msd0>).

  \;

  Finally, for a volume <math|V=L<rsup|d>>, we obtain:

  <\eqnarray>
    <tformat|<table|<row|<cell|<around*|\<langle\>|\<Delta\><wide|r|\<vect\>><around*|(|t,t<rsub|0>|)><rsup|2>|\<rangle\>>>|<cell|=>|<cell|<frac|1|V><big|int><rsub|V>d*<wide|r|\<vect\>>
    <around*|\||<wide|r|\<vect\>>|\|><rsup|2>>>|<row|<cell|>|<cell|=>|<cell|<frac|1|L<rsup|d>><big|int><rsup|L/2><rsub|-L/2>d*x<rsub|d>*\<ldots\><big|int><rsup|L/2><rsub|-L/2>d*x<rsub|2><big|int><rsup|L/2><rsub|-L/2>d*x<rsub|1>
    <around*|(|x<rsub|1><rsup|2>+x<rsub|2><rsup|2>+\<ldots\>+x<rsub|d><rsup|2>|)>>>|<row|<cell|>|<cell|=>|<cell|<frac|1|L<rsup|d>>*L<rsup|d-1>*<frac|2*d|3><around*|(|<frac|L|2>|)><rsup|3>=<frac|d|12>*L<rsup|2><long-arrow|\<rubber-rightarrow\>|L=1><choice|<tformat|<table|<row|<cell|1/6,>|<cell|d=2>>|<row|<cell|1/4,>|<cell|d=3>>>>><eq-number><label|eq:plateau>>>>>
  </eqnarray>

  \;

  By using the time translation invariance of the system (at thermalization)
  and the fact that all the particles are identical, we can compute an
  estimate of the MSD by averaging over every time interval
  <math|<around*|[|t,t+\<Delta\>t|]>> and every particle <math|i>:

  <\equation>
    MSD<around*|(|\<Delta\>t|)>=<frac|1|N>*<big|sum><rsup|N><rsub|i=1>*<frac|1|<around*|(|t<rsub|S>-\<Delta\>t-t<rsub|0>+1|)>>*<big|sum><rsup|t<rsub|S>-\<Delta\>t><rsub|t=t<rsub|0>><around*|[|<wide|r|\<vect\>><rsub|i><around*|(|t+\<Delta\>t|)>-<wide|r|\<vect\>><rsub|i><around*|(|t|)>|]><rsup|2>
  </equation>

  with <math|t<rsub|S>> being the time of the simulation.

  \;

  We see from (Fig.<reference|fig:msd>) that initially the curves grow
  linearly with the time separation as one would expect for a diffusive
  process. For larger separations, though, the MSD reaches the plateau of
  (<reference|eq:plateau>) and fluctuate around it. The measurement taken at
  very large displacements (<math|\<Delta\>t\<approx\>t<rsub|S>>) are of
  little significance because of the reduced amount of statistics we can
  callect:

  <\equation*>
    N<rsub|samples><around*|(|\<Delta\>t|)>=<around*|(|t<rsub|S>-\<Delta\>t-t<rsub|0>+1|)><long-arrow|\<rubber-rightarrow\>||t\<sim\>t<rsub|S>>1
  </equation*>

  We can also see the phase transition of the system in the abrupt drop in
  the self-diffusion coefficient of the initial diffusive parts of the
  curves<\footnote>
    As already mentioned in (<reference|eq:diffusion>), the first derivative
    of the MSD with respect to time is proportional to the self-diffusion
    coefficient <math|D>.
  </footnote>.

  <big-figure|<image|../hardcore2d/msd/img/MSD.eps|0.75par|||>|<label|fig:msd>Mean
  squared displacement from a simulation of <math|N=100> particles. The
  measurements are taken for a simulation time <math|t<rsub|S>=20> with a
  time step of <math|0.003> after a thermalization of
  <math|5\<cdot\>10<rsup|5>> collisions. The color palette represents
  different values of <math|\<eta\>>. The solid line in black is the exact
  result for <math|\<Delta\>t\<rightarrow\>\<infty\>>.>

  As <math|\<eta\>> approaches large values, the particles are more and more
  constrained by the increase in occupied volume and are less free to travel
  around (Fig.<reference|fig:trajectory>). As a consequence they resent much
  later of the finite size effect of the system, and continue to diffuse
  linearly with time for much longer (Fig.<reference|fig:msd1>):

  <big-figure|<image|../hardcore2d/msd/img/MSD3.eps|0.5par|||><image|../hardcore2d/msd/img/MSD2.eps|0.5par|||>|<label|fig:msd1>Mean
  squared displacement from a simulation of <math|N=100> particles at
  <math|\<eta\>=0.555> and <math|\<eta\>=0.725>. The measurements are taken
  for a simulation time <math|t<rsub|S>=100> with a time step of <math|0.01>
  after a thermalization of <math|5\<cdot\>10<rsup|5>> collisions.>

  This is intuitively understood by looking at the trajectory on the right of
  (Fig.<reference|fig:trajectory>) and realizing that the particle lives
  mostly in the bulk of the box and that it almost never travels around a
  loop of non trivial homology.

  <big-figure|<image|../hardcore2d/msd/img/trajectory2.eps|0.5par|||><image|../hardcore2d/msd/img/trajectory1.eps|0.5par|||>|<label|fig:trajectory>Trajectory
  of a single particle at <math|\<eta\>=0.555> (left) and
  <math|\<eta\>=0.725> (right) in a system with <math|N=100>. Both
  simulations had a runtime of <math|t<rsub|S>=100> after a thermalization
  time corresponding to <math|5\<cdot\>10<rsup|5>> collisions.>
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
    <associate|auto-10|<tuple|6|7>>
    <associate|auto-11|<tuple|7|8>>
    <associate|auto-12|<tuple|8|8>>
    <associate|auto-13|<tuple|1.4|8>>
    <associate|auto-14|<tuple|9|9>>
    <associate|auto-15|<tuple|10|9>>
    <associate|auto-16|<tuple|1.5|9>>
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
    <associate|auto-4|<tuple|2|3>>
    <associate|auto-5|<tuple|3|4>>
    <associate|auto-6|<tuple|1.2|4>>
    <associate|auto-7|<tuple|4|5>>
    <associate|auto-8|<tuple|5|6>>
    <associate|auto-9|<tuple|1.3|6>>
    <associate|cwos|<tuple|3|?>>
    <associate|diffusion|<tuple|11|?>>
    <associate|eq:MC|<tuple|2|?>>
    <associate|eq:betac|<tuple|7|?>>
    <associate|eq:cosh|<tuple|22|10>>
    <associate|eq:diffusion|<tuple|12|10>>
    <associate|eq:msd|<tuple|11|9>>
    <associate|eq:msd0|<tuple|16|10>>
    <associate|eq:plateau|<tuple|17|10>>
    <associate|eq:scalingtau|<tuple|6|4>>
    <associate|eq:temp|<tuple|5|2>>
    <associate|eq:tint|<tuple|7|3>>
    <associate|fig:autocorrelation1|<tuple|2|3>>
    <associate|fig:autocorrelation2|<tuple|4|5>>
    <associate|fig:autocorrelation_time|<tuple|2|3>>
    <associate|fig:collision_time|<tuple|9|9>>
    <associate|fig:corr|<tuple|11|10>>
    <associate|fig:energy_bin|<tuple|9|9>>
    <associate|fig:fss|<tuple|13|12>>
    <associate|fig:heatcapacity|<tuple|5|5>>
    <associate|fig:hist1|<tuple|4|5>>
    <associate|fig:hist2|<tuple|5|6>>
    <associate|fig:lattice|<tuple|1|?>>
    <associate|fig:levels|<tuple|8|7>>
    <associate|fig:msd|<tuple|11|11>>
    <associate|fig:msd1|<tuple|12|12>>
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
    <associate|fig:times|<tuple|10|9>>
    <associate|fig:toruseffect|<tuple|1|3>>
    <associate|fig:trajectory|<tuple|13|12>>
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
      <tuple|normal|On the left we illustrate the initial spatial
      configuration of a system of <with|mode|<quote|math>|100> particles at
      temperature <with|mode|<quote|math>|T=1> and
      <with|mode|<quote|math>|\<eta\>=0.75>. On the right we show the same
      system after <with|mode|<quote|math>|2\<cdot\>10<rsup|5>> collisions.
      The red disks indicate two particles colliding.|<pageref|auto-3>>

      <tuple|normal|Plot of the thermalization process of an hard-core
      interacting gas of <with|mode|<quote|math>|N=100> particles. The top
      two figures illustrate the pressure as a function of the number of
      collisions, while the bottom two show the mean free path of the
      particles. Different colors represent the different values of
      <with|mode|<quote|math>|\<eta\>=0.15,0.30,0.45,0.60,0.75> used for the
      simulations. On the right is the same process, after a larger number of
      collisions. The mixing rate of the system (as a function of the number
      of collisions) grows with <with|mode|<quote|math>|\<eta\>> and the
      number of particles.|<pageref|auto-4>>

      <tuple|normal|Plot of the thermalization process of an hard-core
      interacting gas of <with|mode|<quote|math>|N=400> particles. The mixing
      of this larger system is much slower.|<pageref|auto-5>>

      <\tuple|normal>
        Histogram of the modulus of the momenta for
        <with|mode|<quote|math>|N=100> particles. The measurements are taken
        after <with|mode|<quote|math>|10<rsup|5>> collisions from the start
        of the simulation, and after that every <with|mode|<quote|math>|500>
        collisions for a total of <with|mode|<quote|math>|10<rsup|4>>
        datasets each containing the momenta of <with|mode|<quote|math>|N>
        particles. The system is initialized at temperatures
        <with|mode|<quote|math>|T=1,4,16>.
      </tuple|<pageref|auto-7>>

      <\tuple|normal>
        Histograms of the <with|mode|<quote|math>|x> (left) and
        <with|mode|<quote|math>|y> (right) components of the momenta for
        <with|mode|<quote|math>|N=100> particles.

        \;
      </tuple|<pageref|auto-8>>

      <tuple|normal|Plot of <with|mode|<quote|math>|<frac|P*V|N*k<rsub|b>T>-1>
      as a function of <with|mode|<quote|math>|\<eta\>> for a system of 100
      particles. Every measurement is taken form the average of
      <with|mode|<quote|math>|50> independent runs each collected after an
      initial thermalization time of <with|mode|<quote|math>|5\<cdot\>10<rsup|5>>
      collisions. \ The errorbars represent the standard errors of the
      averages.|<pageref|auto-10>>

      <tuple|normal|Plot of the mean free path against
      <with|mode|<quote|math>|\<eta\>> for
      <with|mode|<quote|math>|N=100>.|<pageref|auto-11>>

      <tuple|normal|Distribution of the mean free path
      <with|mode|<quote|math>|l<rsub|c>> for <with|mode|<quote|math>|N=100>
      and <with|mode|<quote|math>|\<eta\>=0.30,0.45,0.60,0.75>. The
      histograms are obtained from a sample of
      <with|mode|<quote|math>|10<rsup|6>> measurements and after a
      thermalization time of <with|mode|<quote|math>|5\<cdot\>10<rsup|5>>
      collisions.|<pageref|auto-12>>

      <tuple|normal|Distribution of the collision time
      <with|mode|<quote|math>|t<rsub|c>> for <with|mode|<quote|math>|N=100>
      and <with|mode|<quote|math>|\<eta\>=0.30,0.45,0.60,0.75>. The
      histograms are obtained from a sample of
      <with|mode|<quote|math>|10<rsup|6>> measurements and after a
      thermalization time of <with|mode|<quote|math>|5\<cdot\>10<rsup|5>>
      collisions.|<pageref|auto-14>>

      <tuple|normal|Plot of the mean collision time
      <with|mode|<quote|math>|<around*|\<langle\>|t<rsub|c>|\<rangle\>>>
      against <with|mode|<quote|math>|\<eta\>> for
      <with|mode|<quote|math>|N=100>.|<pageref|auto-15>>

      <tuple|normal|Mean squared displacement from a simulation of
      <with|mode|<quote|math>|N=100> particles. The measurements are taken
      for a simulation time <with|mode|<quote|math>|t<rsub|S>=20> with a time
      step of <with|mode|<quote|math>|0.003> after a thermalization of
      <with|mode|<quote|math>|5\<cdot\>10<rsup|5>> collisions. The color
      palette represents different values of
      <with|mode|<quote|math>|\<eta\>>. The solid line in black is the exact
      result for <with|mode|<quote|math>|\<Delta\>t\<rightarrow\>\<infty\>>.|<pageref|auto-17>>

      <tuple|normal|Mean squared displacement from a simulation of
      <with|mode|<quote|math>|N=100> particles at
      <with|mode|<quote|math>|\<eta\>=0.555> and
      <with|mode|<quote|math>|\<eta\>=0.725>. The measurements are taken for
      a simulation time <with|mode|<quote|math>|t<rsub|S>=100> with a time
      step of <with|mode|<quote|math>|0.01> after a thermalization of
      <with|mode|<quote|math>|5\<cdot\>10<rsup|5>>
      collisions.|<pageref|auto-18>>

      <tuple|normal|Trajectory of a single particle at
      <with|mode|<quote|math>|\<eta\>=0.555> (left) and
      <with|mode|<quote|math>|\<eta\>=0.725> (right) in a system with
      <with|mode|<quote|math>|N=100>. Both simulations had a runtime of
      <with|mode|<quote|math>|t<rsub|S>=100> after a thermalization time
      corresponding to <with|mode|<quote|math>|5\<cdot\>10<rsup|5>>
      collisions.|<pageref|auto-19>>
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

      <with|par-left|<quote|1tab>|1.3<space|2spc>Phase Transition
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-9>>

      <with|par-left|<quote|1tab>|1.4<space|2spc>Collision Times
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-13>>

      <with|par-left|<quote|1tab>|1.5<space|2spc>Mean Squared Displacement
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-16>>
    </associate>
  </collection>
</auxiliary>