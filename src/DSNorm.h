#ifndef DSNORM_H_
#define DSNORM_H_

#include <distribution/RScalarDist.h>

namespace jags {
namespace jagsmodule {

class DSNorm : public RScalarDist {
 public:
  DSNorm();

  double d(double x, PDFType type, std::vector<double const *> const &par, bool give_log) const;
  double p(double q, std::vector<double const *> const &par, bool lower, bool give_log) const;
  double q(double p, std::vector<double const *> const &par, bool lower, bool log_p) const;
  double r(std::vector<double const *> const &par, RNG *rng) const;

  bool checkParameterValue(std::vector<double const *> const &par) const;
};

}  // namespace jagsmodule
}  // namespace jags

#endif /* DSNORM_H_ */
