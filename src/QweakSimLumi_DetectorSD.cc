#include "QweakSimLumi_DetectorSD.hh"
#include "QweakSimLumi_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimSensitiveDetectorDefinition.hh"

QweakSimLumi_DetectorSD::QweakSimLumi_DetectorSD(G4String name):G4VSensitiveDetector(name) {
    collectionName.insert("LumiCollection");
    Lumi_CollectionID = -1;
}

QweakSimLumi_DetectorSD::~QweakSimLumi_DetectorSD() {
    //delete Lumi_HitCollection;
}

void QweakSimLumi_DetectorSD::Initialize(G4HCofThisEvent* HCE) {
    Lumi_DetectorHitsCollection = new QweakSimLumi_DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    Lumi_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    HCE->AddHitsCollection(Lumi_CollectionID, Lumi_DetectorHitsCollection);
}

G4bool QweakSimLumi_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    G4int motherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();

    G4double trackID = aStep->GetTrack()->GetTrackID();

    G4ParticleDefinition* fpParticleDefinition = aStep->GetTrack()->GetDefinition();
    G4String particleName = fpParticleDefinition->GetParticleName();

    G4int pdgEncoding = fpParticleDefinition->GetPDGEncoding();

    G4double      globalTime   = aStep->GetPreStepPoint()->GetGlobalTime();

    G4ThreeVector worldPos             = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector localPos             = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
    G4ThreeVector originVertexPosition = aStep->GetTrack()->GetVertexPosition();

    G4ThreeVector worldMomentum                 = aStep->GetPreStepPoint()->GetMomentum();
    G4ThreeVector localMomentum                 = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
    G4ThreeVector currentMomentumDirection      = aStep->GetTrack()->GetMomentumDirection();
    G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();

    G4double      originVertexKineticEnergy = aStep->GetTrack()->GetVertexKineticEnergy();
    G4double      originVertexTotalEnergy   = aStep->GetTrack()->GetVertexKineticEnergy();//GetVertexTotalEnergy();

    G4double      currentKineticEnergy      = aStep->GetTrack()->GetKineticEnergy();
    G4double      currentTotalEnergy        = aStep->GetTrack()->GetTotalEnergy();

    G4double      depositedEnergy      = aStep->GetTotalEnergyDeposit();

    QweakSimLumi_DetectorHit* aHit = new QweakSimLumi_DetectorHit(motherCopyNo);

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

    aHit -> StoreHitDepositedEnergy(depositedEnergy);

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

    Lumi_DetectorHitsCollection->insert(aHit);  

    return true;
}

void QweakSimLumi_DetectorSD::EndOfEvent(G4HCofThisEvent*) {
    // placeholder 
}
