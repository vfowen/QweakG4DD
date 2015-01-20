
// QweakSimPMTOnly_PMTSD.cc
// Martin McHugh
// 2013-08-01

#include "QweakSimPMTOnly_PMTSD.hh"

// geant4 includes
#include "G4OpticalPhoton.hh"

// user includes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimPMTOnly_PMTHit.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrajectory.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPMTOnly_PMTSD::QweakSimPMTOnly_PMTSD(G4String name, QweakSimUserInformation *userInfo)
:G4VSensitiveDetector(name)
{
  collectionName.insert("PMTHitCollection"); 
  PMTOnlyPMT_CollectionID = -1;
  myUserInfo = userInfo; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPMTOnly_PMTSD::~QweakSimPMTOnly_PMTSD()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPMTOnly_PMTSD::Initialize(G4HCofThisEvent* HCE)
{
   PMTOnly_PMTHitsCollection = new QweakSimPMTOnly_PMTHitsCollection(SensitiveDetectorName,collectionName[0]);
   
   if(PMTOnlyPMT_CollectionID<0)
     { PMTOnlyPMT_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(PMTOnly_PMTHitsCollection); }
   HCE->AddHitsCollection(PMTOnlyPMT_CollectionID , PMTOnly_PMTHitsCollection);   
}

G4bool QweakSimPMTOnly_PMTSD::ProcessHits(G4Step* ,G4TouchableHistory* ){
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool QweakSimPMTOnly_PMTSD::ProcessHits_constStep(const G4Step* aStep, G4TouchableHistory* )
{
  // Make sure that this is a 
  if (aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) 
    return false;

  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
  G4StepPoint*        postStepPoint = aStep->GetPostStepPoint();

  if (postStepPoint->GetStepStatus() != fGeomBoundary) return false;
  if (preStepPoint->GetStepStatus() != fGeomBoundary) return false;	// Entering Volume

  G4double currentPhotonEnergy = aStep->GetTrack()->GetTotalEnergy();
  QweakSimPMTOnly_PMTHit* aHit = new QweakSimPMTOnly_PMTHit();

  aHit->StorePhotonEnergy(currentPhotonEnergy);
  G4int hitCount = PMTOnly_PMTHitsCollection->insert(aHit); 
  aHit->StoreHitID(hitCount);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPMTOnly_PMTSD::EndOfEvent(G4HCofThisEvent* )
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory* QweakSimPMTOnly_PMTSD::GetParentTrajectory(G4int parentID)
{
  G4TrajectoryContainer* trajectoryContainer = 
   G4RunManager::GetRunManager()->GetCurrentEvent()->GetTrajectoryContainer();

  if(trajectoryContainer==0) {
      G4cout << " Could not find the TrajectoryContainer" << G4endl;
      return 0;
  }

  G4int i = 0;
  G4int n_entries = trajectoryContainer->entries();
  while( i < n_entries) {
    QweakSimTrajectory* trj = (QweakSimTrajectory*)((*trajectoryContainer)[i]);
    G4cout << " Current charge of possible parent track = " <<trj->GetCharge() << "--- Parent ID = "
	   <<  trj->GetTrackID() << G4endl;
    if(trj->GetTrackID()==parentID) return trj;
    i++;
  }

  return 0;
}

