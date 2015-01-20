#include "QweakSimTrackHistory.hh"

// geant4 includes
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

//ClassImp(QweakSimTrackHistory)

QweakSimTrackHistory::QweakSimTrackHistory()
{
} 

QweakSimTrackHistory::~QweakSimTrackHistory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackHistory::AddTrackInfo(const G4Track* aTrack)
{
    sourceTrackID       = aTrack->GetTrackID();
    sourceDefinition    = aTrack->GetDefinition();
    sourcePosition      = aTrack->GetPosition();
    sourceMomentum      = aTrack->GetMomentum();
    sourceEnergy        = aTrack->GetTotalEnergy();
    sourceTime          = aTrack->GetGlobalTime();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackHistory::Print() const
{
//   G4cout  << "###### Calling QweakSimTrackHistory::Print() " << G4endl;

    G4cout << "########################################################################"  << G4endl; 
    G4cout << "Source Track ID                = " << sourceTrackID                        << G4endl;
    G4cout << "Source Particle Name           = " << sourceDefinition->GetParticleName()  << G4endl;
    G4cout << "Source Particle Energy   [GeV] = " << sourceEnergy/GeV                     << G4endl; 
    G4cout << "Source Particle Position [mm]  = " << sourcePosition                       << G4endl;
    G4cout << "########################################################################"  << G4endl; 

//   G4cout  << "###### Leaving QweakSimTrackHistory::Print() " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackHistory::Initialize()
{
  //G4cout << G4endl << "###### Calling QweakSimTrackHistory::Initialize() " << G4endl << G4endl;

    sourceTrackID    = -1;
    sourceTrackID    = -1;
    sourceDefinition = 0;
    sourcePosition   = G4ThreeVector(0.,0.,0.);
    sourceMomentum   = G4ThreeVector(0.,0.,0.);
    sourceEnergy     = 0.;
    sourceTime       = 0.;


  //G4cout << G4endl << "###### Leaving QweakSimTrackHistory::Initialize() " << G4endl << G4endl;

}
