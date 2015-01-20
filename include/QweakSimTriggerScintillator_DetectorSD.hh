
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTriggerScintillator_DetectorSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:00 $
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
   \class QweakSimTriggerScintillator_DetectorSD
    
   \brief Storing hit information of the Trigger Scintillator detector

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
//  Update Date:      $Date: 2005/12/27 19:28:00 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTriggerScintillator_DetectorSD_h
#define QweakSimTriggerScintillator_DetectorSD_h 

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimTriggerScintillator_DetectorHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTriggerScintillator_DetectorSD : public G4VSensitiveDetector
{

public:
  QweakSimTriggerScintillator_DetectorSD(G4String name);
  ~QweakSimTriggerScintillator_DetectorSD();
  
  void Initialize(G4HCofThisEvent* HCE);
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
  void EndOfEvent(G4HCofThisEvent* HCE);

private:
  
  QweakSimTriggerScintillator_DetectorHitsCollection*  TriggerScintillator_DetectorHitsCollection;
  
  G4int TriggerScintillator_CollectionID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_DetectorSD.hh,v $
//      Revision 1.2  2005/12/27 19:28:00  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

