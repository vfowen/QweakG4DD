#include "G4EmStandardPhysics.hh"
#include <vector>

class QweakSimEmStandardPhysics: public G4EmStandardPhysics
{
  public:
    QweakSimEmStandardPhysics(std::vector<double> *asInfo,G4int ver = 0): 
    G4EmStandardPhysics(ver),verbose(ver),asymInfo(asInfo) { };
    virtual ~QweakSimEmStandardPhysics() { };

    virtual void ConstructProcess();

  private:
    G4int verbose;
    std::vector<double> *asymInfo;
};

