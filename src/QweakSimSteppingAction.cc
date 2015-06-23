//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimSteppingAction.hh"

// geant4 includes
#include "G4TrackVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OpticalPhoton.hh"
#include "G4PionMinus.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"

// user includes
#include "QweakSimUserInformation.hh"
#include "QweakSimSteppingVerbose.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimEPEvent.hh"
#include "QweakSimCerenkovDetector_PMTSD.hh"
#include "QweakSimPMTOnly_PMTSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimSteppingAction::QweakSimSteppingAction(QweakSimUserInformation* myUInfo, QweakSimEPEvent* myEPEvent)
{

    G4cout << "###### Calling QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;

    myEventCounter = 0;
    fSecondary = NULL;
    myUserInfo = myUInfo;

    myEvent = myEPEvent;

    evtGenStatus = 0;
    targetCenterPositionZ = myUserInfo->TargetCenterPositionZ;

    fout=new TFile("o_tuple.root","RECREATE");	
    tout=new TNtuple("t","Ntuple primary info in Pb",
		     "be:bx:by:bz:bpx:bpy:bpz:bdpx:bdpy:bdpz:ae:ax:ay:az:apx:apy:apz:adpx:adpy:adpz:angle:process:stepL:evN:trackID:parentID:pType:polX:polY:polZ");
    G4cout << "###### Leaving QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimSteppingAction::UserSteppingAction(const G4Step* theStep) {

  fSecondary = fpSteppingManager->GetfSecondary();

  // ** all the track info is postStep **
  G4Track*              theTrack     = theStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  G4StepPoint*          thePrePoint  = theStep->GetPreStepPoint();
  G4VPhysicalVolume*    thePrePV     = thePrePoint->GetPhysicalVolume();
  G4StepPoint*          thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume*    thePostPV    = thePostPoint->GetPhysicalVolume();
  G4TouchableHistory*   theTouchable = (G4TouchableHistory*)(thePrePoint->GetTouchable());
  G4String              particleName = theTrack->GetDefinition()->GetParticleName();
  G4ProcessManager*     pm           = particleType->GetProcessManager();
  
  //get material
  G4Material* theMaterial = theTrack->GetMaterial();
  
  //to get the kryptonie to work
  if(theMaterial->GetName()=="Kryptonite"){
    theTrack->SetTrackStatus(fKillTrackAndSecondaries);
  }
  
  G4int parentID = theTrack->GetParentID();
  if( (particleType==G4Electron::ElectronDefinition()||particleType==G4PionMinus::PionMinusDefinition())
      && parentID==0 ) {
    
    //jpan: to account for the energy loss before the event generation,
    //      force to change primary momentum direction here
    
    //scattering only occur inside reaction region of the target, only occur once
    G4ThreeVector thePosition = theTrack->GetPosition();
    G4double theX = thePosition.getX();
    G4double theY = thePosition.getY();
    G4double theZ = thePosition.getZ();
    
    G4String procName = thePostPoint->GetProcessDefinedStep()->GetProcessName();
    // dEE in MeV -> all Elosses are in MeV
    G4double dEE = thePrePoint->GetKineticEnergy()/MeV-thePostPoint->GetKineticEnergy()/MeV;
    
    
    // need this here, else the track might get out of physical volume,
    //  and crash the program
    if(!thePostPV || !thePrePV)	return;
    
    // various energy losses at the target
    if(((thePrePV->GetName()).contains("QweakTarget") ||
	(thePostPV->GetName()).contains("QweakTarget"))) {
      if (procName.compare("msc")==0)
	myUserInfo->AddTodEMscOut(dEE);
      else if(procName.compare("eIoni")==0)
	myUserInfo->AddTodEIonOut(dEE);
      else if(procName.compare("eBrem")==0)
	myUserInfo->AddTodEBremOut(dEE);      
    }
    
  }// if primary 


    
  // Events that happen in the Pb FIXME
  // debug toggle !!!! it prints out a lot of things
  G4bool debugPrint=false;
  // toggle to write out e\pm/gammas on top of primary electrons !! really big files
  G4bool writeOutAll=false;
  // toggle for filling the Pb ntuple
  G4bool fillNtuple=true; 
  
  int _trackID=theStep->GetTrack()->GetTrackID(); 
  int _parentID = theStep->GetTrack()->GetParentID();
  double _priE=theStep->GetTrack()->GetTotalEnergy();
  G4String _name=theStep->GetTrack()->GetDefinition()->GetParticleName();
  G4String _pn=thePostPoint->GetProcessDefinedStep()->GetProcessName();
  G4ThreeVector _polarization=theStep->GetTrack()->GetPolarization();
  G4Material *_material=thePostPoint->GetMaterial();
  
  if(_material){

    if(_material->GetName().compare("PBA")==0){ // perform this only in the Radiator

      /*
	Brem depolarization: PhysRev.114.887
	implemented only for transverse polarization
	will decrease the overall polarization by a functional form from figure 5 in the paper      
      */
      // if(_polarization.getR()>0.2 && particleType==G4Electron::ElectronDefinition() ){
      //   G4cout<<G4endl<<_polarization.getR()<<" "<<_polarization.getX()<<" "<<_polarization.getY()<<" "<<_polarization.getZ()<<" "<<G4endl;
      //   theStep->GetTrack()->SetPolarization(_polarization*0.9);
      //   G4cout<<_polarization.getR()<<" "<<_polarization.getX()<<" "<<_polarization.getY()<<" "<<_polarization.getZ()<<" "<<G4endl;
      // }    

      // either write out only the primaries or all e\pm and gammas
      if(((particleType==G4Positron::PositronDefinition() ||
	   particleType==G4Electron::ElectronDefinition() ||
	   particleType==G4Gamma::GammaDefinition()) && writeOutAll) ||
	 (particleType==G4Electron::ElectronDefinition() && _parentID==0) ) {
	
	// "be:bx:by:bz:bpx:bpy:bpz:bdpx:bdpy:bdpz:
	//  ae:ax:ay:az:apx:apy:apz:adpx:adpy:adpz:
	//  angle:process:stepL:evN:trackID:parentID:pType:
	//  polX:polY:polZ"
	float _var[30];
	_var[0] = thePrePoint->GetTotalEnergy();
	_var[1] = thePrePoint->GetPosition().getX();
	_var[2] = thePrePoint->GetPosition().getY();
	_var[3] = thePrePoint->GetPosition().getZ();
	_var[4] = thePrePoint->GetMomentum().getX();
	_var[5] = thePrePoint->GetMomentum().getY();
	_var[6] = thePrePoint->GetMomentum().getZ();
	_var[7] = thePrePoint->GetMomentumDirection().getX();
	_var[8] = thePrePoint->GetMomentumDirection().getY();
	_var[9] = thePrePoint->GetMomentumDirection().getZ();
	_var[10]= thePostPoint->GetTotalEnergy();
	_var[11]= thePostPoint->GetPosition().getX();
	_var[12]= thePostPoint->GetPosition().getY();
	_var[13]= thePostPoint->GetPosition().getZ();
	_var[14]= thePostPoint->GetMomentum().getX();
	_var[15]= thePostPoint->GetMomentum().getY();
	_var[16]= thePostPoint->GetMomentum().getZ();
	_var[17]= thePostPoint->GetMomentumDirection().getX();
	_var[18]= thePostPoint->GetMomentumDirection().getY();
	_var[19]= thePostPoint->GetMomentumDirection().getZ();
	
	const G4ThreeVector _preP=thePrePoint->GetMomentumDirection();
	const G4ThreeVector _postP=thePostPoint->GetMomentumDirection();
	float scatAng=_postP.angle(_preP);
	_var[20]=scatAng;
	if(_pn.compare("msc")==0)
	  _var[21]=1;
	else if(_pn.compare("CoulombScat")==0)
	  _var[21]=2;
	else if(_pn.compare("eBrem")==0)
	  _var[21]=3;
	else if(_pn.compare("Transportation")==0)
	  _var[21]=4;
	else if(_pn.compare("eIoni")==0)
	  _var[21]=5;
	else
	  _var[21]=0;
	
	double _steplength=theStep->GetStepLength(); // gives slightly larger values that the diff in position
	_var[22]=_steplength;
	_var[23]=myUserInfo->GetPrimaryEventNumber();
	_var[24]=_trackID;
	_var[25]=_parentID;
	
	G4cout<<" PDGEncoding for electron "<<particleType->GetPDGEncoding()<<G4endl;
	if(particleType==G4Positron::PositronDefinition()) _var[26]=-11;
	else if(particleType==G4Gamma::GammaDefinition()) _var[26]=22;
	else if(particleType==G4Electron::ElectronDefinition()) _var[26]=11;
	else _var[26]=-999;
	
	_var[27]=_polarization.getX();
	_var[28]=_polarization.getY();
	_var[29]=_polarization.getZ();
	
	if(fillNtuple)
	  tout->Fill(_var);
	
	if(debugPrint){
	  G4cout<<"~Primary: "<<_trackID<<" "<<_parentID<<" "<<_priE<<" "<<_pn<<" "<<_name<<" "
		<<_material->GetName()<<" angle "<<scatAng<<" "<<_pn<<" "<<_steplength<<G4endl;
	  G4cout<<"  preP R th phi "<<_preP.getR()<<" "<<_preP.getTheta()<<" "<<_preP.getPhi()<<G4endl;
	  G4cout<<" postP R th phi "<<_postP.getR()<<" "<<_postP.getTheta()<<" "<<_postP.getPhi()<<G4endl;
	  G4cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<G4endl;
	}
      }
    }
  }
  
  if(particleType==G4Electron::ElectronDefinition())
    {
      G4ThreeVector worldPos = thePrePoint->GetPosition();
      G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
      
      if((!strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalRight") ||
	  !strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalLeft")) &&
	 (!strcmp(thePrePV->GetName(),"ActiveArea_Physical") ||
	  !strcmp(thePrePV->GetName(),"CerenkovMasterContainer_Physical")))
        {
	  //     if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"CerenkovDetector_Physical") &&
	  //        !strcmp(thePrePV->GetName(),"CerenkovContainer_Physical")){
	  myUserInfo->StoreLocalCerenkovExitPosition(localPos);
        }
    }
  
  //   QweakSimTrackInformation *TrackInfo = (QweakSimTrackInformation*)theTrack->GetUserInformation();
  
  //pqwang: optical photon process
  
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4OpBoundaryProcess* boundary=NULL;
  
  if(!boundary) {
    //    G4ProcessManager* pm
    //      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    for(G4int i=0; i<nprocesses; i++) {
      if((*pv)[i]->GetProcessName()=="OpBoundary") {
	boundary = (G4OpBoundaryProcess*)(*pv)[i];
	break;
      }
    }
  }
  
  if(!thePostPV) {
    return;
  }
  
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()) {
    boundaryStatus=boundary->GetStatus();
    if(thePostPoint->GetStepStatus()==fGeomBoundary) {
      switch(boundaryStatus) {
      case Absorption:
	{
	  //std::cout<<"Absorption"<<std::endl;
	  break;
	}
      case Detection:
	{
	  //std::cout<<"Detected a photon."<<std::endl;
	  G4SDManager* SDman = G4SDManager::GetSDMpointer();
	  if(strcmp(thePostPV->GetName(),"PMTOnlyCathode_Physical") == 0) {
	    //std::cout << "Optical Photon hit pmtonl cathode" << std::endl;
	    G4String pmtonlSDName="PMTOnly_PMTSD";
	    QweakSimPMTOnly_PMTSD* pmtonlSD = (QweakSimPMTOnly_PMTSD*)SDman->FindSensitiveDetector(pmtonlSDName);
	    if(pmtonlSD) {
	      //myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
	      pmtonlSD->ProcessHits_constStep(theStep,NULL);
	      theTrack->SetTrackStatus(fStopAndKill);
	    }
	    break;
	  } else {
	    G4String CerenkovSDName="/CerenkovPMTSD";
	    QweakSimCerenkovDetector_PMTSD* cerenkovpmtSD = (QweakSimCerenkovDetector_PMTSD*)SDman->FindSensitiveDetector(CerenkovSDName);
	    if(cerenkovpmtSD) {
	      //myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
	      cerenkovpmtSD->ProcessHits_constStep(theStep,NULL);
	      theTrack->SetTrackStatus(fStopAndKill);
	    }
	    break;
	  }
	}
      case FresnelReflection:
	{
	  //std::cout<<"FresnelReflection"<<std::endl;
	  break;
	}
      case TotalInternalReflection:
	{
	  //std::cout<<"TotalInternalReflection"<<std::endl;
	  break;
	}
      case SpikeReflection:
	{
	  //std::cout<<"SpikeReflection"<<std::endl;
	  break;
	}
      default:
	{
	  //std::cout<<"Undefined"<<std::endl;
	  break;
	}
      }
    }
  }  // end of optical photon process
  
  
  //   if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
  //
  //     if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"PMTEntranceWindow_Physical")){
  //       if(!strcmp(thePrePV->GetName(),"Cathode_Physical")){
  //
  //       myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
  // 	// 	theTrack->SetTrackStatus(fStopAndKill);
  //       }
  //     }
  //   }
  
  myUserInfo->StoreStepVolumeName(thePrePV->GetName());
  
  //======================================================================
  //   Stolen from GATE code:
  //
  //   In a few random cases, a particle gets 'stuck' in an
  //   an infinite loop in the geometry. It then oscillates until GATE
  //   crashes on some out-of-memory error.
  //   To prevent this from happening, I've added below a quick fix where
  //   particles get killed when their step number gets absurdely high
  
  //jpan@nuclear.uwinnipeg.ca
  //The following codes cause the electron tracks killed at the edge of magnetic field
  //This must be avoid by increasing the 10000 steps to 100000.
  
  if ( theStep->GetTrack()->GetCurrentStepNumber() > 100000 )
    theStep->GetTrack()->SetTrackStatus(fStopAndKill);
  return;
}       // end of QweakSimSteppingAction::UserSteppingAction

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int QweakSimSteppingAction::GetTrackVectorStartIndex()
{
    if(!fSecondary) return -1;

    return (*fSecondary).size() - GetTotalNumOfSecondaries();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int QweakSimSteppingAction::GetTrackVectorSize()
{
    if(!fSecondary) return 0;
    return (*fSecondary).size();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ParticleDefinition *QweakSimSteppingAction::GetSecondaryParticleDefinition(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return NULL;

    return (*fSecondary)[idx]->GetDefinition();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String QweakSimSteppingAction::GetSecondaryParticleName(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return "undefined";

    return (*fSecondary)[idx]->GetDefinition()->GetParticleName();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleTotalEnergy(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return -1;

    return (*fSecondary)[idx]->GetTotalEnergy();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleKineticEnergy(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return -1;

    return (*fSecondary)[idx]->GetKineticEnergy();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleXOrigin(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6;

    return (*fSecondary)[idx]->GetPosition().x();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleYOrigin(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6;

    return (*fSecondary)[idx]->GetPosition().y();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleZOrigin(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6;

    return (*fSecondary)[idx]->GetPosition().z();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreeVector QweakSimSteppingAction::GetSecondaryParticleOrigin(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return G4ThreeVector(1e6,1e6,1e6);

    return (*fSecondary)[idx]->GetPosition();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreeVector QweakSimSteppingAction::GetSecondaryParticleMomentum(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return G4ThreeVector(1e6,1e6,1e6);

    return (*fSecondary)[idx]->GetMomentumDirection();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String QweakSimSteppingAction::GetSecondaryCreatorProcessName(G4int idx)
{
    if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return "undefined";
    return (*fSecondary)[idx]->GetCreatorProcess()->GetProcessName();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//----------------------------------------------------------------------------------------------------------------------------------------------------------
// here we are only interested if the particle is crossing a boundary
// If you want to identify the first step in a volume: pick fGeomBoundary status in preStepPoint
// If you want to identify a step out of a volume    : pick fGeomBoundary status in postStepPoint

//   if( (theStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) && (strcmp( theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName(),"CerenkovDetector_Physical") == 0) ) //OK
//   //if( (theStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) && (strcmp( theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName(),"CerenkovDetector_Physical") == 0) ) // crash
//    {
//       G4cout << "------------------------" << G4endl;
//       //G4cout << "PreStepVolumeName  = " << theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
//       //G4cout << "PostStepVolumeName = " << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
//       G4cout << "------------------------" << G4endl;

// //       QweakSimTrackInformation* trackInfo;
// //       trackInfo = (QweakSimTrackInformation*)(theTrack->GetUserInformation());
// //       trackInfo->SetTrackingStatus(1);
// //       trackInfo->SetImpactTrackInformationForCerenkov(theTrack);

//   }

//----------------------------------------------------------------------------------------------------------------------------------------------------------

//   if(particleType==G4Electron::ElectronDefinition())
//   {
//       G4ThreeVector worldPos = thePrePoint->GetPosition();
//       G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

//       if( (myUserInfo->GetStoredStepVolumeName().compare("CerenkovDetector_Physical")==0) &&
// 	  (thePrePV->GetName().compare("CerenkovContainer_Physical")==0) )
//       {
// 	  myUserInfo->StoreLocalCerenkovExitPosition(localPos);
//       }
//   }
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//   if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
//     if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"PMTEntranceWindow_Physical")){
//
//
//       if(!strcmp(thePrePV->GetName(),"Cathode_Physical")){
//
//         QweakSimTrackInformation *TrackInfo = (QweakSimTrackInformation*)theTrack->GetUserInformation();
//         G4cout << "Particle History For This Photon" << G4endl;
//         G4cout << "Event ID = " << myUserInfo->GetPrimaryEventNumber() << G4endl;
//         G4cout << "Hit ID = " << myUserInfo->GetCurrentPMTHit()->GetHitID() << G4endl;
//         for(int i = 0; i < TrackInfo->GetParticleHistoryLength(); i++){
//           G4cout << "Particle "<< i <<" = " << TrackInfo->GetParticleDefinitionAtIndex(i)->GetParticleName();
//           if(i == TrackInfo->GetParticleHistoryLength()-1)
//             G4cout << " Eng = " << theTrack->GetTotalEnergy()/MeV;
//           else
//             G4cout << " Eng = " << TrackInfo->GetParentEnergyAtIndex(i+1)/MeV;
//
//           G4cout << " Cerenkov Hit Energy = " << TrackInfo->GetCerenkovHitEnergyAtIndex(i) << G4endl;
//         }
// //      G4int index = 0;
// //      if(TrackInfo->GetParticleHistoryLength() < 3)
// // //     myUserInfo->SetPhotonFromPrimary(TrackInfo->GetParticleDefinitionAtIndex(index));
// //      else{
// //        index = TrackInfo->GetParticleHistoryLength()-3;
// // //     myUserInfo->SetPhotonFromParticle(TrackInfo->GetParticleDefinitionAtIndex(index));
// //      }
//
//         myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
//         //      theTrack->SetTrackStatus(fStopAndKill);
//       }
//     }
//   }





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



