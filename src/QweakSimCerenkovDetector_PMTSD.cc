//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkovDetector_PMTSD.hh"

// geant4 includes
#include "G4OpticalPhoton.hh"

// user includes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimCerenkovDetector_PMTHit.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrajectory.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector_PMTSD::QweakSimCerenkovDetector_PMTSD(G4String name, QweakSimUserInformation *userInfo)
:G4VSensitiveDetector(name)
{
  collectionName.insert("PMTHitCollection"); 
  CerenkovDetectorPMT_CollectionID = -1;
  myUserInfo = userInfo;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector_PMTSD::~QweakSimCerenkovDetector_PMTSD()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector_PMTSD::Initialize(G4HCofThisEvent* HCE)
{
   CerenkovDetector_PMTHitsCollection = new QweakSimCerenkovDetector_PMTHitsCollection(SensitiveDetectorName,collectionName[0]);
   
   if(CerenkovDetectorPMT_CollectionID<0)
     { CerenkovDetectorPMT_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(CerenkovDetector_PMTHitsCollection); }
   HCE->AddHitsCollection(CerenkovDetectorPMT_CollectionID , CerenkovDetector_PMTHitsCollection);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool QweakSimCerenkovDetector_PMTSD::ProcessHits_constStep(const G4Step* aStep,G4TouchableHistory* /*ROhist*/)
{

  if (aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) 
    return false;

  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
  G4StepPoint*        postStepPoint = aStep->GetPostStepPoint();
//   G4VPhysicalVolume*  thePrePV      = preStepPoint->GetPhysicalVolume();
//   G4VPhysicalVolume*  thePostPV     = postStepPoint->GetPhysicalVolume();

  G4TouchableHistory* theTouchable  = (G4TouchableHistory*)(preStepPoint->GetTouchable());
//   G4VPhysicalVolume*  physVol       = theTouchable->GetVolume();

  if (postStepPoint->GetStepStatus() != fGeomBoundary) return false;

  //if( physVol->GetName().compare("Cathode_Physical")!=0 ) return false;

  if (preStepPoint->GetStepStatus() != fGeomBoundary) return false; // Entering Geometry

  G4double currentPhotonEnergy = aStep->GetTrack()->GetTotalEnergy();
  G4double currentHitTime      = aStep->GetTrack()->GetGlobalTime();
  G4int MotherCopyNo      = theTouchable->GetVolume(1)->GetCopyNo();
  QweakSimCerenkovDetector_PMTHit* aHit = new QweakSimCerenkovDetector_PMTHit();
  G4int MotherReplicaNo2  = theTouchable->GetReplicaNumber(3);        // Several MotherVolumes

//  std::cout<<"store hit info: detector "<<MotherReplicaNo2<<"  PMTID "<<MotherCopyNo<<std::endl;
  aHit->StoreDetectorID(MotherReplicaNo2); // which octant (number to be converted) 
  aHit->StorePMTID(MotherCopyNo);          // left or right pmt

  aHit->StorePhotonEnergy(currentPhotonEnergy);
  aHit->StoreHitTime(currentHitTime);
  G4int hitCount = CerenkovDetector_PMTHitsCollection->insert(aHit); 
  aHit->StoreHitID(hitCount);
  //aHit->SetHitValid(False);
  myUserInfo->SetCurrentPMTHit(aHit,MotherCopyNo);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetector_PMTSD::EndOfEvent(G4HCofThisEvent* )
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory* QweakSimCerenkovDetector_PMTSD::GetParentTrajectory(G4int parentID)
{
  G4TrajectoryContainer* trajectoryContainer = 
   G4RunManager::GetRunManager()->GetCurrentEvent()->GetTrajectoryContainer();

  if(trajectoryContainer==0) 
  {
      G4cout << " Could not find the TrajectoryContainer" << G4endl;
      return 0;
  }
//  TrajectoryVector* vect = container->GetVector();
//
//    (G4VTrajectory**) tr = vect->begin();
//
//   while(tr != vect->end())
//   {
//     QweakSimTrajectory* tr1 = (QweakSimTrajectory*)(*tr);
//     if(tr1->GetTrackID()==parentID) return tr1;
//     tr++;
//   }

G4int i = 0;

G4int n_trajectories = trajectoryContainer->entries();

while(i != n_trajectories)
{

    QweakSimTrajectory* trj = (QweakSimTrajectory*)((*trajectoryContainer)[i]);
    G4cout << " Current charge of possible parent track = " <<trj->GetCharge() << "--- Parent ID = "
	   <<  trj->GetTrackID() << G4endl;
    if(trj->GetTrackID()==parentID) return trj;
    i++;
}

return 0;
}

