// 
/**
 
   \file QweakSimCerenkovDetector_PMTHit.cc

   $Revision: 1.3 $	
   $Date: 2005/12/27 19:01:50 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:01:50 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkovDetector_PMTHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Allocator<QweakSimCerenkovDetector_PMTHit> QweakSimCerenkovDetector_PMTHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector_PMTHit::QweakSimCerenkovDetector_PMTHit()
{
  DetectorID          = -1;
  PMTID               = -1;
  currentPhotonEnergy = 0.;
  currentHitTime = 0.;
}

QweakSimCerenkovDetector_PMTHit::QweakSimCerenkovDetector_PMTHit(G4int pmt_id)
{
  PMTID  = pmt_id;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector_PMTHit::~QweakSimCerenkovDetector_PMTHit()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector_PMTHit::QweakSimCerenkovDetector_PMTHit(const QweakSimCerenkovDetector_PMTHit &right)
  : G4VHit() 
{
  DetectorID          = right.DetectorID;
  PMTID               = right.PMTID;
  currentPhotonEnergy = right.currentPhotonEnergy;
  currentHitTime      = right.currentHitTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const QweakSimCerenkovDetector_PMTHit& QweakSimCerenkovDetector_PMTHit::operator=(const QweakSimCerenkovDetector_PMTHit &right)
{
  DetectorID          = right.DetectorID;
  PMTID               = right.PMTID;
  currentPhotonEnergy = right.currentPhotonEnergy;
  currentHitTime      = right.currentHitTime;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int QweakSimCerenkovDetector_PMTHit::operator==(const QweakSimCerenkovDetector_PMTHit & ) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCerenkov_PMTHit.cc,v $



