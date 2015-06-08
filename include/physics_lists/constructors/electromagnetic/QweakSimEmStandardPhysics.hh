#include "G4EmStandardPhysics.hh"

class QweakSimEmStandardPhysics: public G4EmStandardPhysics
{
  public:
    QweakSimEmStandardPhysics(G4int ver = 0): G4EmStandardPhysics(ver),verbose(ver) { };
    virtual ~QweakSimEmStandardPhysics() { };

    virtual void ConstructProcess();

  private:
    G4int verbose;
};

