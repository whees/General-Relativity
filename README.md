# General-Relativity
This program constructs a metric tensor from 10 independant 4-variable functions.  So far, functionality is limited to the numerical calculation of  Christoffel's 3-index symbols, and the Riemann-Christoffel tensor (prone to singularities when certain coordinates are equal to zero).
The ultimate goal of this project is to create an engine capable of numerically solving for geodesics in a space defined by any given metric.
Metrics are defined by populating a 4 by 4 array of pointers to 4-variable functions (representing members of the metric tensor) then feeding it to the metric constructor.
Singularities result from coordinates that make the determinate of the covariant metric tensor equal to zero. Since this program is number based, not symbol based, a result like 
(r^2 / r) would be indeterminate at zero. However, by symbolically analyzing this expression, we see that if we cancel out a factor of r we can obtain the limit of this expression
as it approaches zero, which in the previous example is zero. In order to circumvent this difficulty, a numerical implimentation of L'Hopitals principle must be developed, which I am currently working on.

