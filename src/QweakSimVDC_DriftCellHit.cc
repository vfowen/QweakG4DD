//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimVDC_DriftCellHit.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:19:31 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:19:31 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDC_DriftCellHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Allocator<QweakSimVDC_DriftCellHit> QweakSimVDC_DriftCellHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellHit::QweakSimVDC_DriftCellHit()
{

  driftCellID      = -1;
  driftCellPlaneID = -1;
  pLogV            = 0;
  time             = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellHit::QweakSimVDC_DriftCellHit(G4int dc_id)
{

  driftCellID      = dc_id;
  driftCellPlaneID = -1;
  time             = 0.;
  pLogV            = 0;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellHit::~QweakSimVDC_DriftCellHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellHit::QweakSimVDC_DriftCellHit(const QweakSimVDC_DriftCellHit &right)
    : G4VHit() {


  driftCellID       = right.driftCellID;
  driftCellPlaneID  = right.driftCellPlaneID;

  cellPos  = right.cellPos;
  cellRot  = right.cellRot;
  pLogV    = right.pLogV;

  worldPos = right.worldPos;
  localPos = right.localPos;
  time     = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;

  dcWidthOnFrame           = right.dcWidthOnFrame;
  dcFullThickness          = right.dcFullThickness;
  dcUPlaneWireAngle        = right.dcUPlaneWireAngle; 
  dcVPlaneWireAngle        = right.dcVPlaneWireAngle; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const QweakSimVDC_DriftCellHit& QweakSimVDC_DriftCellHit::operator=(const QweakSimVDC_DriftCellHit &right)
{

  driftCellID       = right.driftCellID;
  driftCellPlaneID  = right.driftCellPlaneID;

  cellPos  = right.cellPos;
  cellRot  = right.cellRot;
  pLogV    = right.pLogV;

  worldPos = right.worldPos;
  localPos = right.localPos;
  time     = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;

  dcWidthOnFrame           = right.dcWidthOnFrame;
  dcFullThickness          = right.dcFullThickness;
  dcUPlaneWireAngle        = right.dcUPlaneWireAngle; 
  dcVPlaneWireAngle        = right.dcVPlaneWireAngle; 

  return *this;
}

int QweakSimVDC_DriftCellHit::operator==(const QweakSimVDC_DriftCellHit & ) const
{
 
  //return (this==&right) ? 1 : 0;

return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDC_DriftCellHit::Draw()
{

    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if(pVVisManager)
    {
//     // draw small yellow balls for the impact point
//     G4Circle circle(worldPos);
//     circle.SetScreenSize(0.1);
//     circle.SetFillStyle(G4Circle::filled);
//     G4Colour colourHit(0.,0.,1.);  // blue
//     G4VisAttributes attribs(colourHit);
//     circle.SetVisAttributes(attribs);
//     pVVisManager->Draw(circle);


	G4Colour colourCell(1.,1.,1.); //white
	G4VisAttributes attribs(colourCell);

	// draw/overlay a white drift cell for a hit
	G4Transform3D trans(cellRot.inverse(),cellPos);
	const G4VisAttributes* pVA = pLogV->GetVisAttributes();

	if(pVA) attribs = *pVA;
	attribs.SetColour(colourCell);
	attribs.SetForceSolid(true);
	attribs.SetVisibility(true);

	pVVisManager->Draw(*pLogV,attribs,trans);

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDC_DriftCellHit::Print()
{
//   G4cout << " DriftCell Plane: " << driftCellPlaneID << " , "
// 	 << " DriftCell[" << driftCellID << "] : time " << time/ns
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
//      $Log: QweakSimVDC_DriftCellHit.cc,v $
//      Revision 1.2  2005/12/27 19:19:31  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

