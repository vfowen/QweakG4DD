//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimHDC_WirePlaneSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:24:52 $
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
   \class QweakSimHDC_WirePlaneSD
    
   \brief Checks for a valid HDC WirePlane hit and stores the hit information
     (Up to now I only activated only 1 out of 6 sensitive wireplanes per HDC)

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
//  Update Date:      $Date: 2005/12/27 19:24:52 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimHDC_WirePlaneSD_h
#define QweakSimHDC_WirePlaneSD_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"

// user classes
#include "QweakSimHDC_WirePlaneHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimHDC_WirePlaneSD : public G4VSensitiveDetector
{

  public:
       QweakSimHDC_WirePlaneSD(G4String name);
      ~QweakSimHDC_WirePlaneSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
      void EndOfEvent(G4HCofThisEvent* HCE);

  private:
      QweakSimHDC_WirePlane_HitsCollection*  hitsCollection;

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
//      $Log: QweakSimHDC_WirePlaneSD.hh,v $
//      Revision 1.2  2005/12/27 19:24:52  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

