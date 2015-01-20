
// QweakSimLeadGlass_DetectorSD.cc
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#include "QweakSimLeadGlass_DetectorSD.hh"

//--- user classes
#include "QweakSimLeadGlass_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimSensitiveDetectorDefinition.hh"



/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorSD::QweakSimLeadGlass_DetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
    collectionName.insert("LeadGlassCollection"); 
    LeadGlass_CollectionID = -1;
}



/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorSD::~QweakSimLeadGlass_DetectorSD()
{
    //delete LeadGlass_HitsCollection;	
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass_DetectorSD::Initialize(G4HCofThisEvent* HCE)
{	
    LeadGlass_DetectorHitsCollection = new QweakSimLeadGlass_DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
    //if(LeadGlass_CollectionID<0)
    LeadGlass_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
    HCE->AddHitsCollection(LeadGlass_CollectionID , LeadGlass_DetectorHitsCollection);

}


/////// --------------------------------------------------------------------

G4bool QweakSimLeadGlass_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{	
  
  G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();
  G4int         motherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume
 
  //G4double    parentID     = aStep->GetTrack()->GetParentID();
  G4double      trackID      = aStep->GetTrack()->GetTrackID();
  
  G4ParticleDefinition*  fpParticleDefinition = aStep->GetTrack()->GetDefinition();
  G4String      particleName = fpParticleDefinition->GetParticleName();
  //G4double    pdgCharge    = fpParticleDefinition->GetPDGCharge();
  G4int         pdgEncoding  = fpParticleDefinition->GetPDGEncoding();
	
  //GlobalTimeOfHit
  G4double      globalTime   = aStep->GetPreStepPoint()->GetGlobalTime();
  
  G4ThreeVector worldPos             = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector localPos             = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
  //localExitPos;
  G4ThreeVector originVertexPosition = aStep->GetTrack()->GetVertexPosition();
  
  G4ThreeVector worldMomentum                 = aStep->GetPreStepPoint()->GetMomentum();
  G4ThreeVector localMomentum                 = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
  G4ThreeVector currentMomentumDirection      = aStep->GetTrack()->GetMomentumDirection();
  G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();
  
  //calculated in Event Action
  //G4double    originVertexThetaAngle;
  //G4double    originVertexPhiAngle;
  
  G4double      originVertexKineticEnergy = aStep->GetTrack()->GetVertexKineticEnergy();
  G4double      originVertexTotalEnergy   = aStep->GetTrack()->GetVertexKineticEnergy();//GetVertexTotalEnergy();
	
  G4double      currentKineticEnergy      = aStep->GetTrack()->GetKineticEnergy();
  G4double      currentTotalEnergy        = aStep->GetTrack()->GetTotalEnergy();
  
  //--- Get User Track Info
  //QweakSimTrackInformation* info = (QweakSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());
  
  //G4int       primaryTrackID       = info->GetPrimaryTrackID();
  //G4double    primaryQ2            = info->GetPrimaryQ2();
  //G4double    crossSection         = info->GetCrossSection();
  //G4double    crossSectionWeight   = info->GetCrossSectionWeight();
  
  //calculated in Event Action
  //G4double    globalThetaAngle;
  //G4double    globalPhiAngle;
  
  //--- LeadGlass deposited energy
  G4double      depositedEnergy      = aStep->GetTotalEnergyDeposit();
  
  
  //----------------- Store Hit information
  
  QweakSimLeadGlass_DetectorHit* aHit = new QweakSimLeadGlass_DetectorHit(motherCopyNo);
  
  aHit -> StoreTrackID(trackID);
  
  aHit -> StoreParticleName(particleName);
  aHit -> StoreParticleType(pdgEncoding);
  
  aHit -> StoreGlobalTime(globalTime);
  
  //aHit -> StoreHasBeenHit(hasBeenHit);
  //aHit -> StoreEdgeEventFlag(edgeEventFlag);
  //aHit -> SotreNbOfHits(nbOfHits);
  
  aHit -> StoreWorldPosition(worldPos);
  aHit -> StoreLocalPosition(localPos);
  //aHit -> StoreLocalExitPosition(localExitPos);
  aHit -> StoreOriginVertexPosition(originVertexPosition);
  
  aHit -> StoreWorldMomentum(worldMomentum);
  aHit -> StoreLocalMomentum(localMomentum);
  aHit -> StoreMomentumDirection(currentMomentumDirection);
  aHit -> StoreOriginVertexMomentumDirection(originVertexMomentumDirection);
  
  //aHit -> StoreOriginVertexThetaAngle; //calculated in EventAction
  //aHit -> StoreOriginVertexPhiAngle;
  
  aHit -> StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  aHit -> StoreOriginVertexTotalEnergy(originVertexTotalEnergy);  // kinetic energy
	
  aHit -> StoreKineticEnergy(currentKineticEnergy);
  aHit -> StoreTotalEnergy(currentTotalEnergy);
	
  //aHit -> StorePrimaryQ2(primaryQ2);
  //aHit -> StoreCrossSection(crossSection);
  //aHit -> StoreCrossSectionWeight(crossSectionWeight);

  //aHit -> StoreGlobalThetaAngle; //calculated in EventAction
  //aHit -> StoreGlobalPhiAngle;
	
  //--- LeadGlass deposited energy
  aHit -> StoreHitDepositedEnergy(depositedEnergy);
	
  //    aHit->Print();
	
  //----------------- check if it is first touch
	
  if ( !(aHit -> GetLogVolume()) )
    {
      //--- store translation and rotation matrix of the drift cell 
      //--- for the sake of drawing the hit 
      aHit -> StoreLogVolume(theTouchable->GetVolume()->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit -> StoreCellRotation(aTrans.NetRotation());
      aHit -> StoreCellPosition(aTrans.NetTranslation());
    }
	
  LeadGlass_DetectorHitsCollection->insert(aHit);  
	
  return true;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass_DetectorSD::EndOfEvent(G4HCofThisEvent* )
{
    //G4int NbDCHits = DC_hitsCollection->entries();
	
    //G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
    // 	     << " hits in the Drift Cells : " << G4endl;
    //for (G4int i=0;i<NbDCHits;i++) (
    //    *DC_hitsCollection)[i]->Print();
	
}



/////// --------------------------------------------------------------------



