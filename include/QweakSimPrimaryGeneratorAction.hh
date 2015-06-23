// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimPrimaryGeneratorAction
    
   \brief Deal with primary particle generation and inject it in the detector

   The primary particle is taken from the root file ep_elastic.root which contains the vertex and kinematic of elastic
   scattered electrons. 

   Placeholder for a long explaination
    
 */
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPrimaryGeneratorAction_h
#define QweakSimPrimaryGeneratorAction_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4ios.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#include "QweakSimUserInformation.hh"
#include "QweakSimEPEvent.hh"

// geant4 classes
class G4ParticleGun;

// user classes
class QweakSimPrimaryGeneratorActionMessenger;

//infomation class
class QweakSimUserInformation;
class QweakSimEPEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class QweakSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI, QweakSimEPEvent* myEPEvent);    
   virtual ~QweakSimPrimaryGeneratorAction();
  
public:


  void SetBeamRasteringRegion(G4double X_min = -2.0*mm,
                              G4double X_max =  2.0*mm,
                              G4double Y_min = -2.0*mm,
                              G4double Y_max =  2.0*mm) {
    if (X_max < X_min) X_max = X_min;
    if (Y_max < Y_min) Y_max = Y_min;
    fPositionX_min = X_min;
    fPositionX_max = X_max;
    fPositionY_min = Y_min;
    fPositionY_max = Y_max;
  }


  void GeneratePrimaries(G4Event* anEvent);
  void SetPolarization(G4String polarization) {
    fPolarization = polarization;
  }

  void SetParticleType(G4String type = "e-") {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(type);
    if (particleGun && particle) {
      G4cout << "###### Setting particle type to " << type << G4endl;
      particleGun->SetParticleDefinition(particle);
    }
  }

  QweakSimUserInformation* GetUserInfo() const { return myUserInfo; };

private:

  G4ParticleGun*                      particleGun;

  QweakSimUserInformation*            myUserInfo;
  
  QweakSimEPEvent* myEvent;

  QweakSimPrimaryGeneratorActionMessenger* myMessenger;  // pointer to the Messenger

  G4String fPolarization;

  G4double fPositionX_min;
  G4double fPositionX_max;
  G4double fPositionY_min;
  G4double fPositionY_max;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

