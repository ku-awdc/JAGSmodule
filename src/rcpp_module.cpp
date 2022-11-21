#include <Rcpp.h>

#include "DSNorm.h"

template <class RcppModuleClassName>
RcppModuleClassName* invalidate_default_constructor() {
  Rcpp::stop("Default constructor is disabled for this class");
  return 0;
}
#define DISABLE_DEFAULT_CONSTRUCTOR() .factory(invalidate_default_constructor)


double dsnorm(const double x, const double mean, const double sd, const double xi, const bool uselog)
{
  jags::RScalarDist *dist;
  dist = new jags::jagsmodule::DSNorm();
  jags::PDFType pdft = jags::PDF_FULL;
  
	std::vector<const double *> pars;
  pars.push_back(&mean);
  pars.push_back(&sd);
  pars.push_back(&xi);
  
  double value = dist->d(x, pdft, pars, uselog);
  
  delete dist;
  return value;
}


RCPP_MODULE(jags_module){

	using namespace Rcpp;

  function("rcpp_dsnorm", &dsnorm, "Test function");
}

