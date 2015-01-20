
// QweakSimUserTriggerScintillator_DetectorEvent.cc
// Klaus Hans Grimm
// 2005-12-27

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserTriggerScintillator_DetectorEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserTriggerScintillator_DetectorEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserTriggerScintillator_DetectorEvent::QweakSimUserTriggerScintillator_DetectorEvent() 
{
  SecondaryElectronCount         = 0;
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserTriggerScintillator_DetectorEvent::~QweakSimUserTriggerScintillator_DetectorEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserTriggerScintillator_DetectorEvent::Initialize()
{
    TrackID                        = 0;
    HasBeenHit                     = 0;
    NbOfHits                       = 0;
    GlobalTimeOfHit                = 0.0;
    EdgeEventFlag                  = 0;


    if(SecondaryElectronCount){

      SecElecLocalOriginX.clear();
      SecElecLocalOriginY.clear();
      SecElecLocalOriginZ.clear();

      SecElecLocalMomentumX.clear();
      SecElecLocalMomentumY.clear();
      SecElecLocalMomentumZ.clear();

      SecElecLocalEnergy.clear();
    }

    SecondaryElectronCount = 0;
  
    HitLocalPositionX              = 0.0;
    HitLocalPositionY              = 0.0;
    HitLocalPositionZ              = 0.0;

    HitGlobalPositionX             = 0.0;
    HitGlobalPositionY             = 0.0;
    HitGlobalPositionZ             = 0.0;
    
    OriginVertexPositionX          = 0.0;
    OriginVertexPositionY          = 0.0;
    OriginVertexPositionZ          = 0.0;

    OriginVertexMomentumDirectionX = 0.0;
    OriginVertexMomentumDirectionY = 0.0;
    OriginVertexMomentumDirectionZ = 0.0;
    
    OriginVertexThetaAngle         = 0.0;
    OriginVertexPhiAngle           = 0.0;
    OriginVertexKineticEnergy      = 0.0;
    OriginVertexTotalEnergy        = 0.0; 

    EdgeEventFlag                  = 0;

    GlobalPhiAngle                 = 0.;
    GlobalThetaAngle               = 0.;
    
    ParticleName.clear();
    ParticleType.clear();
    
    DepositedEnergy.clear();
    TotalDepositedEnergy = 0.0;
}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserTriggerScintillator_DetectorEvent::AddSecondaryElectronEvent(Float_t XO, Float_t YO, Float_t ZO,
    Float_t XM, Float_t YM, Float_t ZM,
    Float_t energy)
{
  SecElecLocalOriginX.push_back(XO);
  SecElecLocalOriginY.push_back(YO);
  SecElecLocalOriginZ.push_back(ZO);

  SecElecLocalMomentumX.push_back(XM);
  SecElecLocalMomentumY.push_back(YM);
  SecElecLocalMomentumZ.push_back(ZM);

  SecElecLocalEnergy.push_back(energy);

  SecondaryElectronCount++;
}

