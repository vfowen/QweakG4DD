#include "G4EmLivermorePhysics.hh"
#include <vector>

class QweakSimEmLivermorePhysics: public G4EmLivermorePhysics
{
  public:
    QweakSimEmLivermorePhysics(G4int ver, std::vector<double> *asInfo): 
    G4EmLivermorePhysics(ver),verbose(ver),asymInfo(asInfo) { };
    virtual ~QweakSimEmLivermorePhysics() { };

    virtual void ConstructProcess() { };

  private:
    G4int verbose;
    std::vector<double> *asymInfo;
};

