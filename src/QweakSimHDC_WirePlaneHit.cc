//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimHDC_WirePlaneHit.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:39:20 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:39:20 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimHDC_WirePlaneHit.hh"

// geant4 includes
#include "G4Circle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Allocator<QweakSimHDC_WirePlaneHit> QweakSimHDC_WirePlane_HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit()
{
//   G4cout << G4endl << "###### Calling QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit() " << G4endl << G4endl;

  HDCID       = -1;
  wireplaneID = -1;
  time        = 0.;

  originVertexPosition            = G4ThreeVector(0.0,0.0,0.0);
  originVertexMomentumDirection   = G4ThreeVector(0.0,0.0,0.0);
  originVertexKineticEnergy       = 0.;
  originVertexTotalEnergy         = 0.;

  currentKineticEnergy            = 0.;
  currentTotalEnergy              = 0.;

  primaryQ2                       = 0.;
  crossSection                    = 0.;
  crossSectionWeight              = 0.;

  primaryEventNumber              = 0;

//   G4cout << G4endl << "###### Leaving QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit(G4int HDC_id, G4int wireplane_id)
{
//   G4cout << G4endl << "###### Calling QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit(G4int z) " << G4endl << G4endl;

  HDCID       = HDC_id;
  wireplaneID = wireplane_id;
  time        = 0.;

//   G4cout << G4endl << "###### Leaving QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit(G4int z) " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDC_WirePlaneHit::~QweakSimHDC_WirePlaneHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDC_WirePlaneHit::QweakSimHDC_WirePlaneHit(const QweakSimHDC_WirePlaneHit &right)
    : G4VHit() {

//   G4cout << G4endl << "###### Calling QweakSimHDC_WirePlaneHit::(const QweakSimHDC_WirePlaneHit &right) " << G4endl << G4endl;

  HDCID       = right.HDCID;
  wireplaneID = right.wireplaneID;

  worldPos    = right.worldPos;
  localPos    = right.localPos;

  worldMomentum    = right.worldMomentum;
  localMomentum    = right.localMomentum;

  currentKineticEnergy = right.currentKineticEnergy;
  currentTotalEnergy   = right.currentTotalEnergy;

  time        = right.time;
  particleName = right.particleName;
  particleType = right.particleType;
  
  originVertexPosition           = right.originVertexPosition;
  originVertexMomentumDirection  = right.originVertexMomentumDirection;
  originVertexKineticEnergy      = right.originVertexKineticEnergy;

  //primaryQ2          = right.primaryQ2;
  //primaryEventNumber = right.primaryEventNumber;

//   G4cout << G4endl << "###### Leaving QweakSimHDC_WirePlaneHit::(const QweakSimHDC_WirePlaneHit &right) " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const QweakSimHDC_WirePlaneHit& QweakSimHDC_WirePlaneHit::operator=(const QweakSimHDC_WirePlaneHit &right)
{
//   G4cout << G4endl << "###### Calling QweakSimHDC_WirePlaneHit::operator=(const QweakSimHDC_WirePlaneHit &right) " << G4endl << G4endl;

  HDCID       = right.HDCID;
  wireplaneID = right.wireplaneID;

  worldPos    = right.worldPos;
  localPos    = right.localPos;
  worldMomentum    = right.worldMomentum;
  localMomentum    = right.localMomentum;

  currentKineticEnergy = right.currentKineticEnergy;
  currentTotalEnergy   = right.currentTotalEnergy;

  time        = right.time;

  originVertexPosition           = right.originVertexPosition;
  originVertexMomentumDirection  = right.originVertexMomentumDirection;
  originVertexKineticEnergy      = right.originVertexKineticEnergy;

//   G4cout << G4endl << "###### Leaving QweakSimHDC_WirePlaneHit::operator=(const QweakSimHDC_WirePlaneHit &right) " << G4endl << G4endl;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//int QweakSimHDC_WirePlaneHit::operator==(const QweakSimHDC_WirePlaneHit & right ) const
int QweakSimHDC_WirePlaneHit::operator==(const QweakSimHDC_WirePlaneHit & ) const
{
 
//   G4cout << G4endl << "###### Calling/Leaving QweakSimHDC_WirePlaneHit::operator==(const QweakSimHDC_WirePlaneHit &right) " << G4endl << G4endl;

  //return (this==&right) ? 1 : 0;

return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimHDC_WirePlaneHit::Draw()
{
//   G4cout << G4endl << "###### Calling QweakSimHDC_WirePlaneHit::Draw() " << G4endl << G4endl; 

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(worldPos);
    circle.SetScreenSize(0.01);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }

//   G4cout << G4endl << "###### Leaving QweakSimHDC_WirePlaneHit::Draw() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimHDC_WirePlaneHit::Print()
{
//   G4cout << "  HDC[" << HDCID << "] : WirePlane[" << wireplaneID << "] : time " << time/ns
//          << " (nsec) --- local (x,y,z) [cm] " 
// 	 << localPos.x()/cm << ", " 
// 	 << localPos.y()/cm << ", " 
// 	 << localPos.z()/cm << ", " 
// 	 << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimHDC_WirePlaneHit.cc,v $
//      Revision 1.3  2006/05/05 21:39:20  grimm
//      Records now the kinetic and total energy.
//
//      Revision 1.2  2005/12/27 19:10:42  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
