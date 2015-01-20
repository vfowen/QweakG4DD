//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserPrimaryEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:18:05 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
// Structure of subtree withtin Root ntuple: 
//  Info saved of primary event
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#include "QweakSimUserPrimaryEvent.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserPrimaryEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserPrimaryEvent::QweakSimUserPrimaryEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserPrimaryEvent::~QweakSimUserPrimaryEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserPrimaryEvent::Initialize()
{
  RandomSeed                     = "";

  TrackID                        = 0;
  GlobalTime                     = 0.0;

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

  OriginVertexKinematicNu        = 0.0;
  OriginVertexKinematicQ2        = 0.0;
  OriginVertexKinematicX         = 0.0;
  OriginVertexKinematicW         = 0.0;

  BeamEnergy                     = 0.0;

  EffectiveKinematicNu           = 0.0;
  EffectiveKinematicQ2           = 0.0;
  EffectiveKinematicX            = 0.0;
  EffectiveKinematicW            = 0.0;

  PrimaryQ2                      = 0.0;
  CrossSection                   = 0.0;
  CrossSectionWeight             = 0.0;
  CrossSectionBornTotal          = 0.0;
  CrossSectionBornInelastic      = 0.0;
  CrossSectionBornQE             = 0.0;
  CrossSectionRadTotal           = 0.0;
  CrossSectionRadElastic         = 0.0;
  CrossSectionRadQE              = 0.0;
  CrossSectionRadDIS             = 0.0;
  CrossSectionRadTotalIntOnly    = 0.0;
  CrossSectionRadElasticIntOnly  = 0.0;
  CrossSectionRadQEIntOnly       = 0.0;
  CrossSectionRadDISIntOnly      = 0.0;
  CrossSectionRadElasticPeak     = 0.0;
  Asymmetry                      = 0.0;

  PDGcode                        = 0;

  ReactionType                   = 1;   // assume elastic as default
  ReactionRegion                 = 1;   // assume LH2 cell interior by default

  // clear Eloss variables
  dEIonIn= dEIonOut=dEIonTot=0;
  dEBremIn= dEBremOut= dEBremTot=0;
  dEMscIn= dEMscOut= dEMscTot=0;
  dETotIn= dETotOut= dETot=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

