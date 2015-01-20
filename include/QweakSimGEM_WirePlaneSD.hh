
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimGEM_WirePlaneSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:24:14 $
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
   \class QweakSimGEM_WirePlaneSD
    
   \brief Checks for a valid GEM  ReadoutPlane hit and stores the hit information
     (I know there is no wire plane ... just for consistent class names )

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimGEM_WirePlaneSD_h
#define QweakSimGEM_WirePlaneSD_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimGEM_WirePlaneHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimGEM_WirePlaneSD : public G4VSensitiveDetector
{

  public:
       QweakSimGEM_WirePlaneSD(G4String name);
      ~QweakSimGEM_WirePlaneSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
      void EndOfEvent(G4HCofThisEvent* HCE);

  private:
      QweakSimGEM_WirePlane_HitsCollection*  hitsCollection;

      G4int HCID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

