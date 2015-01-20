
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_DriftCellFrontSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:32:03 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimVDC_DriftCellFrontSD
    
   \brief Checks for a valid VDC U-DriftCell and/or V-DriftCell hit and stores the hit information

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:32:03 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_DriftCellFrontSD_h
#define QweakSimVDC_DriftCellFrontSD_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimVDC_DriftCellHit.hh"

// user classes
class QweakSimVDC;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimVDC_DriftCellFrontSD : public G4VSensitiveDetector
{

public:
  QweakSimVDC_DriftCellFrontSD(G4String name);
  ~QweakSimVDC_DriftCellFrontSD();
  
  void Initialize(G4HCofThisEvent* HCE);
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
  void EndOfEvent(G4HCofThisEvent* HCE);

  static void SetNumberOfDriftCellsPerPlane(G4int dc_npp) { DCNumberPerPlane  = dc_npp; }
  static void StoreDCWidthOnFrame(G4double dc_w)          { DCWidthOnFrame    = dc_w; }
  static void StoreDCFullThickness(G4double dc_ft)        { DCFullThickness   = dc_ft; }
  static void StoreDCUPlaneWireAngle(G4double dc_ua)      { DCUPlaneWireAngle = dc_ua; }
  static void StoreDCVPlaneWireAngle(G4double dc_va)      { DCVPlaneWireAngle = dc_va; }

private:
  
  QweakSimVDC_DriftCellHitsCollection*  DC_hitsCollection;
  
  G4int DC_ID;

  static G4int DCNumberPerPlane;
  static G4double DCWidthOnFrame;
  static G4double DCFullThickness;
  static G4double DCUPlaneWireAngle;
  static G4double DCVPlaneWireAngle;

  QweakSimVDC* pQweakSimVDCSetup;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellFrontSD.hh,v $
//      Revision 1.2  2005/12/27 19:32:03  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

