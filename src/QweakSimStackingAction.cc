
#include "QweakSimStackingAction.hh"

// geant4 includes
#include "G4Track.hh"

// user includes
#include "QweakSimSteppingAction.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrajectory.hh"

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
G4ClassificationOfNewTrack
QweakSimStackingAction::ClassifyNewTrack(const G4Track* /*aTrack*/)
{
  G4ClassificationOfNewTrack classification = fUrgent;

  //QweakSimTrackInformation* trackInfo;

  //if( (aTrack->GetDefinition()!=G4OpticalPhoton::OpticalPhotonDefinition()) ) {trackInfo->SetSourceTrackInformation(aTrack);}
  //if(  aTrack->GetTrackID()>2) {trackInfo->SetSourceTrackInformation(aTrack);}


//  if( (aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()) && (trackInfo->GetSourceParticle()!= G4OpticalPhoton::OpticalPhotonDefinition()) )
//  {
//      G4cout << " StackingAction: What has created the current Cerenkov photon :" << G4endl;
//      trackInfo = (QweakSimTrackInformation*)(aTrack->GetUserInformation());
//      //trackInfo->PrintSourceTrackInfo();
//      G4cout << " ParticleName = " << aTrack->GetDefinition()->GetParticleName() << G4endl;
//      G4cout << " Position     = " << aTrack->GetPosition()                      << G4endl;
//  }
//
  //trackInfo->SetSourceTrackInformation(aTrack);

   return classification;

//    //Count what process generated the optical photons
//    if(aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())
//    {
//        G4cout << "StackingAction: we have an optical photon !"<< G4endl;
//
//        // particle is optical photon
//        if(aTrack->GetParentID()>0)
//        {
//            // particle is secondary
//            if(aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov")
//            {
//
//                G4int parentID = aTrack->GetParentID();
//                G4int trackID  = aTrack->GetTrackID();
//                G4cout << G4endl << "Photon's Track ID = " << trackID  << G4endl;
//                G4cout << G4endl << "It's    Parent ID = " << parentID << G4endl;
//            }
//        }
//    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

