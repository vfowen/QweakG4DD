//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTriggerScintillator_PMTSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:15 $
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
   \class QweakSimTriggerScintillator_PMTSD
    
   \brief Storing photomultiplier hit information of the Trigger Scintillator detector

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
//  Update Date:      $Date: 2005/12/27 19:28:15 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTriggerScintillator_PMTSD_h
#define QweakSimTriggerScintillator_PMTSD_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"

// user classes
class QweakSimTriggerScintillator_PMTHitsCollection;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTriggerScintillator_PMTSD : public G4VSensitiveDetector
{

public:
  QweakSimTriggerScintillator_PMTSD(G4String name);
  ~QweakSimTriggerScintillator_PMTSD();
  
  void Initialize(G4HCofThisEvent* HCE);
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
  void EndOfEvent(G4HCofThisEvent* HCE);

private:
  
  QweakSimTriggerScintillator_PMTHitsCollection*  TriggerScintillator_PMTHitsCollection;
  
  G4int TriggerScintillatorPMT_CollectionID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_PMTSD.hh,v $
//      Revision 1.2  2005/12/27 19:28:15  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

