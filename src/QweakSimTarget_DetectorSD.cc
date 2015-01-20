
// QweakSimTarget_DetectorSD.cc
// Martin McHugh
// 2013-07-20

/////// --------------------------------------------------------------------

#include "QweakSimTarget_DetectorSD.hh"

//--- user classes
#include "QweakSimTarget_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimSensitiveDetectorDefinition.hh"

/////// --------------------------------------------------------------------

QweakSimTarget_DetectorSD::QweakSimTarget_DetectorSD(G4String name)
: G4VSensitiveDetector(name)
{
    collectionName.insert("TargetCollection");
    Target_DetectorHitsCollection = 0;
    Target_CollectionID = -1;
}

/////// --------------------------------------------------------------------

void QweakSimTarget_DetectorSD::Initialize(G4HCofThisEvent* HCE)
{	
    Target_DetectorHitsCollection = new QweakSimTarget_DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
    Target_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    HCE->AddHitsCollection(Target_CollectionID, Target_DetectorHitsCollection);
}

/////// --------------------------------------------------------------------

G4bool QweakSimTarget_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{	
    //--- Not Entering Geometry	
    if (aStep->GetPreStepPoint()->GetStepStatus() != fGeomBoundary ) return false;
	
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();

    //G4double    parentID     = aStep->GetTrack()->GetParentID();
    G4double      trackID      = aStep->GetTrack()->GetTrackID();
	
    G4ParticleDefinition*  fpParticleDefinition = aStep->GetTrack()->GetDefinition();
    G4String	particleName = fpParticleDefinition->GetParticleName();
    //G4double	pdgCharge    = fpParticleDefinition->GetPDGCharge();
    G4int	pdgEncoding  = fpParticleDefinition->GetPDGEncoding();
	
    //GlobalTimeOfHit
    G4double      globalTime   = aStep->GetPreStepPoint()->GetGlobalTime();
	
    G4ThreeVector worldPos             = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector localPos             = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

    // Local Origin (where did the hit come from)
    G4ThreeVector originVertexPosition = aStep->GetTrack()->GetVertexPosition();

    G4ThreeVector worldMomentum                 = aStep->GetPreStepPoint()->GetMomentum();
    G4ThreeVector localMomentum                 = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
    G4ThreeVector currentMomentumDirection      = aStep->GetTrack()->GetMomentumDirection();
    G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();

    G4double      originVertexKineticEnergy = aStep->GetTrack()->GetVertexKineticEnergy();
    G4double      originVertexTotalEnergy   = aStep->GetTrack()->GetVertexKineticEnergy();//GetVertexTotalEnergy();
	
    G4double      currentKineticEnergy      = aStep->GetTrack()->GetKineticEnergy();
    G4double      currentTotalEnergy        = aStep->GetTrack()->GetTotalEnergy();
	
    //--- Target deposited energy
    G4double      depositedEnergy      = aStep->GetTotalEnergyDeposit();
	
	
    //----------------- Store Hit information
	
    QweakSimTarget_DetectorHit* aHit = new QweakSimTarget_DetectorHit();
	
    aHit -> StoreTrackID(trackID);
	
    aHit -> StoreParticleName(particleName);
    aHit -> StoreParticleType(pdgEncoding);
	
    aHit -> StoreGlobalTime(globalTime);
		
    aHit -> StoreWorldPosition(worldPos);
    aHit -> StoreLocalPosition(localPos);
    aHit -> StoreOriginVertexPosition(originVertexPosition);
	
    aHit -> StoreWorldMomentum(worldMomentum);
    aHit -> StoreLocalMomentum(localMomentum);
    aHit -> StoreMomentumDirection(currentMomentumDirection);
    aHit -> StoreOriginVertexMomentumDirection(originVertexMomentumDirection);
	
    aHit -> StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
    aHit -> StoreOriginVertexTotalEnergy(originVertexTotalEnergy);  // kinetic energy
	
    aHit -> StoreKineticEnergy(currentKineticEnergy);
    aHit -> StoreTotalEnergy(currentTotalEnergy);
	
    //--- Target deposited energy
    aHit -> StoreDepositedEnergy(depositedEnergy);
	
	
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
	
	Target_DetectorHitsCollection->insert(aHit);
	
	return true;
}

/////// --------------------------------------------------------------------

void QweakSimTarget_DetectorSD::EndOfEvent(G4HCofThisEvent* )
{
    //G4int NbDCHits = DC_hitsCollection->entries();
	
    //G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
    // 	     << " hits in the Drift Cells : " << G4endl;
    //for (G4int i=0;i<NbDCHits;i++) (
    //    *DC_hitsCollection)[i]->Print();
}

/////// --------------------------------------------------------------------
