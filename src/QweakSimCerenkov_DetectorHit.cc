//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/**
 
   \file QweakSimCerenkov_DetectorHit.cc

   $Revision: 1.3 $	
   $Date: 2005/12/27 19:01:50 $

   \author Klaus Hans Grimm   

*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkov_DetectorHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Allocator<QweakSimCerenkov_DetectorHit> QweakSimCerenkovDetectorHitAllocator;

QweakSimCerenkov_DetectorHit::QweakSimCerenkov_DetectorHit()
{
  DetectorID  = -1;
  pLogV       = 0;
  time        = 0.;

  originVertexPosition            = G4ThreeVector(0.0,0.0,0.0);
  originVertexMomentumDirection   = G4ThreeVector(0.0,0.0,0.0);
  originVertexKineticEnergy       = 0.;
  originVertexTotalEnergy         = 0.;

  currentMomentumDirection        = G4ThreeVector(0.0,0.0,0.0);
  currentKineticEnergy            = 0.;
  currentTotalEnergy              = 0.;
  currentPolarization             = G4ThreeVector(0.0,0.0,0.0);

  primaryQ2                       = 0.;
  crossSection                    = 0.;
  crossSectionWeight              = 0.;

  particleName                    = "None";
  CreatorProcessName              = "None";
  TrackID                         = -1;
  ParentID                        = -1;
  particleType                    = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_DetectorHit::QweakSimCerenkov_DetectorHit(G4int detector_id)
{

  DetectorID      = detector_id;
  time = 0.;
  pLogV = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_DetectorHit::~QweakSimCerenkov_DetectorHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_DetectorHit::QweakSimCerenkov_DetectorHit(const QweakSimCerenkov_DetectorHit &right)
    : G4VHit() {

  DetectorID       = right.DetectorID;

  cellPos  = right.cellPos;
  cellRot  = right.cellRot;
  pLogV    = right.pLogV;

  worldPos = right.worldPos;
  localPos = right.localPos;
  worldMomentum    = right.worldMomentum;
  localMomentum    = right.localMomentum;

  time     = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;
  originVertexTotalEnergy       = right.originVertexTotalEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;
  currentPolarization      = right.currentPolarization;

  particleName             = right.particleName;
  CreatorProcessName       = right.CreatorProcessName;
  particleType             = right.particleType;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const QweakSimCerenkov_DetectorHit& QweakSimCerenkov_DetectorHit::operator=(const QweakSimCerenkov_DetectorHit &right)
{
  DetectorID       = right.DetectorID;

  cellPos  = right.cellPos;
  cellRot  = right.cellRot;
  pLogV    = right.pLogV;

  worldPos = right.worldPos;
  localPos = right.localPos;
  worldMomentum    = right.worldMomentum;
  localMomentum    = right.localMomentum;
  time     = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;
  originVertexTotalEnergy       = right.originVertexTotalEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;
  currentPolarization      = right.currentPolarization;

  particleName             = right.particleName;
  CreatorProcessName       = right.CreatorProcessName;
  particleType             = right.particleType;
  
  return *this;
}

int QweakSimCerenkov_DetectorHit::operator==(const QweakSimCerenkov_DetectorHit & ) const
{
  //return (this==&right) ? 1 : 0;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkov_DetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    // draw small yellow balls for the impact point
//     G4Circle circle(worldPos);
//     circle.SetScreenSize(0.01);
//     circle.SetFillStyle(G4Circle::filled);
//     G4Colour colourHit(1.,1.,0.);  // yellow
//     G4VisAttributes attribs(colourHit);
//     circle.SetVisAttributes(attribs);
//     pVVisManager->Draw(circle);

//     // draw/overlay a white drift cell for a hit
//     G4Transform3D trans(cellRot.inverse(),cellPos);
//     const G4VisAttributes* pVA = pLogV->GetVisAttributes();
//     if(pVA) attribs = *pVA;
//     G4Colour colourCell(1.,1.,1.);
//     attribs.SetColour(colourCell);
//     attribs.SetForceSolid(true);
//     attribs.SetVisibility(true);
//     pVVisManager->Draw(*pLogV,attribs,trans);

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkov_DetectorHit::Print()
{
  G4cout << " CerenkovDetector[" << DetectorID << "] : time " << time/ns
         << " (nsec) --- local (x,y,z) [cm] " 
	 << localPos.x()/cm << ", " 
	 << localPos.y()/cm << ", " 
	 << localPos.z()/cm << ", " 
	 << "--- world (x,y,z) [cm] "
	 << worldPos.x()/cm << ", " 
	 << worldPos.y()/cm << ", " 
	 << worldPos.z()/cm << ", "
	 << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
