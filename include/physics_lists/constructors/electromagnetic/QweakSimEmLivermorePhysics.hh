#include "G4EmLivermorePhysics.hh"

class QweakSimEmLivermorePhysics: public G4EmLivermorePhysics
{
  public:
    QweakSimEmLivermorePhysics(G4int ver = 0): G4EmLivermorePhysics(ver),verbose(ver) { };
    virtual ~QweakSimEmLivermorePhysics() { };

    virtual void ConstructProcess();

  private:
    G4int verbose;
};

