//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimPrimaryGeneratorAction.cc

   $Revision: 1.4 $
   $Date: 2006/05/05 21:35:07 $

   \author Klaus Hans Grimm

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorAction.hh"

// geant4 includes
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

// user includes
#include "QweakSimPrimaryGeneratorActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4int QweakSimPrimaryGeneratorAction::kActiveOctantNumber = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI, QweakSimEPEvent* myEPEvent)
{
    G4cout << "###### Calling QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;

    fPositionX_min = -2.0*mm;
    fPositionX_max =  2.0*mm;
    fPositionY_min = -2.0*mm;
    fPositionY_max =  2.0*mm;
    
    fPolarization = "L";
    
    myUserInfo = myUI;
    myEvent = myEPEvent;
    
    // get my messenger
    myMessenger = new QweakSimPrimaryGeneratorActionMessenger(this);
    
    // get my messenger
    myMessenger = new QweakSimPrimaryGeneratorActionMessenger(this);
    
    // initialize my own event counter
    // myEventCounter = 0;
    
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);
    SetParticleType("e-");
    
    myEvent->SetBeamEnergy();
    
    G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction()
{

    G4cout << "###### Calling/Leaving QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction " << G4endl;

    if (particleGun) delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    /** \page target_energy_loss target energy loss
     * Pre-scattering (external) target energy loss is simulated by throwing one primary particle
     * starting at 30 cm upstream of the target and letting it propagate to the actual z vertex position
     * in the target.  A second primary particle is then thrown with the angle and transverse position
     * of the first primary at that point.  Event time starts when the first primary is thrown.
     * \todo need to double-check that position and momentum are properly transferred to second primary
     */

    G4int myEventCounter = myUserInfo->GetPrimaryEventNumber();

    if (myEventCounter%1000==0) G4cout << "*=== Event number = " << myEventCounter << " ===*" << G4endl;

    G4double myPositionX, myPositionY, myPositionZ, myVertexZ;
    G4double myNormMomentumX, myNormMomentumY, myNormMomentumZ;
    G4double E_beam;  // Energy of the incoming and outgoing particle


    myPositionX =  myUserInfo->GetBeamPositionX();
    myPositionY =  myUserInfo->GetBeamPositionY();
    myPositionZ =  myUserInfo->GetBeamPositionZ();

    myNormMomentumX  = tan(myUserInfo->GetNormMomentumX()); // = 0
    myNormMomentumY  = tan(myUserInfo->GetNormMomentumY()); // = 0
    myNormMomentumZ  = sqrt(1.0 - myNormMomentumX * myNormMomentumX - myNormMomentumY * myNormMomentumY);  // = 1

    E_beam = myUserInfo->GetBeamEnergy() - 0.511*MeV;

    myUserInfo->StoreOriginVertexPositionZ(myEvent->GetVertexZ());
    myUserInfo->EvtGenStatus = 0;   
    
    particleGun->SetParticlePosition(G4ThreeVector(myPositionX,
						   myPositionY,
						   myPositionZ ));
    
    
    //Buddhini - Hard code the gun to spit out particles in +-20 deg angles in the horizontal plane.
//     G4double theta_x = 0.0;
//     theta_x = CLHEP::RandFlat::shoot(-20,20);
//     G4cout<<"$$$$ theta_x "<<theta_x<<G4endl;
//     G4ThreeVector momDir;
//     momDir.setRThetaPhi(1.,theta_x*deg,0*deg);
//     particleGun->SetParticleMomentumDirection(momDir);

    particleGun->SetParticleMomentumDirection(G4ThreeVector(myNormMomentumX,
    							    myNormMomentumY,
    							    myNormMomentumZ));
    
    if (fPolarization == "L") {
      // longitudinal polarization (after generation)
      particleGun->SetParticlePolarization((G4ThreeVector(myNormMomentumX,
							  myNormMomentumY,
							  myNormMomentumZ)));
    }else if (fPolarization == "V") {
      // vertical transverse polarization (after generation)
      particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,
							 myNormMomentumY,
							 myNormMomentumZ)
					   .cross(G4ThreeVector(1,0,0)));
    }else if (fPolarization == "H") {
      // horizontal transverse polarization (after generation)
      particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,
							 myNormMomentumY,
							 myNormMomentumZ)
					   .cross(G4ThreeVector(0,1,0)));
    }else if(fPolarization == "mV"){
      particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,
							 myNormMomentumY,
							 myNormMomentumZ)
                                           .cross(G4ThreeVector(-1,0,0)));
    }else if(fPolarization == "mH"){
      particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,
							 myNormMomentumY,
							 myNormMomentumZ)
					   .cross(G4ThreeVector(0,-1,0)));
    }else if(fPolarization == "mL"){
      particleGun->SetParticlePolarization(G4ThreeVector(-myNormMomentumX,
							 -myNormMomentumY,
							 -myNormMomentumZ));
    }else if(fPolarization == "0"){
      particleGun->SetParticlePolarization(0,0,0);
    }else particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,myNormMomentumY,myNormMomentumZ)); //longitudinal by default
    
    particleGun->SetParticleEnergy(E_beam);
    
    // finally : fire !!!
    particleGun->GeneratePrimaryVertex(anEvent);  // takes an event, generates primary vertex, and associates primary particles with the vertex
    myUserInfo->StorePrimaryEventNumber(myEventCounter+1);
    //myUserInfo->SetBeamEnergy(myEvent->GetBeamEnergy());
    // rest of userInfo filled in QweakSimSteppingAction.cc
    
    //  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
