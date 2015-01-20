
// QweakSimUserPMTOnly_PMTEvent.hh
// Martin McHugh
// 2013-08-01

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserPMTOnly_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserPMTOnly_PMTEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserPMTOnly_PMTEvent::QweakSimUserPMTOnly_PMTEvent() 
{
    Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserPMTOnly_PMTEvent::~QweakSimUserPMTOnly_PMTEvent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserPMTOnly_PMTEvent::Initialize()
{
  PMTHasBeenHit = 0;
  PMTTotalNbOfHits = 0;
  PMTTotalNbOfPEs = 0.0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

