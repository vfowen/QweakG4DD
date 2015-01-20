//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserGEM_WirePlaneEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:51:16 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:51:16 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserGEM_WirePlaneEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserGEM_WirePlaneEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserGEM_WirePlaneEvent::QweakSimUserGEM_WirePlaneEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserGEM_WirePlaneEvent::~QweakSimUserGEM_WirePlaneEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserGEM_WirePlaneEvent::Initialize()
{
  Clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserGEM_WirePlaneEvent::Clear(const Option_t*)
{
  NbOfHits = 0;

  TrackID.clear();
  GlobalTimeOfHit.clear();

  PlaneHasBeenHit = 0;

  PlaneLocalPositionX.clear();
  PlaneLocalPositionY.clear();
  PlaneLocalPositionZ.clear();

  PlaneGlobalPositionX.clear();
  PlaneGlobalPositionY.clear();
  PlaneGlobalPositionZ.clear();

  PlaneLocalMomentumX.clear();
  PlaneLocalMomentumY.clear();
  PlaneLocalMomentumZ.clear();

  PlaneGlobalMomentumX.clear();
  PlaneGlobalMomentumY.clear();
  PlaneGlobalMomentumZ.clear();

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

//   PrimaryQ2                      = 0.0;
//   CrossSection                   = 0.0;
//   CrossSectionWeight             = 0.0;

  GlobalPhiAngle.clear();
  GlobalThetaAngle.clear();

  TotalEnergy.clear();
  KineticEnergy.clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserGEM_WirePlaneEvent.cc,v $
//      Revision 1.3  2006/05/05 21:51:16  grimm
//      Records now the kinetic and total energy of track/particle
//
//      Revision 1.2  2005/12/27 19:17:21  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

