
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimPhysicsList.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:23:56 $
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
   \class QweakSimPhysicsList
    
   \brief Declaration of the particles and physical processes.

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
//  Update Date:      $Date: 2006/05/05 21:23:56 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPhysicsList_h
#define QweakSimPhysicsList_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4VUserPhysicsList.hh"
#include "G4Decay.hh"

// geant4 classes
class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpBoundaryProcess;

// user classes
class QweakSimPhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimPhysicsList: public G4VUserPhysicsList
{
public:
  QweakSimPhysicsList();
  ~QweakSimPhysicsList();

  //for the Messenger 
  void SetVerbose(G4int);
  void SetNbOfPhotonsCerenkov(G4int); 
  void SetCuts();
 
protected:
  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();
    
  // these methods Construct particles 
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructMesons();
  void ConstructBaryons();
  void ConstructIons();
  void ConstructShortLiveds();
  
  // these methods Construct physics processes and register them
  void ConstructEMProcess();
  void ConstructOpticalPhotonProcess();
  void ConstructHadronProcess();
  void ConstructNeutronProcess();
  void ConstructPhotonNuclearProcess();
  void ConstructElectronNuclearProcess();
  void ConstructDecayProcess();

  virtual void AddTransportation();
   
  G4Decay fDecayProcess;


private:

  G4Cerenkov*          theCerenkovProcess;
  G4Scintillation*     theScintillationProcess;
  G4OpAbsorption*      theAbsorptionProcess;
  G4OpRayleigh*        theRayleighScatteringProcess;
  G4OpBoundaryProcess* theBoundaryProcess;
  
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4double cutForAlpha;
  G4double cutForGenericIon;

  QweakSimPhysicsListMessenger* pMessenger;   
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPhysicsList.hh,v $
//      Revision 1.3  2006/05/05 21:23:56  grimm
//      Included/Restructured:
//
//
//      void ConstructEMProcess();
//      void ConstructOpticalPhotonProcess();
//      void ConstructHadronProcess();
//
//      void ConstructNeutronProcess();
//      void ConstructPhotonNuclearProcess();
//      void ConstructElectronNuclearProcess();
//      void ConstructDecayProcess();
//
//      Revision 1.2  2005/12/27 19:26:04  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//  
