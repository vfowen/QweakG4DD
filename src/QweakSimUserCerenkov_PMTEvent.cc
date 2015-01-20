/**
 
   \file QweakSimUserCerenkov_PMTEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:16:56 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserCerenkov_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserCerenkov_PMTEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserCerenkov_PMTEvent::Initialize()
{
  PMTHasBeenHit.clear();

  PMTTimeOfHits.clear();
  PMTOctantOfHits.clear();

  PMTLeftNbOfHits.clear();
  PMTRightNbOfHits.clear();
  PMTTotalNbOfHits.clear();
  PMTLeftNbOfPEs.clear();
  PMTRightNbOfPEs.clear();
  PMTTotalNbOfPEs.clear();

  PMTLeftRate.clear();
  PMTRightRate.clear();
  PMTTotalRate.clear();
  PMTLeftRateEL.clear();
  PMTRightRateEL.clear();
  PMTTotalRateEL.clear();
  PMTLeftRateDIS.clear();
  PMTRightRateDIS.clear();
  PMTTotalRateDIS.clear();
  PMTLeftRateQE.clear();
  PMTRightRateQE.clear();
  PMTTotalRateQE.clear();
  PMTLeftRateELPeak.clear();
  PMTRightRateELPeak.clear();
  PMTTotalRateELPeak.clear();
  
  PMTLeftYield.clear();
  PMTRightYield.clear();
  PMTTotalYield.clear();
  PMTLeftYieldEL.clear();
  PMTRightYieldEL.clear();
  PMTTotalYieldEL.clear();
  PMTLeftYieldDIS.clear();
  PMTRightYieldDIS.clear();
  PMTTotalYieldDIS.clear();
  PMTLeftYieldQE.clear();
  PMTRightYieldQE.clear();
  PMTTotalYieldQE.clear();
  PMTLeftYieldELPeak.clear();
  PMTRightYieldELPeak.clear();
  PMTTotalYieldELPeak.clear();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
