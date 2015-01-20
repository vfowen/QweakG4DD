
// QweakSimPMTOnly_PMTHit.cc
// Martin McHugh
// 2013-08-01

#include "QweakSimPMTOnly_PMTHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Allocator<QweakSimPMTOnly_PMTHit> QweakSimPMTOnly_PMTHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPMTOnly_PMTHit::QweakSimPMTOnly_PMTHit()
{
  myHitID = 0;
  currentPhotonEnergy = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPMTOnly_PMTHit::~QweakSimPMTOnly_PMTHit()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPMTOnly_PMTHit::QweakSimPMTOnly_PMTHit(const QweakSimPMTOnly_PMTHit &right)
  : G4VHit() 
{
  currentPhotonEnergy = right.currentPhotonEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const QweakSimPMTOnly_PMTHit& QweakSimPMTOnly_PMTHit::operator=(const QweakSimPMTOnly_PMTHit &right)
{
  currentPhotonEnergy = right.currentPhotonEnergy;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int QweakSimPMTOnly_PMTHit::operator==(const QweakSimPMTOnly_PMTHit & ) const
{
  return 0;
}


