//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserCerenkov_DetectorEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:43:04 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserCerenkov_DetectorEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserCerenkov_DetectorEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserCerenkov_DetectorEvent::QweakSimUserCerenkov_DetectorEvent() 
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserCerenkov_DetectorEvent::~QweakSimUserCerenkov_DetectorEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserCerenkov_DetectorEvent::Initialize()
{
    DetectorID.clear();
    TrackID                        = 0;
    HasBeenHit                     = 0;
    NbOfHits                       = 0;
    GlobalTimeOfHit.clear();
    EdgeEventFlag.clear();

    SecPartLocalOriginX.clear();
    SecPartLocalOriginY.clear();
    SecPartLocalOriginZ.clear();

    SecPartLocalMomentumX.clear();
    SecPartLocalMomentumY.clear();
    SecPartLocalMomentumZ.clear();

    SecPartLocalEnergy.clear();
    SecPartLocalType.clear();


    OpticalPhotonCount = 0;
    CerenkovPhotonEnergy.clear();

    SecondaryParticleCount = 0;
    SecondaryElectronCount = 0;
    SecondaryPhotonCount   = 0;  
    SecondaryPositronCount = 0;
  
    HitLocalPositionX.clear();
    HitLocalPositionY.clear();
    HitLocalPositionZ.clear();

    PolarizationX.clear();
    PolarizationY.clear();
    PolarizationZ.clear();
    LongitudinalPolarization.clear();
    TransversePolarization.clear();
    TransversePolarizationX.clear();
    TransversePolarizationY.clear();
    TransversePolarizationZ.clear();
    TransversePolarizationPhiAngle.clear();

    HitLocalExitPositionX.clear();
    HitLocalExitPositionY.clear();
    HitLocalExitPositionZ.clear();

    HitGlobalPositionX.clear();
    HitGlobalPositionY.clear();
    HitGlobalPositionZ.clear();
    
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
    
    LocalMomentumX.clear();
    LocalMomentumY.clear();
    LocalMomentumZ.clear();
    LocalThetaAngle.clear();
    LocalPhiAngle.clear();

    GlobalMomentumX.clear();
    GlobalMomentumY.clear();
    GlobalMomentumZ.clear();
    GlobalThetaAngle.clear();
    GlobalPhiAngle.clear();
    
    EdgeEventFlag.clear();

    ParticleName.clear();
    CreatorProcessName.clear();
    ParticleID.clear();
    ParentID.clear();
    ParticleType.clear();
    
    TotalEnergy.clear();
    KineticEnergy.clear();

}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimUserCerenkov_DetectorEvent::AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
								   Float_t XM, Float_t YM, Float_t ZM,
								   Float_t energy, Int_t type)
{
  SecPartLocalOriginX.push_back(XO);
  SecPartLocalOriginY.push_back(YO);
  SecPartLocalOriginZ.push_back(ZO);
  
  SecPartLocalMomentumX.push_back(XM);
  SecPartLocalMomentumY.push_back(YM);
  SecPartLocalMomentumZ.push_back(ZM);
  
  SecPartLocalEnergy.push_back(energy);
  SecPartLocalType.push_back(type);
 
  if (type == 11)  SecondaryElectronCount++;
  if (type == 22)  SecondaryPhotonCount++;
  if (type == -11) SecondaryPositronCount++;
  SecondaryParticleCount++;  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

