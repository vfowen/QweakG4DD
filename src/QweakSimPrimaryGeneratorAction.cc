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
    
    fPolarization = "0";
    
    myUserInfo = myUI;
    myEvent = myEPEvent;
    
    // get my messenger
    myMessenger = new QweakSimPrimaryGeneratorActionMessenger(this);
        
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
  G4int myEventCounter = myUserInfo->GetPrimaryEventNumber();
  
  if (myEventCounter%1000==0) G4cout << "*=== Event number = " << myEventCounter << " ===*" << G4endl;
  
  G4double myPositionX, myPositionY, myPositionZ;
  G4double myNormMomentumX, myNormMomentumY, myNormMomentumZ;
  G4double E_beam;  // Energy of the incoming and outgoing particle
  
  if( myUserInfo->GetFixedPosMom() ){
    myPositionX =  myUserInfo->GetBeamPositionX(-1);
    myPositionY =  myUserInfo->GetBeamPositionY(-1);
    myPositionZ =  myUserInfo->GetBeamPositionZ(-1);
    myNormMomentumX  = sin(myUserInfo->GetNormMomentumX(-1));
    myNormMomentumY  = sin(myUserInfo->GetNormMomentumY(-1));
  }else{
    myPositionX =  myUserInfo->GetBeamPositionX(myEventCounter);    
    myPositionY =  myUserInfo->GetBeamPositionY(myEventCounter);
    myPositionZ =  myUserInfo->GetBeamPositionZ(myEventCounter);
    myNormMomentumX  = sin(myUserInfo->GetNormMomentumX(myEventCounter));
    myNormMomentumY  = sin(myUserInfo->GetNormMomentumY(myEventCounter));
  }

  myNormMomentumZ  = sqrt(1.0 - myNormMomentumX * myNormMomentumX - myNormMomentumY * myNormMomentumY);

  E_beam = myUserInfo->GetBeamEnergy() - 0.511*MeV;
  
  myUserInfo->StoreOriginVertexPositionZ(myEvent->GetVertexZ());
  myUserInfo->EvtGenStatus = 0;   
  
  particleGun->SetParticlePosition(G4ThreeVector(myPositionX,
						 myPositionY,
						 myPositionZ ));
  
  particleGun->SetParticleMomentumDirection(G4ThreeVector(myNormMomentumX,
							  myNormMomentumY,
							  myNormMomentumZ));

  if(myEventCounter<10 && 0)
    G4cout<<" posmom "<<myPositionX<<" "<<myPositionY<<" "<<myPositionZ<<" "
	  <<myNormMomentumX<<" "<<myNormMomentumY<<" "<<myNormMomentumZ<<" "<<G4endl;
  if (fPolarization == "f") {
    G4double myPolX(0),myPolY(0),myPolZ(0);
    myPolX=myUserInfo->GetBeamPolarizationX(myEventCounter);
    myPolY=myUserInfo->GetBeamPolarizationY(myEventCounter);
    myPolZ=sqrt(1-myPolX*myPolX-myPolY*myPolY);

    if(myEventCounter<10 && 0)
      G4cout<<" pol "<<myPolX<<" "<<myPolY<<" "<<myPolZ<<G4endl;
    
    particleGun->SetParticlePolarization(G4ThreeVector(myPolX,myPolY,myPolZ));
  }else{
  
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
    }else if(fPolarization == "0"){//unpolarized
      particleGun->SetParticlePolarization(G4ThreeVector(0,0,0));
    }else particleGun->SetParticlePolarization(G4ThreeVector(myNormMomentumX,
							     myNormMomentumY,
							     myNormMomentumZ)); //longitudinal by default
  }

  particleGun->SetParticleEnergy(E_beam);
  
  // takes an event, generates primary vertex, and associates primary particles with the vertex
  particleGun->GeneratePrimaryVertex(anEvent);  
  myUserInfo->StorePrimaryEventNumber(myEventCounter+1);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
