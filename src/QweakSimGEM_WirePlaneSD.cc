//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimGEM_WirePlaneSD.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:39:28 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGEM_WirePlaneSD.hh"

// user includes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimGEM_WirePlaneHit.hh"
#include "QweakSimTrackInformation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGEM_WirePlaneSD::QweakSimGEM_WirePlaneSD(G4String name)
:G4VSensitiveDetector(name)
{
//  G4cout << G4endl << "###### Calling QweakSimGEM_WirePlaneSD::QweakSimGEM_WirePlaneSD() " << G4endl << G4endl; 

  collectionName.insert("GEMWirePlaneCollection"); //collectionName[0]
   HCID = -1;

//  G4cout << G4endl << "###### Leaving QweakSimGEM_WirePlaneSD::QweakSimGEM_WirePlaneSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimGEM_WirePlaneSD::~QweakSimGEM_WirePlaneSD()
{
  //G4cout << G4endl << "###### Calling QweakSimGEM_WirePlaneSD::~QweakSimGEM_WirePlaneSD() " << G4endl << G4endl; 
  //delete hitsCollection;
  //G4cout << G4endl << "###### Leaving QweakSimGEM_WirePlaneSD::~QweakSimGEM_WirePlaneSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM_WirePlaneSD::Initialize(G4HCofThisEvent* HCE)
{
  //G4cout << G4endl << "###### Calling QweakSimGEM_WirePlaneSD::Initialize() " << G4endl << G4endl; 

    hitsCollection     = new QweakSimGEM_WirePlane_HitsCollection(SensitiveDetectorName,collectionName[0]);
    
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
    
    HCE->AddHitsCollection( HCID, hitsCollection );
    
  //G4cout << G4endl << "###### Leaving QweakSimGEM_WirePlaneSD::Initialize() " << G4endl << G4endl; 

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool QweakSimGEM_WirePlaneSD::ProcessHits(G4Step* aStep,G4TouchableHistory* /*ROhist*/)
{
  //G4cout << G4endl << "###### Calling QweakSimGEM_WirePlaneSD::ProcessHits() " << G4endl << G4endl; 


  G4double charge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();

//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Charge =" << charge << G4endl;

  // dismiss photons
  if(charge==0.) return false;


  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
  G4StepPoint*        postStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume*  physVol      = theTouchable->GetVolume();

  // we are only interested if the particle is crossing a boundary (glass->vaccuum)
  if (postStepPoint->GetStepStatus() != fGeomBoundary) { 
//       G4cout << "=======================================================================" << G4endl; 
//       G4cout << ">>>> QweakSimGEM_WirePlaneSD: We are NOT crossing a boundary  <<<<<<" << G4endl; 
//       G4cout << ">>>>       Aborting QweakSimGEM_WirePlaneSD::ProcessHits      <<<<<<" << G4endl; 
//       G4cout << "=======================================================================" << G4endl;   

    return false;
  }

//   G4cout << "================== We are in volume :" << physVol->GetName() << G4endl << G4endl;


  if(strcmp(physVol->GetName(),"GEM_AnodeCopperLayer_Physical") == 0 ) {

//    G4cout << "=============================================================" << G4endl;
//    G4cout << ">>>>>>> Particle crossing  : GEM_AnodeCopperLayer_Physical <<<<<<<<<" << G4endl;
//    G4cout << "=============================================================" << G4endl;

//     G4int trackID = aStep->GetTrack()->GetTrackID();
//     G4cout << "====> Track ID     : " <<  trackID << G4endl;
    
//     G4int parentID = aStep->GetTrack()->GetParentID();
//     G4cout << "====> Parent ID    : " <<  parentID << G4endl;
  
  

//     G4int    MotherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();  // Several MotherVolumes
    G4int WirePlaneCopyNo = theTouchable->GetVolume()->GetCopyNo();   // but only one WirePlane per MV
//     G4int MotherReplicaNo = theTouchable->GetReplicaNumber(1);        // Several MotherVolumes

//pqwang@jlab.org
//there are 3 fold MotherVolume, the GEMID must be taken from the outer container
// for decoding correct GEMID in the EventAction
//    G4int    MotherCopyNo2 = theTouchable->GetVolume(2)->GetCopyNo();  // Several MotherVolumes
//    G4int MotherReplicaNo2 = theTouchable->GetReplicaNumber(2);        // Several MotherVolumes

    G4int    MotherCopyNo3 = theTouchable->GetVolume(3)->GetCopyNo();  // Several MotherVolumes
//     G4int MotherReplicaNo3 = theTouchable->GetReplicaNumber(3);        // Several MotherVolumes

//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane MV    CopyNumber  :" << MotherCopyNo    << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane       CopyNumber  :" << WirePlaneCopyNo << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane    ReplicaNumber  :" << MotherReplicaNo << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane MV    CopyNumber2 :" << MotherCopyNo2    << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane    ReplicaNumber2 :" << MotherReplicaNo2 << G4endl;
    

    G4ThreeVector worldPos = preStepPoint->GetPosition();
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldPos.X [cm]:" << worldPos.x()/cm << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldPos.Y [cm]:" << worldPos.y()/cm << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldPos.Z [cm]:" << worldPos.z()/cm << G4endl;
    
    G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalPos.X [cm]:" << localPos.x()/cm << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalPos.Y [cm]:" << localPos.y()/cm << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalPos.Z [cm]:" << localPos.z()/cm << G4endl;
  
    G4ThreeVector worldMomentum = preStepPoint->GetMomentum();
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.X [GeV]:" << worldMomentum.x()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.Y [GeV]:" << worldMomentum.y()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.Z [GeV]:" << worldMomentum.z()/GeV << G4endl;
    
    G4ThreeVector localMomentum = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.X [GeV]:" << localMomentum.x()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.Y [GeV]:" << localMomentum.y()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.Z [GeV]:" << localMomentum.z()/GeV << G4endl;

  G4double      currentKineticEnergy     = preStepPoint->GetKineticEnergy();
  G4double      currentTotalEnergy       = preStepPoint->GetTotalEnergy();

 // Vertex: where this track was generated
  G4ThreeVector originVertexPosition          = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double      originVertexKineticEnergy     = aStep->GetTrack()->GetVertexKineticEnergy();

//   G4cout << "====> originVertexPosition_X [cm]     : " <<  originVertexPosition.x()/cm << G4endl;
//   G4cout << "====> originVertexPosition_Y [cm]     : " <<  originVertexPosition.y()/cm << G4endl;
//   G4cout << "====> originVertexPosition_Z [cm]     : " <<  originVertexPosition.z()/cm << G4endl;

//   G4cout << "====> originVertexMomentumDirection_X : " <<  originVertexMomentumDirection.x() << G4endl;
//   G4cout << "====> originVertexMomentumDirection_Y : " <<  originVertexMomentumDirection.y() << G4endl;
//   G4cout << "====> originVertexMomentumDirection_Z : " <<  originVertexMomentumDirection.z() << G4endl;

//   G4cout << "====> originVertexKineticEnergy [Mev] : " <<  originVertexKineticEnergy/MeV << G4endl;



//   G4double target_zcut = -630*cm;

//    if  (originVertexPosition.z()/cm > target_zcut/cm)
//      {
// 	G4cout << "################################################################" << G4endl;
// 	G4cout << ">>>>>>>>>>>>    originVertexPosition.z > 630cm !!!   <<<<<<<<<<<" << G4endl;
// 	G4cout << ">>>>>>>>>>>>    Track does not origin from target    <<<<<<<<<<<" << G4endl;
// 	G4cout << ">>>>>>>>>>>>   Aborting QweakSimGEM_WirePlaneSD::ProcessHits() <<<<<<<<<<<" << G4endl;
// 	G4cout << "################################################################" << G4endl;
//	
//	return false;
//
//      }

//   // get User Track Info
//   QweakSimTrackInformation* info = (QweakSimTrackInformation*) (aStep->GetTrack()->GetUserInformation());
//   info->Print();

//   G4double primaryQ2                      = info->GetPrimaryQ2();
//   G4double crossSection                   = info->GetCrossSection();
//   G4double crossSectionWeight             = info->GetCrossSectionWeight();
//   G4int    primaryEventNumber             = info->GetPrimaryEventNumber();

//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original Track Q2                 : " << primaryQ2                       << G4endl;
//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original Track Event Number       : " << primaryEventNumber              << G4endl;
//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original CrossSection Weight (ub) : " << crossSectionWeight              << G4endl << G4endl;



//  G4cout << " =====> Storing GEM hit information into aHit" << G4endl;

    //   QweakSimGEMHit* aHit = new QweakSimGEMHit(MotherCopyNo); // there is only one plane per motherVolume
    QweakSimGEM_WirePlaneHit* aHit = new QweakSimGEM_WirePlaneHit(); // there is only one plane per motherVolume

//pqwang@jlab.org
//there are 3 fold MotherVolume, the GEMID must be taken from the outer container
// for decoding correct GEMID in the EventAction 
    aHit->StoreGEMID(MotherCopyNo3);         // 0: Front GEM       , 1: Back GEM
    aHit->StoreWirePlaneID(WirePlaneCopyNo);    // [0,5] : WirePlane #0 to #5 (6 wire plane in total per GEM)

    aHit->StoreWorldPosition(worldPos);
    aHit->StoreLocalPosition(localPos);

    aHit->StoreWorldMomentum(worldMomentum);
    aHit->StoreLocalMomentum(localMomentum);

    aHit->StoreGlobalTime(preStepPoint->GetGlobalTime());
    
    aHit->StoreOriginVertexPosition(originVertexPosition);
    aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);
    aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);

//     aHit->StorePrimaryQ2(primaryQ2);
//     aHit->StoreCrossSection(crossSection);
//     aHit->StoreCrossSectionWeight(crossSectionWeight);
//     aHit->StorePrimaryEventNumber(primaryEventNumber);

    aHit->StoreKineticEnergy(currentKineticEnergy);
    aHit->StoreTotalEnergy(currentTotalEnergy);


    // now store all the hit information into the hit collection
    hitsCollection->insert(aHit);

    //delete aHit;  // NOT ALLOWED, Geant4 crashes
  
  } // end of  if(strcmp(physVol->GetName(),"GEM_WirePlane_Physical")==0)


  //G4cout << G4endl << "###### Leaving QweakSimGEM_WirePlaneSD::ProcessHits() " << G4endl << G4endl; 

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void QweakSimGEM_WirePlaneSD::EndOfEvent(G4HCofThisEvent*  HCE)
void QweakSimGEM_WirePlaneSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimGEM_WirePlaneSD::EndOfEvent() " << G4endl << G4endl; 

//      G4int NbHits = hitsCollection->entries();
//       G4cout << "\n-------->Hits Collection: in this event they are " << NbHits
//              << " hits in the Wire Planes: " << G4endl;
//       for (G4int i=0;i<NbHits;i++) (*hitsCollection)[i]->Print();

   //G4cout << G4endl << "###### Leaving QweakSimGEM_WirePlaneSD::EndOfEvent() " << G4endl << G4endl; 

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
