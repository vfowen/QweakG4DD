// QweakSimTriggerScintillator_DetectorSD.cc
// Klaus Hans Grimm   
// 2005-12-27
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTriggerScintillator_DetectorSD.hh"

// user classes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimTriggerScintillator_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 

  collectionName.insert("TriggerScintillatorCollection"); 
  TriggerScintillator_CollectionID = -1;

  //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorSD::~QweakSimTriggerScintillator_DetectorSD()
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::~QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 

  //delete TriggerScintillator_HitsCollection;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator_DetectorSD::Initialize(G4HCofThisEvent* HCE)
{
   //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::Initialize() " << G4endl << G4endl; 

   TriggerScintillator_DetectorHitsCollection = new QweakSimTriggerScintillator_DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);

   //if(TriggerScintillator_CollectionID<0)

   TriggerScintillator_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 

   HCE->AddHitsCollection(TriggerScintillator_CollectionID , TriggerScintillator_DetectorHitsCollection);
   
   //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::Initialize() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//G4bool QweakSimTriggerScintillatorSD::ProcessHits(G4Step* aStep,G4TouchableHistory* /*ROhist*/)
G4bool QweakSimTriggerScintillator_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
//   G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::ProcessHits() " << G4endl << G4endl; 

  G4Track *track = aStep->GetTrack();    
  G4String  particlename = track->GetDefinition()->GetParticleName();
  G4int     particletype = track->GetDefinition()->GetPDGEncoding();

  G4ThreeVector worldPos;
  G4ThreeVector localPos;
  G4ThreeVector worldMomentum;
  
  G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();
 
  if (aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary ) {
    // Entering Geometry
    worldPos      = aStep->GetPreStepPoint()->GetPosition();
    localPos      = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
    worldMomentum = aStep->GetPreStepPoint()->GetMomentum();
  } else { 
    return false;
  }

  G4ThreeVector localMomentum = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
 
  // Vertex: where this track was generated
  G4ThreeVector originVertexPosition          = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double      originVertexKineticEnergy     = aStep->GetTrack()->GetVertexKineticEnergy();

  G4double      currentKineticEnergy     = aStep->GetTrack()->GetKineticEnergy();
  G4double      currentTotalEnergy       = aStep->GetTrack()->GetTotalEnergy();
  G4ThreeVector currentMomentumDirection = aStep->GetTrack()->GetMomentumDirection();

  G4int trackID = aStep->GetTrack()->GetTrackID();
  
  G4int    MotherCopyNo    = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume

  QweakSimTriggerScintillator_DetectorHit* aHit = new QweakSimTriggerScintillator_DetectorHit(MotherCopyNo);
  
  // Energy deposited in TS 
  G4double depositedEnergy = aStep->GetTotalEnergyDeposit();
  aHit->StoreDepositedEnergy(depositedEnergy);

  aHit->StoreTrackID(trackID);

  aHit->StoreGlobalTime(aStep->GetPreStepPoint()->GetGlobalTime());

  aHit->StoreParticleName(particlename);
  aHit->StoreParticleType(particletype);
    
  aHit->StoreWorldPosition(worldPos);
  aHit->StoreLocalPosition(localPos);

  aHit->StoreWorldMomentum(worldMomentum);
  aHit->StoreLocalMomentum(localMomentum);

  aHit->StoreOriginVertexPosition(originVertexPosition);
  aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  aHit->StoreOriginVertexTotalEnergy(originVertexKineticEnergy);   /// \todo beware: total.neq.kinetic (testing only)
  aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);

  aHit->StoreMomentumDirection(currentMomentumDirection);
  aHit->StoreKineticEnergy(currentKineticEnergy);
  aHit->StoreTotalEnergy(currentTotalEnergy);

  // check if it is first touch
  if(!(aHit->GetLogVolume()))
    {
      // store translation and rotation matrix of the drift cell 
      // for the sake of drawing the hit 
      aHit->StoreLogVolume(theTouchable->GetVolume()->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->StoreCellRotation(aTrans.NetRotation());
      aHit->StoreCellPosition(aTrans.NetTranslation());
    }
 
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  before inserting the hit" << G4endl;

  TriggerScintillator_DetectorHitsCollection->insert(aHit); 
  
//   G4cout << G4endl << "###### Leaving QweakSimTriggerScintillatorSD::ProcessHits() " << G4endl << G4endl; 
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void QweakSimTriggerScintillatorSD::EndOfEvent(G4HCofThisEvent*  HCE)
void QweakSimTriggerScintillator_DetectorSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::EndOfEvent() " << G4endl << G4endl; 
  
//   G4int NbDCHits = DC_hitsCollection->entries();
  
//   G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
// 	 << " hits in the Drift Cells : " << G4endl;
//   for (G4int i=0;i<NbDCHits;i++) (*DC_hitsCollection)[i]->Print();
  


   //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::EndOfEvent() " << G4endl << G4endl; 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 

