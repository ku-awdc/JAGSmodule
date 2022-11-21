#include "DSNorm.h"
#include <util/nainf.h>
#include <rng/RNG.h>

#include <cmath>
#include <cfloat>

#include <Rcpp.h>

using std::vector;
using std::exp;
using std::log;
using std::pow;

#define ALPHA(par) (*par[0])

#define MEAN(par) (*par[0])
#define SIGMA(par) (*par[1])
#define XI(par) (*par[2])

namespace jags {
namespace jagsmodule {

DSNorm::DSNorm()
    : RScalarDist("dsnorm", 3, DIST_POSITIVE)
{}

double DSNorm::d(double x, PDFType type, vector<double const *> const &par, bool give_log) const
{

  const double mean = MEAN(par);
  const double sd = SIGMA(par);
  const double xi = XI(par);

  if(xi == 0.0)
  {
    return R::dnorm(x, mean, sd, give_log);
  }

  x = (x-mean)/sd;

  const double m1 = 2.0 / std::sqrt(2.0 * M_PI);
  const double mu = m1 * (xi - 1.0/xi);
  const double sigma = std::sqrt((1.0-std::pow(m1,2))*(std::pow(xi,2)+1.0/std::pow(xi,2)) + 2.0*std::pow(m1,2) - 1.0);
  const double z = x*sigma + mu;

  double Xi;
  if(z == 0.0)
  {
    Xi = 1.0;
  }
  else if(z > 0.0)
  {
    Xi = xi;
  }
  else
  {
    Xi = 1.0 / xi;
  }


  double g = 2.0 / (xi + 1.0/xi);
  double density = g * R::dnorm(z/Xi, 0.0, 1.0, false) * sigma;

  double result = density / sd;

  return give_log ? log(result) : result;
/*
# Standardize:
m1 = 2/sqrt(2*pi)
mu = m1 * (xi - 1/xi)
sigma = sqrt((1-m1^2)*(xi^2+1/xi^2) + 2*m1^2 - 1)
z = x*sigma + mu
# Compute:
Xi = xi^sign(z)
g = 2 / (xi + 1/xi)
Density = g * dnorm(x = z/Xi)
# Return Value:
Density * sigma
  */

  // result = .dsnorm(x = (x-mean)/sd, xi = xi) / sd

  /*
  double alpha = ALPHA(par);
  double sigma = SIGMA(par);

  if (x < 0)
    return give_log ? JAGS_NEGINF : 0;

  if (give_log)
  	return (log(alpha) - log(sigma)) + ((alpha+1)*log(sigma) - (alpha+1)*log(x + sigma));
  else
    return alpha/sigma * pow((1 + x/sigma),-(alpha + 1));
  */
}

double DSNorm::p(double q, vector<double const *> const &par, bool lower, bool give_log) const
{
  const double mean = MEAN(par);
  const double sd = SIGMA(par);
  const double xi = XI(par);

  // TODO: fix
  return R::pnorm(q, mean, sd, lower, give_log);
}

double DSNorm::q(double p, vector<double const *> const &par, bool lower, bool log_p) const
{
    if ( (log_p  && p > 0) || (!log_p && (p < 0 || p > 1)) )
	return JAGS_NAN;

    const double mean = MEAN(par);
    const double sd = SIGMA(par);
    const double xi = XI(par);

    // TODO: fix
    return R::qnorm(p, mean, sd, lower, log_p);
}

double DSNorm::r(vector<double const *> const &par, RNG *rng) const
{
    return q(rng->uniform(), par, false, false);
}

bool DSNorm::checkParameterValue (vector<double const *> const &par) const
{
  return (SIGMA(par) > 0);
}

}  // namespace jagsmodule
}  // namespace jags
