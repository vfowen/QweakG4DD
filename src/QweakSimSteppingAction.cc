//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimSteppingAction.cc

   $Revision: 1.4 $
   $Date: 2006/05/05 21:46:05 $

   \author Klaus Hans Grimm

*/

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
    //RandomPositionZ = myEvent->GetVertexZ();
    _primaryID.push_back(0);
    //std::ofstream EventDataFile("Event.dat", std::ios::out);

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
    //   G4int                 ReplicaNo    = 0;
    G4String              particleName = theTrack->GetDefinition()->GetParticleName();
    G4ProcessManager*     pm           = particleType->GetProcessManager();

//get material
    G4Material* theMaterial = theTrack->GetMaterial();

    //   G4int                 nprocesses   = pm->GetProcessListLength();
    //   G4ProcessVector*      pv           = pm->GetProcessList();
    //   G4VSteppingVerbose*   theVerbStep  = G4VSteppingVerbose::GetInstance();
    //   G4double              charge       = particleType->GetPDGCharge();

    //   G4int nSecAtRest       = GetNumOfAtRestSecondaries();
    //   G4int nSecAlong        = GetNumOfAlongStepSecondaries();
    //   G4int nSecPost         = GetNumOfPostStepSecondaries();
    //   G4int nSecTotal        = GetTotalNumOfSecondaries();

    //RandomPositionZ = myEvent->GetVertexZ();
    RandomPositionZ = myUserInfo->GetOriginVertexPositionZ();

    //jpan@nuclear.uwinnipeg.ca Thu Apr 16 01:33:14 CDT 2009
    // check if it is primary

    //to get the kryptonie to work
    if(theMaterial->GetName()=="Kryptonite")
    {
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
        // G4cout << "Track pos:: " << theX/mm << "\t" << theY/mm << "\t" << theZ/mm << G4endl;
        // G4cout << "RandomPositionZ :: " << RandomPositionZ << G4endl;

        G4String procName = thePostPoint->GetProcessDefinedStep()->GetProcessName();
        // dEE in MeV -> all Elosses are in MeV
        G4double dEE = thePrePoint->GetKineticEnergy()/MeV-thePostPoint->GetKineticEnergy()/MeV;

        if(myUserInfo->GetPrimaryEventNumber() %2!=3) {

            //    if( theZ > targetCenterPositionZ+35*cm*0.5+5*(2.54*cm*0.001) || sqrt(theX*theX+theY*theY)>2.54*cm)
            //     {
            //        evtGenStatus = 0;
            //     }

            if( myUserInfo->EvtGenStatus == 0) { // true for primary event # = 0,2,4,...
                // see QweakSimPrimaryGeneratorAction.cc

                // // various energy losses at the target
                // // IMP:: all the Elosses upto the vertex, theZ, is stored here
                if ( thePrePV && thePostPV) {  // Added check to prevent a seg fault
                    if(((thePrePV->GetName()).contains("QweakTarget") ||
                            (thePostPV->GetName()).contains("QweakTarget"))) {
                        if (procName.compare("msc")==0)
                            myUserInfo->AddTodEMscIn(dEE);
                        else if(procName.compare("eIoni")==0)
                            myUserInfo->AddTodEIonIn(dEE);
                        else if(procName.compare("eBrem")==0)
                            myUserInfo->AddTodEBremIn(dEE);
                    }
                }

                G4double theStepLength = theStep->GetStepLength();

                // if the z-position of the particle, theZ, is within
                // the stepLength of RandomPositionZ,
                // then kill the particle, and reset the origin vertex Z as theZ
                if( 1==2 && fabs(theZ - RandomPositionZ)<=theStepLength && sqrt(theX*theX+theY*theY)<2.54*cm) {

                    std::vector< G4double > CrossSection;
                    for (Int_t i = 0; i<16; i++) {
                        CrossSection.push_back(0.0);
                    }

                    G4double WeightN, Q2, E_out, theta, phi;
                    G4double Asymmetry;
                    G4ThreeVector MomentumDirection = theTrack->GetMomentumDirection();
                    G4double E_in = theTrack->GetTotalEnergy()/MeV;  //Event generator needs units of MeV

                    // evaluate the MomentumDirection, E_out ..
                    myEvent->GetanEvent(E_in, CrossSection, WeightN, Q2, E_out, MomentumDirection, theta, phi, Asymmetry);

                    //theTrack->SetKineticEnergy(E_out*MeV);
                    //theTrack->SetMomentumDirection(MomentumDirection);

                    myUserInfo->EvtGenStatus = 1;

                    // set track info
                    //theTrack->SetVertexPosition(thePosition);
                    //theTrack->SetVertexMomentumDirection(MomentumDirection);
                    //theTrack->SetVertexKineticEnergy(E_out);

                    //fill user info
                    myUserInfo->StoreTrackID(theTrack->GetTrackID());
                    myUserInfo->StoreGlobalTime(theTrack->GetGlobalTime());
                    myUserInfo->StoreOriginVertexPositionX(theX);
                    myUserInfo->StoreOriginVertexPositionY(theY);
                    //	  myUserInfo->StoreOriginVertexPositionZ(theZ);
                    myUserInfo->StoreOriginVertexPositionZ(RandomPositionZ);
                    myUserInfo->StoreOriginVertexMomentumDirectionX(MomentumDirection.getX());
                    myUserInfo->StoreOriginVertexMomentumDirectionY(MomentumDirection.getY());
                    myUserInfo->StoreOriginVertexMomentumDirectionZ(MomentumDirection.getZ());
                    myUserInfo->StoreOriginVertexThetaAngle(theta);
                    myUserInfo->StoreOriginVertexPhiAngle(phi);
                    //myUserInfo->StoreOriginVertexKineticEnergy(theTrack->GetKineticEnergy());
                    //myUserInfo->StoreOriginVertexTotalEnergy(theTrack->GetTotalEnergy());

                    myUserInfo->StorePreScatteringKineticEnergy(E_in - 0.511*MeV);
                    if(particleType==G4Electron::ElectronDefinition()) {
                        myUserInfo->StoreOriginVertexKineticEnergy(E_out - 0.511*MeV);
                        //	    G4cout << "Stepping Action E_out:: " << (E_out - 0.511*MeV)/MeV << G4endl;
                    }
                    if(particleType==G4PionMinus::PionMinusDefinition())
                    {
                        myUserInfo->StoreOriginVertexKineticEnergy(E_out - 139.57*MeV);
                    }
                    myUserInfo->StoreOriginVertexTotalEnergy(E_out);

                    myUserInfo->StorePrimaryQ2(Q2*0.000001); //in units of GeV^2
                    myUserInfo->StoreCrossSection(CrossSection[0]);
                    myUserInfo->StoreCrossSectionWeight(WeightN);
                    myUserInfo->StoreCrossSectionBornTotal    (CrossSection[1]);
                    myUserInfo->StoreCrossSectionBornInelastic(CrossSection[2]);
                    myUserInfo->StoreCrossSectionBornQE       (CrossSection[3]);
                    myUserInfo->StoreCrossSectionRadTotal     (CrossSection[4]);
                    myUserInfo->StoreCrossSectionRadElastic   (CrossSection[5]);
                    myUserInfo->StoreCrossSectionRadQE        (CrossSection[6]);
                    myUserInfo->StoreCrossSectionRadDIS       (CrossSection[7]);
                    myUserInfo->StoreCrossSectionRadTotalIntOnly   (CrossSection[8]);
                    myUserInfo->StoreCrossSectionRadElasticIntOnly (CrossSection[9]);
                    myUserInfo->StoreCrossSectionRadQEIntOnly      (CrossSection[10]);
                    myUserInfo->StoreCrossSectionRadDISIntOnly     (CrossSection[11]);
                    myUserInfo->StoreCrossSectionRadElasticPeak    (CrossSection[12]);
                    myUserInfo->StoreAsymmetry ( Asymmetry );
                    //myUserInfo->StorePrimaryEventNumber(myEventCounter);
                    myUserInfo->StoreReactionType(myEvent->GetReactionType());
                    myUserInfo->StorePDGcode(theTrack->GetDefinition()->GetPDGEncoding());

                    // print the stored values
                    // G4cout << "*********** myEventCounter = " << myEventCounter << G4endl;
                    // G4cout << "Pre scat KE:: "<<E_in<< G4endl;
                    // G4cout << "Org ver scat KE:: "<<E_out<< G4endl;

                    //             myUserInfo->Print();
                    theTrack->SetTrackStatus(fStopAndKill);
                } // end of if( fabs(theZ - RandomPositionZ)<=theStepLength && sqrt(theX*theX+theY*theY)<2.54*cm)
            } // end of  if( myUserInfo->EvtGenStatus == 0){  // true for primary event # = 0,2,4,...
        } // end of    if(myUserInfo->GetPrimaryEventNumber() %2!=0)
        else {

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
        }
    }

//now this is handled in the TrackingAction with the control of the tracking flag
//  else  //secondary, umcomment to disregard all secondaries to speed up the primary particle simulation
//   {
//      theTrack->SetTrackStatus(fStopAndKill);
//      return;
//   }

//jpan@nuclear.uwinnipeg
//kill a track if it is in collimators or shielding wall
//   if(thePrePV->GetName()=="CollimatorHousing" || thePrePV->GetName()=="ShieldingWallHousing"){
//   theTrack->SetTrackStatus(fStopAndKill); return;
//   }

// Peiqing : storing secondary information makes the simulation very slow
//           I commented them out. Uncomment them only in case we really
//           want to spend time to study the details of secondaries.
//
//  QweakSimTrackInformation* info = (QweakSimTrackInformation*)(theTrack->GetUserInformation());
//
//   for(G4int i = GetTrackVectorSize()-nSecTotal; i < GetTrackVectorSize(); i++)
//   {
//     if((*fSecondary)[i]->GetUserInformation()==0)
//     {
//       QweakSimTrackInformation* infoNew = new QweakSimTrackInformation(info);
//
//       infoNew->StoreParticleDefinition(GetSecondaryParticleDefinition(i));
//       infoNew->StoreParentEnergy(theTrack->GetTotalEnergy());
//       infoNew->StorePrimaryKineticEnergy(GetSecondaryParticleKineticEnergy(i));
//       infoNew->StoreCerenkovHitEnergy(-1,-1.0*MeV);
//       infoNew->StoreCreatorProcess(GetSecondaryCreatorProcessName(i));
//       infoNew->StoreOriginVertex(GetSecondaryParticleOrigin(i));
//       (*fSecondary)[i]->SetUserInformation(infoNew);
//     }
//
//     if(particleType==G4Electron::ElectronDefinition() && theTrack->GetParentID() == 0 &&
// //        !strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")){
//        (!strcmp(thePrePV->GetName(),"QuartzBar_PhysicalRight") || !strcmp(thePrePV->GetName(),"QuartzBar_PhysicalLeft") ))
//     {
//       if(GetSecondaryParticleDefinition(i) == G4OpticalPhoton::OpticalPhotonDefinition() &&
// 	 GetSecondaryParticleTotalEnergy(i)/eV <= 4.9594)
//       {
// 	myUserInfo->IncrementCerenkovOpticalPhotonCount();
// 	myUserInfo->StoreCerenkovPhotonEnergy(GetSecondaryParticleTotalEnergy(i));
//       }
//     }
//  }


//jpan@nuclear.uwinnipeg.ca
// commented out the cout statements for speeding up

//  G4cout << "Particle Name = " << particleType->GetParticleName() << G4endl;

//   if(!strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")){
//!strcmp(thePrePV->GetName(),"LightGuide_PhysicalRight") || !strcmp(thePrePV->GetName(),"LightGuide_PhysicalLeft")

// Peiqing:  commented out the followings for speeding up
//
//   if(!strcmp(thePrePV->GetName(),"QuartzBar_PhysicalRight") || !strcmp(thePrePV->GetName(),"QuartzBar_PhysicalLeft"))
//   {
//
//     myUserInfo->AddCerenkovEnergyDeposit(theStep->GetTotalEnergyDeposit());
//
//     if(theTrack->GetParentID() > 0 && (particleType==G4Electron::ElectronDefinition() ||
// 				       particleType==G4Positron::PositronDefinition() ||
// 				       particleType==G4Gamma::GammaDefinition())){
//
// //       if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"CerenkovContainer_Physical") &&
// 	 // 	 !strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")
// // 	 ){
//
//       if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"ActiveArea_Physical")){
//
// 	myUserInfo->StoreCerenkovSecondaryParticleInfo(theTrack->GetVertexPosition(),
// 						       theTrack->GetMomentum(),
// 						       theTrack->GetTotalEnergy(),
// 						       charge);
//       }
//     }
//   }
// Events that happen in the Pb FIXME
    G4Material *_material=thePostPoint->GetMaterial();
    if(_material)
        if(_material->GetName()=="PBA") {
	    int _priID=theStep->GetTrack()->GetTrackID(); 
	    int _priParentID = theStep->GetTrack()->GetParentID();
	    double _priE=theStep->GetTrack()->GetTotalEnergy();
	    TString _pn=thePostPoint->GetProcessDefinedStep()->GetProcessName();
	    int _foundP=0;
	    int _found=0;
	    for(int i=0;i<(int)_primaryID.size() && (!_foundP || !_found);i++){
		if(_priParentID==_primaryID[i]) _foundP++;
		if(_priID==_primaryID[i]) _found++;
	    }
	   
	   //G4cout<<"~Primary: "<<_priID<<" "<<_priParentID<<" "<<_priE<<" "<<_pn.Data()<<G4endl;
	   
	   if(_foundP){
	      if(!_found && _priE>0) _primaryID.push_back(_priID);
		G4cout<<"~Primary: "<<_priID<<" "<<_priParentID<<" "<<_priE<<" "<<_pn.Data()<<G4endl;
	    }
	    
            int found=-1;
            for(int i=0; i<(int)_procName.size() && found==-1; i++)
                if(strcmp(_pn.Data(),_procName[i].Data())==0) found=i;
            if(found==-1) {
                _procName.push_back(_pn);
                _nProc.push_back(1);
            }
            else _nProc[found]++;
	    
	    if ( _pn == "compt" ){
	      
	      double _priE=theStep->GetTrack()->GetTotalEnergy();
	      	    
	      const std::vector<const G4Track*> *_a=theStep->GetSecondaryInCurrentStep();
	      for( int i = 0 ; i < (int)(*_a).size() ; i++ ){
		G4cout<<"Secondaries: "<<(*_a)[i]->GetTrackID() << " "
		<< (*_a)[i]->GetParentID() << " "<< (*_a)[i]->GetTotalEnergy()<<G4endl;
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



