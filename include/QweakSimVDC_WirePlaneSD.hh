//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_WirePlaneSD.hh

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:47:57 $

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
   \class QweakSimVDC_WirePlaneSD
    
   \brief Checks for a valid VDC U-WirePlane and/or V-Wireplane hit and stores the hit information

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
//  Update Date:      $Date: 2006/01/06 21:47:57 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_WirePlaneSD_h
#define QweakSimVDC_WirePlaneSD_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimVDC_WirePlaneHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimVDC_WirePlaneSD : public G4VSensitiveDetector
{

  public:
       QweakSimVDC_WirePlaneSD(G4String name);
      ~QweakSimVDC_WirePlaneSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
      void EndOfEvent(G4HCofThisEvent* HCE);

  private:
      QweakSimVDC_WirePlane_HitsCollection*  hitsCollection;

      G4int HCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_WirePlaneSD.hh,v $
//      Revision 1.3  2006/01/06 21:47:57  grimm
//      Cosmetic changes.
//
//      Revision 1.2  2005/12/27 19:32:34  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

