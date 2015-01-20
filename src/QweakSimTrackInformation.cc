//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTrackInformation.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:15:27 $

   \author Klaus Hans Grimm   

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTrackInformation.hh"

// geant4 includes
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

// user includes
#include "QweakSimTrackHistory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Primary Track info
// based on http://geant4.slac.stanford.edu/Tips/index.html

G4Allocator<QweakSimTrackInformation> aTrackInformationAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrackInformation::QweakSimTrackInformation()
{
  //G4cout << G4endl << "###### Calling QweakSimTrackInformation::QweakSimTrackInformation() " << G4endl << G4endl;

  Initialize();

  //G4cout << G4endl << "###### Leaving QweakSimTrackInformation::QweakSimTrackInformation() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrackInformation::~QweakSimTrackInformation()
{
  //G4cout << G4endl << "###### Calling/Leaving QweakSimTrackInformation::~QweakSimTrackInformation() " << G4endl << G4endl;
}

QweakSimTrackInformation::QweakSimTrackInformation(const G4Track* aTrack)
{

    primaryTrackID     = aTrack->GetTrackID();
    particleDefinition = aTrack->GetDefinition();

    G4double tmpE = -1.0*MeV;
    CerenkovHitEnergy.push_back(tmpE);
    ParticleHistory.push_back(aTrack->GetDefinition());
    ParentEnergy.push_back(aTrack->GetTotalEnergy());
    ParticleCreatorProcess.push_back("Primary");
    OriginVertex.push_back(aTrack->GetPosition());

    primaryPosition      = aTrack->GetPosition();
    primaryMomentum      = aTrack->GetMomentum();
    primaryEnergy        = aTrack->GetTotalEnergy();
    primaryKineticEnergy = aTrack->GetKineticEnergy();
    primaryTime          = aTrack->GetGlobalTime();

    trackingStatus       = 0;
    trackIsPrimaryStatus = 0;

    sourceTrackID    = -1;
    sourceDefinition = 0;
    sourcePosition   = G4ThreeVector(0.,0.,0.);
    sourceMomentum   = G4ThreeVector(0.,0.,0.);
    sourceEnergy     = 0.;
    sourceTime       = 0.;

    cerenkovImpactTrackID    = -1;
    cerenkovImpactDefinition = 0;
    cerenkovImpactPosition   = G4ThreeVector(0.,0.,0.);
    cerenkovImpactMomentum   = G4ThreeVector(0.,0.,0.);
    cerenkovImpactEnergy     = 0.;
    cerenkovImpactTime       = 0.;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrackInformation::QweakSimTrackInformation(const QweakSimTrackInformation* aTrackInfo)
{
 //G4cout << G4endl << "###### Calling QweakSimTrackInformation::QweakSimTrackInformation(const QweakSimTrackInformation* aTrackInfo) " << G4endl << G4endl;


    // Return TrackInfo which can not derived from G4Track
    // Must be filled/provided manually  
//     primaryQ2                   = aTrackInfo->primaryQ2;
//     crossSection                = aTrackInfo->crossSection;
//     crossSectionWeight          = aTrackInfo->crossSectionWeight;
//     primaryEventNumber          = aTrackInfo->primaryEventNumber;
    //----------
    primaryTrackID              = aTrackInfo->primaryTrackID;
    particleDefinition          = aTrackInfo->particleDefinition;
    primaryPosition             = aTrackInfo->primaryPosition;
    primaryMomentum             = aTrackInfo->primaryMomentum;
    primaryEnergy               = aTrackInfo->primaryEnergy;
    primaryTime                 = aTrackInfo->primaryTime;
    //---------
    sourceTrackID               = aTrackInfo->sourceTrackID;
    sourceDefinition            = aTrackInfo->sourceDefinition;
    sourcePosition              = aTrackInfo->sourcePosition;
    sourceMomentum              = aTrackInfo->sourceMomentum;
    sourceEnergy                = aTrackInfo->sourceEnergy;
    sourceTime                  = aTrackInfo->sourceTime;
    sourceOriginPosition        = aTrackInfo->sourceOriginPosition;
    sourceOriginEnergy          = aTrackInfo->sourceOriginEnergy;
    //---------
    cerenkovImpactTrackID       = aTrackInfo->cerenkovImpactTrackID;
    cerenkovImpactDefinition    = aTrackInfo->cerenkovImpactDefinition;
    cerenkovImpactPosition      = aTrackInfo->cerenkovImpactPosition;
    cerenkovImpactMomentum      = aTrackInfo->cerenkovImpactMomentum;
    cerenkovImpactEnergy        = aTrackInfo->cerenkovImpactEnergy;
    cerenkovImpactTime          = aTrackInfo->cerenkovImpactTime;
    cerenkovImpactOriginPosition      = aTrackInfo->cerenkovImpactOriginPosition;
    cerenkovImpactOriginEnergy        = aTrackInfo->cerenkovImpactOriginEnergy;
    //---------
    trackingStatus              = aTrackInfo->trackingStatus;
    trackIsPrimaryStatus        = aTrackInfo->trackIsPrimaryStatus;
    //---------

    ParticleHistory.resize(aTrackInfo->ParticleHistory.size());
    ParentEnergy.resize(aTrackInfo->ParticleHistory.size());
    CerenkovHitEnergy.resize(aTrackInfo->ParticleHistory.size());
    ParticleCreatorProcess.resize(aTrackInfo->ParticleHistory.size());
    OriginVertex.resize(aTrackInfo->ParticleHistory.size());
    for(size_t i = 0; i < aTrackInfo->ParticleHistory.size(); i++)
    {
	ParticleHistory[i]   = aTrackInfo->ParticleHistory[i];
	ParentEnergy[i]      = aTrackInfo->ParentEnergy[i];
	CerenkovHitEnergy[i] = aTrackInfo->CerenkovHitEnergy[i];
	ParticleCreatorProcess[i] = aTrackInfo->ParticleCreatorProcess[i];
	OriginVertex[i] = aTrackInfo->OriginVertex[i];
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::SetSourceTrackInformation(const G4Track* aTrack)
{
    sourceTrackID       = aTrack->GetTrackID();
    sourceDefinition    = aTrack->GetDefinition();
    sourcePosition      = aTrack->GetPosition();
    sourceMomentum      = aTrack->GetMomentum();
    sourceEnergy        = aTrack->GetTotalEnergy();
    sourceTime           = aTrack->GetGlobalTime();
    sourceOriginPosition = aTrack->GetVertexPosition();
    sourceOriginEnergy   = aTrack->GetVertexKineticEnergy();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::SetImpactTrackInformationForCerenkov(const G4Track* aTrack)
{
    cerenkovImpactTrackID       = aTrack->GetTrackID();
    cerenkovImpactDefinition    = aTrack->GetDefinition();
    cerenkovImpactPosition      = aTrack->GetPosition();
    cerenkovImpactMomentum      = aTrack->GetMomentum();
    cerenkovImpactEnergy        = aTrack->GetTotalEnergy();
    cerenkovImpactTime          = aTrack->GetGlobalTime();
    cerenkovImpactOriginPosition = aTrack->GetVertexPosition();
    cerenkovImpactOriginEnergy   = aTrack->GetVertexKineticEnergy();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::AddTrackInfoToCerenkovTrackHistory(const G4Track* aTrack)
{

    QweakSimTrackHistory* theTrackHistory =  new QweakSimTrackHistory();

    theTrackHistory->AddTrackInfo(aTrack);

    theCerenkovTrackHistory.push_back(theTrackHistory);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::PrintPrimaryTrackInfo() const
{
//   G4cout  << "###### Calling QweakSimTrackInformation::PrintPrimaryTrackInfo() " << G4endl;

    G4cout << "########################################################################"  << G4endl; 
    G4cout << "Primary Track ID              = " << primaryTrackID                        << G4endl;
    G4cout << "Primary Particle Name         = " << particleDefinition->GetParticleName() << G4endl;
    G4cout << "Primary Particle Energy [GeV] = " << primaryEnergy/GeV                     << G4endl; 
    G4cout << "Primary Start Position  [mm]  = " << primaryPosition                       << G4endl;
    G4cout << "------------------------------------------------------------------------"  << G4endl; 
//     G4cout << "Primary track with Q2         = " << primaryQ2                             << G4endl;
//     G4cout << "Primary track with CS         = " << crossSection                          << G4endl;
//     G4cout << "Primary track with CSW        = " << crossSectionWeight                    << G4endl;
//     G4cout << "Primary track event number    = " << primaryEventNumber                    << G4endl;
    G4cout << "########################################################################"  << G4endl; 

//   G4cout  << "###### Leaving QweakSimTrackInformation::PrintPrimaryTrackInfo() " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::PrintSourceTrackInfo() const
{
//   G4cout  << "###### Calling QweakSimTrackInformation::PrintSourceTrackInfo() " << G4endl;

    G4cout << "########################################################################"  << G4endl; 
    G4cout << "Source Track ID                = " << sourceTrackID                        << G4endl;
    G4cout << "Source Particle Name           = " << sourceDefinition->GetParticleName()  << G4endl;
    G4cout << "Source Particle Energy   [GeV] = " << sourceEnergy/GeV                     << G4endl; 
    G4cout << "Source Particle Position [mm]  = " << sourcePosition                       << G4endl;
    G4cout << "Source Origin Position   [mm]  = " << sourceOriginPosition                 << G4endl;
    G4cout << "Source Origin Energy     [GeV] = " << sourceOriginEnergy                   << G4endl; 
    G4cout << "########################################################################"  << G4endl; 

//   G4cout  << "###### Leaving QweakSimTrackInformation::PrintSourceTrackInfo() " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::PrintCerenkovImpactTrackInfo() const
{
//   G4cout  << "###### Calling QweakSimTrackInformation::PrintCerenkovImpactTrackInfo() " << G4endl;

    G4cout << "########################################################################"  << G4endl; 
    G4cout << "Cerenkov Impact Track ID                = " << cerenkovImpactTrackID                        << G4endl;
    G4cout << "Cerenkov Impact Particle Name           = " << cerenkovImpactDefinition->GetParticleName()  << G4endl;
    G4cout << "Cerenkov Impact Particle Energy   [GeV] = " << cerenkovImpactEnergy/GeV                     << G4endl; 
    G4cout << "Cerenkov Impact Particle Position [mm]  = " << cerenkovImpactPosition                       << G4endl;
    G4cout << "Cerenkov Impact Origin Position   [mm]  = " << cerenkovImpactOriginPosition                 << G4endl;
    G4cout << "Cerenkov Impact Origin Energy     [GeV] = " << cerenkovImpactOriginEnergy                   << G4endl; 
    G4cout << "########################################################################"  << G4endl; 

//   G4cout  << "###### Leaving QweakSimTrackInformation::PrintCerenkovImpactTrackInfo() " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackInformation::Initialize()
{
  //G4cout << G4endl << "###### Calling QweakSimTrackInformation::Initialize() " << G4endl << G4endl;

    primaryTrackID     = 0;
    particleDefinition = 0;
    primaryPosition    = G4ThreeVector(0.0,0.0,0.0);
    primaryMomentum    = G4ThreeVector(0.0,0.0,0.0);
    primaryEnergy      = 0.0;
    primaryTime        = 0.0;

    ParticleHistory.resize(0);
    ParentEnergy.resize(0);
    CerenkovHitEnergy.resize(0);
    ParticleCreatorProcess.resize(0);
    OriginVertex.resize(0);

//     primaryQ2          = 0.0;
//     crossSection       = 0.0;
//     crossSectionWeight = 0.0;
//     primaryEventNumber = 0;

    trackingStatus       = 0;
    trackIsPrimaryStatus = 0;

    sourceTrackID    = -1;
    sourceTrackID    = -1;
    sourceDefinition = 0;
    sourcePosition   = G4ThreeVector(0.,0.,0.);
    sourceMomentum   = G4ThreeVector(0.,0.,0.);
    sourceEnergy     = 0.;
    sourceTime       = 0.;
    sourceOriginPosition   = G4ThreeVector(0.,0.,0.);
    sourceOriginEnergy     = 0.;

    cerenkovImpactTrackID    = -1;
    cerenkovImpactTrackID    = -1;
    cerenkovImpactDefinition = 0;
    cerenkovImpactPosition   = G4ThreeVector(0.,0.,0.);
    cerenkovImpactMomentum   = G4ThreeVector(0.,0.,0.);
    cerenkovImpactEnergy     = 0.;
    cerenkovImpactTime       = 0.;
    cerenkovImpactOriginPosition   = G4ThreeVector(0.,0.,0.);
    cerenkovImpactOriginEnergy     = 0.;



   theCerenkovTrackHistory.clear();
   theCerenkovTrackHistory.resize(0);

  //G4cout << G4endl << "###### Leaving QweakSimTrackInformation::Initialize() " << G4endl << G4endl;

}

void QweakSimTrackInformation::StoreCerenkovHitEnergy(G4int ind, G4double eng)
{
  if(ind < 0 || ind >= GetParticleHistoryLength()) {
    CerenkovHitEnergy.push_back(eng);
    return;
  }

  CerenkovHitEnergy[ind] = eng;
}

G4double QweakSimTrackInformation::GetCerenkovHitEnergyAtIndex(G4int ind)
{
  if (CerenkovHitEnergy.size() == 0) return -1.0;
  if (ind < 0 || ind >= (G4int) CerenkovHitEnergy.size()) return CerenkovHitEnergy[0];
  return CerenkovHitEnergy[ind];
}

G4ParticleDefinition* QweakSimTrackInformation::GetParticleDefinitionAtIndex(G4int ind)
{
  if (ParticleHistory.size() == 0) return NULL;
  if (ind > (G4int) ParticleHistory.size() - 1) return ParticleHistory[0];
  return ParticleHistory[ind];
}

G4double QweakSimTrackInformation::GetParentEnergyAtIndex(G4int ind)
{
  if (ParentEnergy.size() == 0) return -1.0;
  if (ind > (G4int) ParentEnergy.size() - 1) return ParentEnergy[0];
  return ParentEnergy[ind];
}

G4String QweakSimTrackInformation::GetCreatorProcessAtIndex(G4int ind)
{
  if (ParticleCreatorProcess.size() == 0) return "None";
  if (ind > (G4int) ParticleCreatorProcess.size() - 1) return "None";
  return ParticleCreatorProcess[ind];  
}

G4ThreeVector QweakSimTrackInformation::GetOriginVertex(G4int ind)
{
  G4ThreeVector vec(-10000*cm,-10000*cm,-10000*cm);

  if (OriginVertex.size() == 0) return vec;
  if (ind > (G4int) OriginVertex.size() - 1) return vec;
  return OriginVertex[ind];  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
