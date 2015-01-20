//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserVDC_WirePlaneEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:42:29 $

   \author Klaus Hans Grimm   

*/
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserVDC_WirePlaneEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserVDC_WirePlaneEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserVDC_WirePlaneEvent::QweakSimUserVDC_WirePlaneEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserVDC_WirePlaneEvent::~QweakSimUserVDC_WirePlaneEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserVDC_WirePlaneEvent::Initialize()
{
  Clear();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimUserVDC_WirePlaneEvent::Clear(const Option_t*)
{
  NbOfHits = 0;

  PackageID.clear();
  TrackID.clear();
  GlobalTimeOfHit.clear();

  HasBeenHit = 0;

  LocalPositionX.clear();
  LocalPositionY.clear();
  LocalPositionZ.clear();
  GlobalPositionX.clear();
  GlobalPositionY.clear();
  GlobalPositionZ.clear();

  LocalMomentumX.clear();
  LocalMomentumY.clear();
  LocalMomentumZ.clear();
  GlobalMomentumX.clear();
  GlobalMomentumY.clear();
  GlobalMomentumZ.clear();

  OriginVertexPositionX.clear();
  OriginVertexPositionY.clear();
  OriginVertexPositionZ.clear();
  OriginVertexMomentumDirectionX.clear();
  OriginVertexMomentumDirectionY.clear();
  OriginVertexMomentumDirectionZ.clear();
  OriginVertexThetaAngle.clear();
  OriginVertexPhiAngle.clear();
  OriginVertexKineticEnergy.clear();
  OriginVertexTotalEnergy.clear();

  GlobalPhiAngle.clear();
  GlobalThetaAngle.clear();

  ParticleName.clear();
  ParticleType.clear();
  TotalEnergy.clear();
  KineticEnergy.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
