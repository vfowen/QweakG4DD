//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTrackingAction.cc

   $Revision: 1.5 $	
   $Date: 2006/01/18 20:27:32 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTrackingAction.hh"

// geant4 includes
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"

// user includes
#include "QweakSimUserInformation.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrackingActionMessenger.hh"
#include "QweakSimTrajectory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTrackingAction::QweakSimTrackingAction(QweakSimUserInformation* myUI)
  : myUserInfo(myUI)
{
  G4cout << G4endl << "###### Calling QweakSimTrackingAction::QweakSimTrackingAction() " << G4endl << G4endl;

  pTrackingActionMessenger = new QweakSimTrackingActionMessenger(this);

  G4cout << G4endl << "###### Leaving QweakSimTrackingAction::QweakSimTrackingAction() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrackingAction::~QweakSimTrackingAction()
{
  G4cout << G4endl << "###### Calling QweakSimTrackingAction::~QweakSimTrackingAction() " << G4endl << G4endl;

  delete pTrackingActionMessenger;

  G4cout << G4endl << "###### Leaving QweakSimTrackingAction::~QweakSimTrackingAction() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 void QweakSimTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{

  //G4cout << G4endl << "###### Calling QweakSimTrackingAction::PreUserTrackingAction() " << G4endl << G4endl;

    // store only trajectory of primary
    // BUT allow tracking of secondaries with an origin of  z>568*cm

//     if( (aTrack->GetParentID()==0) || (aTrack->GetVertexPosition().z() > 568.0*cm) )
//     {
//         fpTrackingManager->SetStoreTrajectory(true);
//         //fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
//     }
//     else
//     {
//         fpTrackingManager->SetStoreTrajectory(false);
//     }

    //-----------------------------------------------------------
    //

  /*
    if (TrackingFlag==1) 
    {
	// store only trajectory of primary particles (== electrons from event generator) for tracking
	//if( (aTrack->GetParentID()==0) || (aTrack->GetVertexPosition().z() > 568.0*cm) )
	
	if( (aTrack->GetParentID()==0) || (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) )
	{
	    fpTrackingManager->SetStoreTrajectory(true);
	    
	    // store track
	    //fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
	    fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	}
	else
	{
	    // G4cout << "===> Not a primary event, Trajectory not stored !!!" << G4endl;
	    fpTrackingManager->SetStoreTrajectory(false);
	}
    }
    else 
    {
	// store all trajectories (primary+secondaries)
	fpTrackingManager->SetStoreTrajectory(true);
	fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	
    }*/



    if (TrackingFlag==0)  //track primary electron only
    {
	// store only trajectory of primary particles (== electrons from event generator) for tracking
	//if( (aTrack->GetParentID()==0) || (aTrack->GetVertexPosition().z() > 568.0*cm) )
	
	if( aTrack->GetParentID()==0 )
	{
	    fpTrackingManager->SetStoreTrajectory(true);
	    
	    // store track
	    fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	}
	else
	{
	    //fpTrackingManager->SetStoreTrajectory(false);
            //aTrack->SetTrackStatus(fStopAndKill); 
            fpTrackingManager->EventAborted();
            return;
	}
    }
    else if (TrackingFlag==1)  //track primary electron and optical photon
    {
	if( (aTrack->GetParentID()==0) || (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) )
	{
	    fpTrackingManager->SetStoreTrajectory(true);
	    
	    // store track
	    fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	}
	else
	{
	    //fpTrackingManager->SetStoreTrajectory(false);
            //aTrack->SetTrackStatus(fStopAndKill); 
            fpTrackingManager->EventAborted();
            return;
	}
	
    }

    else if (TrackingFlag==2)  //track primary electron and secondaries except optical photon
    {
	if( aTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition() )
	{
	    fpTrackingManager->SetStoreTrajectory(true);
	    
	    // store track
	    fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	}
	else
	{
	    //fpTrackingManager->SetStoreTrajectory(false);
            //aTrack->SetTrackStatus(fStopAndKill); 
            fpTrackingManager->EventAborted();
            return;
	}
	
    }

    else  // if (TrackingFlag==3)  //track all particles
    {
	// store all trajectories (primary+secondaries)
	fpTrackingManager->SetStoreTrajectory(true);
	fpTrackingManager->SetTrajectory(new QweakSimTrajectory(aTrack));
	
    }
    //
    //-----------------------------------------------------------

  
    // Check if the track already has track info
    // in case of a  primary event w/o user track info: 
    // create/store user track info
   if( (aTrack->GetParentID()==0) && (aTrack->GetUserInformation()==0) )
    {
	//  G4cout << G4endl << "###### Creating new Track User Information for primary" << G4endl << G4endl;
		
	// create user track info using current primary track pointer as an input
	QweakSimTrackInformation* anInfo = new QweakSimTrackInformation(aTrack);
	  
	// fill user track info with data stored in myUserInfo (class QweakUserInformation)
// 	anInfo->StorePrimaryQ2(myUserInfo->GetPrimaryQ2());
// 	anInfo->StoreCrossSection(myUserInfo->GetCrossSection());
// 	anInfo->StoreCrossSectionWeight(myUserInfo->GetCrossSectionWeight());
// 	anInfo->StorePrimaryEventNumber(myUserInfo->GetPrimaryEventNumber());

/*
        anInfo->StorePrimaryTrackID(myUserInfo->GetTrackID());

        int particleType = myUserInfo->GetPDGcode();
        if (particleType==3)
          anInfo->StorePrimaryParticle(G4Electron::ElectronDefinition());

        G4double theX = myUserInfo->GetOriginVertexPositionX();
        G4double theY = myUserInfo->GetOriginVertexPositionY();
        G4double theZ = myUserInfo->GetOriginVertexPositionZ();
        anInfo->StorePrimaryPosition(G4ThreeVector(theX, theY, theZ));

        G4double mdX = myUserInfo->GetOriginVertexMomentumDirectionX();
        G4double mdY = myUserInfo->GetOriginVertexMomentumDirectionY();
        G4double mdZ = myUserInfo->GetOriginVertexMomentumDirectionZ();
        G4double mdNormal = sqrt(mdX*mdX+mdY*mdY+mdZ*mdZ);
        G4double Ek = myUserInfo->GetOriginVertexKineticEnergy();
        G4double px = Ek*mdX/mdNormal;
        G4double py = Ek*mdY/mdNormal;
        G4double pz = Ek*mdZ/mdNormal;
        anInfo->StorePrimaryMomentum(G4ThreeVector(px,py,pz));
        anInfo->StorePrimaryEnergy(Ek);
        anInfo->StorePrimaryKineticEnergy(Ek);
        anInfo->StorePrimaryTime(myUserInfo->GetGlobalTime());
*/

	// set the source track info (which is here identical to the primary track info)
	anInfo->SetSourceTrackInformation(aTrack);
	//anInfo->Print();
	
	// access the track pointer
	G4Track* theTrack = (G4Track*) aTrack;
	
	// attach/expand track with user track info
	theTrack->SetUserInformation(anInfo);
	
	//delete anInfo;
      }



 // G4cout << G4endl << "###### Leaving QweakSimTrackingAction::PreUserTrackingAction() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrackingAction::PostUserTrackingAction(const G4Track* /*aTrack*/)
{
  //G4cout << G4endl << "###### Calling QweakSimTrackingAction::PostUserTrackingAction() " << G4endl << G4endl;

  //-------------------------------------------------------------------------
  // attach user track info of the primary particle to the seconary particles
  //-------------------------------------------------------------------------
  
  // get pointer to secondaries
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  

  if(secondaries)
  {
 
    // how many secondaries do we have ?
    G4int nSeco = secondaries->size();

    //G4cout << "###### --> How many secondaries: " << nSeco << G4endl;

    if(nSeco>0)
    {
	//G4cout << "###### --> Within secondary loop " << G4endl;

	// get pointer to primary track info
// 	QweakSimTrackInformation* info = (QweakSimTrackInformation*)(aTrack->GetUserInformation());

// 	// NEW: add the track information of the source track to the secondaries
// 	//      (don't mix up source track info with unique primary track info)
// 	//      nedded for figuring out if a primary electron or secondary particles
// 	//      has created a cerenkov photon           



// 	//G4cout << "###### --> We got info = (QweakSimTrackInformation*)(aTrack->GetUserInformation() " << G4endl;
	

// 	for(G4int i=0;i<nSeco;i++)
// 	{
// 	    // create secondary track info pointer for each secondary
// 	    QweakSimTrackInformation* infoNew = new QweakSimTrackInformation(info);


// 	    // copy primary track info to the current secondary
// 	    (*secondaries)[i]->SetUserInformation(infoNew);

// 	    // check for cerenkov photon generation
// 	    if ( (*secondaries)[i]->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition() && 
//          	 (*secondaries)[i]->GetCreatorProcess()->GetProcessName()=="Cerenkov" )
// 	    {
// 		G4cout << " Cerenkov Photon generated here" << G4endl;

// 		info->SetSourceTrackInformation(aTrack);

// 	    }

// 	    // tried it: G4 crashes if I delete infoNew
// 	    //delete infoNew;
	    
// 	}  // end for
    }    // end if (nSeco>0)
  }      // end if (secondaries)
  
  //G4cout << G4endl << "###### Leaving QweakSimTrackingAction::PostUserTrackingAction() " << G4endl << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
