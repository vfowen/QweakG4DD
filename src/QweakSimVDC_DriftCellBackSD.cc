
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimVDC_DriftCellBackSD.cc

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:47:36 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:47:36 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDC_DriftCellBackSD.hh"

// user includes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimVDC.hh"
#include "QweakSimVDC_DriftCellHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int    QweakSimVDC_DriftCellBackSD::DCNumberPerPlane  = 401;
G4double QweakSimVDC_DriftCellBackSD::DCWidthOnFrame    =  11.0*mm;
G4double QweakSimVDC_DriftCellBackSD::DCFullThickness   =  26.0*mm;
G4double QweakSimVDC_DriftCellBackSD::DCUPlaneWireAngle =  60.0*degree;
G4double QweakSimVDC_DriftCellBackSD::DCVPlaneWireAngle = -60.0*degree;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimVDC_DriftCellBackSD::QweakSimVDC_DriftCellBackSD(G4String name)
:G4VSensitiveDetector(name)
{
  //G4cout << G4endl << "###### Calling QweakSimVDC_DriftCellBackSD::QweakSimVDC_DriftCellBackSD() " << G4endl << G4endl; 

  collectionName.insert("DriftCellBackCollection"); 

  DC_ID = -1;

  //G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::QweakSimVDC_DriftCellBackSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimVDC_DriftCellBackSD::~QweakSimVDC_DriftCellBackSD()
{
	//G4cout << G4endl << "###### Calling QweakSimVDC_DriftCellBackSD::~QweakSimVDC_DriftCellBackSD() " << G4endl << G4endl; 
	
}		

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC_DriftCellBackSD::Initialize(G4HCofThisEvent* HCE)
{
  //G4cout << G4endl << "###### Calling QweakSimVDC_DriftCellBackSD::Initialize() " << G4endl << G4endl; 

   DC_hitsCollection = new QweakSimVDC_DriftCellHitsCollection(SensitiveDetectorName,collectionName[0]);

   // for(int i=0;i<DCNumberPerPlane;i++)
   //{ DC_hitsCollection->insert(new QweakSimVDC_DriftCellHit); }

   if(DC_ID<0)
     { DC_ID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
     //{ DC_ID = G4SDManager::GetSDMpointer()->GetCollectionID(DC_hitsCollection); }
   HCE->AddHitsCollection( DC_ID, DC_hitsCollection );
   
  //G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::Initialize() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//G4bool QweakSimVDC_DriftCellBackSD::ProcessHits(G4Step* aStep,G4TouchableHistory* /*ROhist*/)
G4bool QweakSimVDC_DriftCellBackSD::ProcessHits(G4Step* aStep,G4TouchableHistory* )
{
 //  G4cout << G4endl << "###### Calling QweakSimVDC_DriftCellBackSD::ProcessHits() " << G4endl << G4endl; 

//   G4double charge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();


//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Charge =" << charge << G4endl;

  // dismiss photons
//  if(charge==0.) {
    
//     G4cout << "==================================================================" << G4endl; 
//     G4cout << ">>>>       Neutral Particle detected (e.g. Photon)          <<<<<<" << G4endl; 
//     G4cout << ">>>> Up to now we don't count HITs for neutrals, therefore: <<<<<<" << G4endl; 
//     G4cout << ">>>>     Aborting QweakSimVDC_DriftCellBackSD::ProcessHits      <<<<<<" << G4endl; 
//    G4cout << "==================================================================" << G4endl;   

//    G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::ProcessHits() " << G4endl << G4endl; 

//   return false;
//  }  

  //=====================================================================================
  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
//   G4StepPoint*        postStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume*  physVol      = theTouchable->GetVolume();
  //=====================================================================================

  //   G4cout << "==================================================================" << G4endl; 
  //   G4cout << ">>>>>>       We are in volume :" << physVol->GetName() <<  "<<<<<<" << G4endl;
  //   G4cout << "==================================================================" << G4endl;   
  

  if( physVol->GetName().compare("VDC_DriftCellBack_Physical") == 0 ) 
  {
      //     G4cout << "==================================================================" << G4endl; 
      //     G4cout << ">>>>>>> Particle crossing  : VDC_DriftCellBack_Physical <<<<<<<<<" << G4endl; 
      //     G4cout << "==================================================================" << G4endl;       
      
      //const G4VProcess* process = aStep->GetPostStepPoint()->GetProcessDefinedStep();
      //G4cout << "@@@@@@@@@@@@@> Physical Processes in VDC_DriftCellBack_Physical = "<< process->GetProcessName() << G4endl;

  }
  else 
  { 
      //     G4cout << "==================================================================" << G4endl; 
      //     G4cout << ">>>> ERROR: We are not within a physical DriftCell Volume   <<<<<<" << G4endl; 
      //     G4cout << ">>>>        Aborting QweakSimVDC_DriftCellBackSD::ProcessHits   <<<<<<" << G4endl; 
      //     G4cout << "==================================================================" << G4endl;   
      
      return false;
  }

  //===============================================================================================
  // here we are only interested if the particle is crossing a boundary
  // otherwise we get additional hits due to physical processes within the sensitive volume 
  // 
  // If you want to identify the first step in a volume: pick fGeomBoundary status in preStepPoint
  // If you want to identify a step out of a volume    : pick fGeomBoundary status in postStepPoint
  //================================================================================================
  //
  if (preStepPoint->GetStepStatus() != fGeomBoundary) { 

      //       G4cout << "=======================================================================" << G4endl; 
      //       G4cout << ">>>> QweakSimVDC_DriftCellFrontSD: We are NOT crossing a boundary  <<<<<<" << G4endl; 
      //       G4cout << ">>>>       Aborting QweakSimVDC_DriftCellBackSD::ProcessHits      <<<<<<" << G4endl; 
      //       G4cout << "=======================================================================" << G4endl;
      //
      //       G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::ProcessHits() " << G4endl << G4endl; 

    return false;
  }


  G4double      currentKineticEnergy     = aStep->GetTrack()->GetKineticEnergy();
  G4double      currentTotalEnergy       = aStep->GetTrack()->GetTotalEnergy();
  G4ThreeVector currentMomentumDirection = aStep->GetTrack()->GetMomentumDirection();

//   G4int trackID = aStep->GetTrack()->GetTrackID();
//   G4cout << "====> Track ID     : " <<  trackID << G4endl;

//   G4int parentID = aStep->GetTrack()->GetParentID();
//   G4cout << "====> Parent ID    : " <<  parentID << G4endl;


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

  
//   G4int    MotherCopyNo    = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume
//   G4int DriftCellCopyNo    = theTouchable->GetVolume()->GetCopyNo();    // but several Driftcells per MV
  G4int DriftCellReplicaNo = theTouchable->GetReplicaNumber();    // but several Driftcells per MV

//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront MV    CopyNumber :" <<    MotherCopyNo    << G4endl; 
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront       CopyNumber :" << DriftCellCopyNo    << G4endl; 
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront    ReplicaNumber :" << DriftCellReplicaNo << G4endl; 
  
  
  G4ThreeVector worldPos = preStepPoint->GetPosition();
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront WorldPos.X [cm]:" << worldPos.x()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront WorldPos.Y [cm]:" << worldPos.y()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront WorldPos.Z [cm]:" << worldPos.z()/cm << G4endl;
  
  G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront LocalPos.X [cm]:" << localPos.x()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront LocalPos.Y [cm]:" << localPos.y()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  VDC_DriftCellFront LocalPos.Z [cm]:" << localPos.z()/cm << G4endl;
  
  QweakSimVDC_DriftCellHit* aHit = new QweakSimVDC_DriftCellHit(DriftCellReplicaNo);
  //QweakSimVDC_DriftCellHit* aHit = (*DC_hitsCollection)[DriftCellReplicaNo];
  
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  got QweakSimVDC_DriftCellHit* aHit" << G4endl;

  aHit->StoreWorldPos(worldPos);
  aHit->StoreLocalPos(localPos);
  aHit->StoreTime(preStepPoint->GetGlobalTime());

  aHit->StoreOriginVertexPosition(originVertexPosition);
  aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);

  aHit->StoreMomentumDirection(currentMomentumDirection);
  aHit->StoreKineticEnergy(currentKineticEnergy);
  aHit->StoreTotalEnergy(currentTotalEnergy);


  G4double myDCUPlaneWireAngle =  90.0*degree - DCUPlaneWireAngle;
  G4double myDCVPlaneWireAngle = -90.0*degree - DCVPlaneWireAngle;

//   G4cout << " DCWidthOnFrame    [mm]  = " << DCWidthOnFrame/mm          << G4endl;
//   G4cout << " DCFullThickness   [mm]  = " << DCFullThickness/mm         << G4endl;
//   G4cout << " DCUPlaneWireAngle [deg] = " << myDCUPlaneWireAngle/degree << G4endl;
//   G4cout << " DCVPlaneWireAngle [deg] = " << myDCVPlaneWireAngle/degree << G4endl;

  aHit->StoreDCWidthOnFrame(DCWidthOnFrame);
  aHit->StoreDCFullThickness(DCFullThickness);
  aHit->StoreDCUPlaneWireAngle(myDCUPlaneWireAngle);
  aHit->StoreDCVPlaneWireAngle(myDCVPlaneWireAngle);



  // check if it is first touch
  if(!(aHit->GetLogV()))
    {
      // store translation and rotation matrix of the drift cell 
      // for the sake of drawing the hit 
      aHit->StoreLogV(physVol->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->StoreCellRot(aTrans.NetRotation());
      aHit->StoreCellPos(aTrans.NetTranslation());
    }
  
  if( physVol->GetName().compare("VDC_DriftCellFront_Physical") == 0 ) { aHit->StoreDriftCellPlaneID(0);}
  if( physVol->GetName().compare("VDC_DriftCellBack_Physical")  == 0 ) { aHit->StoreDriftCellPlaneID(1);}
  
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  before inserting the hit" << G4endl;

  DC_hitsCollection->insert(aHit); 

//   G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::ProcessHits() " << G4endl << G4endl; 
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void QweakSimVDC_DriftCellBackSD::EndOfEvent(G4HCofThisEvent*  HCE)
void QweakSimVDC_DriftCellBackSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimVDC_DriftCellBackSD::EndOfEvent() " << G4endl << G4endl; 
  
//   G4int NbDCHits = DC_hitsCollection->entries();
  
//   G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
// 	 << " hits in the Drift Cells : " << G4endl;
//   for (G4int i=0;i<NbDCHits;i++) (*DC_hitsCollection)[i]->Print();
  


   //G4cout << G4endl << "###### Leaving QweakSimVDC_DriftCellBackSD::EndOfEvent() " << G4endl << G4endl; 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellBackSD.cc,v $
//      Revision 1.4  2006/05/05 21:47:36  grimm
//      Seperation into DriftCellBack and DriftCellFront for testing purpose.
//
//      Revision 1.3  2006/01/02 13:24:22  grimm
//      Commenting the originVertexPosition cut (z> 635*cm). Now I'm allowing to record all charged hits of the drift cell regardless of the vertex origin.
//      (With the target cut I got ~20k drift cell hits out of 300k primary events. The wire planes without origin cut get a hit quote of 30%)
//
//      Revision 1.2  2005/12/27 19:19:16  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
