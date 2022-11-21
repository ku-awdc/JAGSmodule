#include <module/Module.h>
#include <function/DFunction.h>
#include <function/PFunction.h>
#include <function/QFunction.h>

#include "DSNorm.h"

using std::vector;

namespace jags {
namespace jagsmodule {

	class JagsModule : public Module {
	  public:
	    JagsModule();
	    ~JagsModule();

		void Rinsert(RScalarDist *dist);
	};

JagsModule::JagsModule() : Module("JAGSmodule")
{
  // For functions or scalar/vector distributions:
  // insert(new DSNorm);

  // For distributions using d/p/q/r:
  Rinsert(new DSNorm);
}

void JagsModule::Rinsert(RScalarDist *dist)
{
	insert(dist);
	insert(new DFunction(dist));
	insert(new PFunction(dist));
	insert(new QFunction(dist));
}

JagsModule::~JagsModule()
{
  vector<Function*> const &fvec = functions();
  for (unsigned int i = 0; i < fvec.size(); ++i) {
    delete fvec[i];
  }
  vector<Distribution*> const &dvec = distributions();
  for (unsigned int i = 0; i < dvec.size(); ++i) {
    delete dvec[i];
  }
}

}  // namespace jagsmodule
}  // namespace jags

jags::jagsmodule::JagsModule _jags_module;
