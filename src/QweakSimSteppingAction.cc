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

#include "QweakSimMScAnalyzingPower.hh"
/*
  Brem depolarization: PhysRev.114.887
  implemented only for transverse polarization
  will decrease the overall polarization by a functional form from figure 5 in the paper      
*/
static const int perpNval=128;
static const double perpXDepol[perpNval]={0.053,0.066,0.075,0.084,0.097,0.112,0.126,0.137,0.148,0.160,0.169,0.180,0.190,0.200,0.210,0.220,0.226,0.236,0.244,0.251,0.258,0.267,0.274,0.283,0.291,0.300,0.308,0.316,0.324,0.332,0.340,0.350,0.357,0.364,0.371,0.379,0.387,0.395,0.403,0.411,0.417,0.425,0.434,0.443,0.453,0.460,0.468,0.477,0.488,0.499,0.509,0.518,0.525,0.532,0.541,0.548,0.555,0.563,0.570,0.576,0.581,0.587,0.594,0.600,0.608,0.616,0.623,0.628,0.635,0.640,0.646,0.653,0.661,0.668,0.676,0.683,0.688,0.694,0.699,0.706,0.709,0.715,0.722,0.728,0.734,0.738,0.745,0.749,0.752,0.757,0.762,0.769,0.776,0.782,0.789,0.795,0.799,0.806,0.810,0.815,0.824,0.830,0.836,0.843,0.847,0.853,0.858,0.864,0.868,0.874,0.881,0.887,0.893,0.900,0.908,0.915,0.920,0.930,0.935,0.945,0.953,0.963,0.969,0.974,0.979,0.985,0.990,0.994};
static const double perpYDepol[perpNval]={0.203,0.277,0.399,0.522,0.764,0.890,1.250,1.608,1.966,2.208,2.565,2.924,3.281,3.639,4.114,4.472,4.945,5.421,5.895,6.251,6.485,6.960,7.556,8.030,8.504,9.097,9.671,10.145,10.620,11.094,11.804,12.396,12.988,13.579,14.161,14.871,15.580,16.407,17.234,17.709,18.417,19.127,20.072,21.021,21.968,22.794,23.744,24.689,25.871,27.288,28.116,29.179,30.006,30.838,31.901,32.968,34.030,34.975,35.920,36.746,37.455,38.164,38.874,39.935,40.998,41.944,43.007,43.933,44.878,45.822,46.884,47.770,48.951,50.132,51.195,52.376,53.437,54.265,55.096,56.041,56.867,57.694,58.757,59.584,60.529,61.573,62.519,63.227,63.935,64.644,65.472,66.653,67.599,68.662,69.725,70.788,71.615,72.449,73.275,74.107,75.290,76.359,77.304,78.251,78.959,79.906,80.733,81.679,82.506,83.334,84.281,85.109,86.055,87.120,88.068,89.015,89.961,91.028,91.862,92.929,94.000,95.421,96.132,96.725,97.436,98.387,98.862,99.219};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimSteppingAction::QweakSimSteppingAction(QweakSimUserInformation* myUInfo, QweakSimEPEvent* myEPEvent,std::vector<double> *asInfo): asymInfo(asInfo)
{

  G4cout << "###### Calling QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;
  
  myEventCounter = 0;
  fSecondary = NULL;
  myUserInfo = myUInfo;

  myEvent = myEPEvent;
  
  evtGenStatus = 0;
  targetCenterPositionZ = myUserInfo->TargetCenterPositionZ;
  
  for(int i=0;i<perpNval;i++) perpDepol.SetPoint(i,perpXDepol[i],perpYDepol[i]);    
  
  fout=new TFile("o_tuple.root","RECREATE");	
  tout=new TNtuple("t","Ntuple primary info in Pb",
		   "be:bx:by:bz:bpx:bpy:bpz:bdpx:bdpy:bdpz:ae:ax:ay:az:apx:apy:apz:adpx:adpy:adpz:StepScatAngle:process:stepL:evN:trackID:parentID:pType:polX:polY:polZ:eLoss:bremDepol:aAngX:aAngY");
  
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
  if( (int(asymInfo->at(3)) & 0x1) == 0x1 )
    debugPrint=true;
  
  // toggle to write out e\pm/gammas on top of primary electrons !! really big files
  G4bool writeOutAll=false;
  // toggle for filling the Pb ntuple
  G4bool fillNtuple=false; 
  
  int _trackID=theStep->GetTrack()->GetTrackID(); 
  int _parentID = theStep->GetTrack()->GetParentID();
  double _priE=theStep->GetTrack()->GetTotalEnergy();
  G4String _name=theStep->GetTrack()->GetDefinition()->GetParticleName();
  G4String _pn=thePostPoint->GetProcessDefinedStep()->GetProcessName();
  G4Material *_material=thePostPoint->GetMaterial();
  G4double depol(0),eLossPercent(0);

  G4ThreeVector _polarization = theStep->GetTrack()->GetPolarization();
  G4ThreeVector initialMom = thePrePoint->GetMomentum().unit();
  G4ThreeVector finalMom  = thePostPoint->GetMomentum().unit();
  G4ThreeVector newBeamPol(0,1,0);
  PolarizationTransfer(initialMom,finalMom,_polarization,newBeamPol,debugPrint);

  if(debugPrint){
    G4cout<<__PRETTY_FUNCTION__<<G4endl;
    G4cout<<"\tinitial Mom (RTP) "<<initialMom.getR()<<"\t"<<initialMom.getTheta()<<"\t"<<initialMom.getPhi()<<G4endl;
    G4cout<<"\tfinal   Mom (RTP) "<<finalMom.getR()<<"\t"<<finalMom.getTheta()<<"\t"<<finalMom.getPhi()<<G4endl;
    G4cout<<"\ti polarization(XYZ) "<<_polarization.getX()<<"\t"<<_polarization.getY()<<"\t"<<_polarization.getZ()<<G4endl;
    G4cout<<"\tf polarization(XYZ) "<<newBeamPol.getX()<<"\t"<<newBeamPol.getY()<<"\t"<<newBeamPol.getZ()<<G4endl;   
  }
  _polarization = newBeamPol;
  theStep->GetTrack()->SetPolarization(_polarization); // set to transported polarization
  
  //this gets used in the physics process to stop the asymmetry calculation
  if( theStep->GetTrack()->GetVolume()->GetName().compare("QuartzBar_PhysicalRight") == 0 ||
      theStep->GetTrack()->GetVolume()->GetName().compare("QuartzBar_PhysicalLeft") == 0 )
    asymInfo->at(2)=0;

  
  if(_material){    
    if(debugPrint){
      G4cout<<__PRETTY_FUNCTION__<<G4endl;
      G4cout<<"\tStep in "<<_material->GetName()<<" "
	    <<theStep->GetTrack()->GetVolume()->GetName()<<G4endl
	    <<"\tpreKEnergy\tpostKEnergy\tstepEnergy"<<G4endl
	    <<"\t"<<thePrePoint->GetKineticEnergy()<<"\t"
	    <<thePostPoint->GetKineticEnergy()<<"\t"<<_priE<<G4endl
	    <<"\tpos: cart: "
	    <<thePostPoint->GetPosition().getX()
	    <<" "<<thePostPoint->GetPosition().getY()
	    <<" "<<thePostPoint->GetPosition().getZ()
	    <<G4endl<<"\tsph: "<<thePostPoint->GetPosition().getR()
	    <<" "<<thePostPoint->GetPosition().getTheta()
	    <<" "<<thePostPoint->GetPosition().getPhi()
	    <<G4endl<<"\taI(0)\taI(1)\taI(2): "
	    <<asymInfo->at(0)<<"\t"
	    <<asymInfo->at(1)<<"\t"
	    <<asymInfo->at(2)<<G4endl;
    }
    
    if(_material->GetName().compare("PBA")==0){ // perform this only in the Radiator
      if(debugPrint)
	G4cout<<"depol:\t"<<_pn.compare("eBrem")<<"\t"<<int(fabs(_polarization.getX())>0)<<"\t"<<int(fabs(_polarization.getY())>0)<<G4endl;

      eLossPercent = 1. - thePostPoint->GetKineticEnergy()/thePrePoint->GetKineticEnergy();
      
      if(_pn.compare("eBrem")==0 &&                           // only for eBrem
	 ( abs(_polarization.unit() * thePostPoint->GetMomentum().unit()) < 1 )){ // only for transverse polarization

	depol=0;
	if( eLossPercent > perpXDepol[perpNval-1]) depol = 1.;
	else if( eLossPercent >= perpXDepol[0] ) depol = perpDepol.Eval(eLossPercent,0,"S")/100.;
	else depol = 0.;
 
	if(debugPrint){
	  G4cout<<__PRETTY_FUNCTION__<<G4endl;
	  G4cout<<"\teBrem depol : "
		<<eLossPercent*100<<"% E loss means\t"
		<< depol <<" depolarization"<<G4endl;
	  G4cout<<"\tpreKinE postKinE: "
		<<thePrePoint->GetKineticEnergy()
		<<" "<<thePostPoint->GetKineticEnergy()<<G4endl;
	  G4cout<<"\tpolarization X Y Z: "
		<<_polarization.getX()<<" "
		<<_polarization.getY()<<" "
		<<_polarization.getZ()<<" => ";
	}
	_polarization *= (1.-depol);
	theStep->GetTrack()->SetPolarization(_polarization);
	if(debugPrint){
	  G4cout<<_polarization.getX()<<" "
		<<_polarization.getY()<<" "
		<<_polarization.getZ()<<G4endl;
	}

      }
      
      if(debugPrint){
	G4cout<<__PRETTY_FUNCTION__<<G4endl;
	G4cout<<"\tPrimaryEventNumber\tasymInfo(0)\tasymInfo(1)"<<G4endl<<"\t"
	      <<myUserInfo->GetPrimaryEventNumber()<<"\t"
	      <<asymInfo->at(0)<<"\t"
	      <<asymInfo->at(1)<<"\t"
	      <<G4endl;
      }

      // either write out only the primaries or all e\pm and gammas
      if(((particleType==G4Positron::PositronDefinition() ||
	   particleType==G4Electron::ElectronDefinition() ||
	   particleType==G4Gamma::GammaDefinition()) && writeOutAll) ||
	 (particleType==G4Electron::ElectronDefinition() && _parentID==0) ) {
	
	// "be:bx:by:bz:bpx:bpy:bpz:bdpx:bdpy:bdpz:
	//  ae:ax:ay:az:apx:apy:apz:adpx:adpy:adpz:
	//  StepScatAngle:process:stepL:evN:trackID:parentID:pType:
	//  polX:polY:polZ:eLoss:bremDepol:aAngX:aAngY"
	float _var[34];
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
	_var[26]=particleType->GetPDGEncoding();	
	_var[27]=_polarization.getX();
	_var[28]=_polarization.getY();
	_var[29]=_polarization.getZ();

	_var[30]=eLossPercent;
	_var[31]=depol;

	G4double aAngX(-999),aAngY(-999);
	if(thePostPoint->GetMomentum().getR()>0){
	  aAngX = atan2( sin(_postP.getTheta()) * cos(_postP.getPhi()) , cos(_postP.getTheta()) ) * 180.0 / pi;
	  aAngY = atan2( sin(_postP.getTheta()) * sin(_postP.getPhi()) , cos(_postP.getTheta()) ) * 180.0 / pi;
	}
	
	_var[32]=aAngX;
	_var[33]=aAngY;


	if(fillNtuple)
	  tout->Fill(_var);
	
	if(debugPrint){
	  G4cout<<__PRETTY_FUNCTION__<<G4endl;
	  G4cout<<"\tPrimary:\ttrackID\tparentID\ttotE\tprocessName\tpartName"<<G4endl
		<<"\t\t\t"<<_trackID<<"\t"<<_parentID<<"\t"<<_priE<<"\t"<<_pn<<"\t"<<_name<<G4endl
		<<"\tmaterialName\tScatteringAngle\tstepLength"<<G4endl<<"\t"
		<<_material->GetName()<<"\t"<<scatAng<<"\t"<<_steplength<<G4endl;
	  G4cout<<"\tpreP R th phi "
		<<_preP.getR()<<" "<<_preP.getTheta()<<" "<<_preP.getPhi()<<G4endl;
	  G4cout<<"\tpostP R th phi "
		<<_postP.getR()<<" "<<_postP.getTheta()<<" "<<_postP.getPhi()<<G4endl;
	  G4cout<<"\tpre.angle(post): "<<_preP.angle(_postP)<<G4endl;
	}

      }//if(writeOut)      
    }//if(PBA)
  }//if(material)
  
  if(particleType==G4Electron::ElectronDefinition())
    {
      G4ThreeVector worldPos = thePrePoint->GetPosition();
      G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
      
      if((!strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalRight") ||
	  !strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalLeft")) &&
	 (!strcmp(thePrePV->GetName(),"ActiveArea_Physical") ||
	  !strcmp(thePrePV->GetName(),"CerenkovMasterContainer_Physical")))
        {
	  myUserInfo->StoreLocalCerenkovExitPosition(localPos);
        }
    }
    
  //pqwang: optical photon process
  
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4OpBoundaryProcess* boundary=NULL;
  
  if(!boundary) {
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

  if(debugPrint){
    G4cout<<__PRETTY_FUNCTION__<<G4endl;
    G4cout<<"\tFinished step"<<G4endl<<G4endl<<G4endl;
    if(_material)
      if(_material->GetName().compare("PBA")==0)
	std::cin.ignore();
  }
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



