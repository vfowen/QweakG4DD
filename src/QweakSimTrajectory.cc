
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTrajectory.cc

   $Revision: 1.4 $	
   $Date: 2005/12/28 23:09:53 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/28 23:09:53 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTrajectory.hh"

// geant4 includes
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Polyline.hh"
#include "G4ParticleTable.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4OpticalPhoton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Allocator<QweakSimTrajectory> myTrajectoryAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory::QweakSimTrajectory()
{
  G4cout << G4endl << "###### Calling QweakSimTrajectory::QweakSimTrajectory()" << G4endl << G4endl;

    drawit       = FALSE;
    forceNoDraw  = FALSE;
    forceDraw    = FALSE;


   fpParticleDefinition = 0;
   ParticleName         = "";
   PDGCharge            = 0;
   PDGEncoding          = 0;
   fTrackID             = 0;
   fParentID            = 0;
   positionRecord       = 0;

   momentum             = G4ThreeVector(0.,0.,0.);
   vertexPosition       = G4ThreeVector(0.,0.,0.);
   globalTime           = 0.;

   G4cout << G4endl << "###### Leaving QweakSimTrajectory::QweakSimTrajectory()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory::QweakSimTrajectory(const G4Track* aTrack)
{
 //   G4cout << G4endl << "###### Calling QweakSimTrajectory::QweakSimTrajectory(aTrack)" << G4endl << G4endl;

   fpParticleDefinition = aTrack->GetDefinition();
   ParticleName         = fpParticleDefinition->GetParticleName();
   PDGCharge            = fpParticleDefinition->GetPDGCharge();
   PDGEncoding          = fpParticleDefinition->GetPDGEncoding();
   fTrackID             = aTrack->GetTrackID();
   fParentID            = aTrack->GetParentID();

   positionRecord =  new QweakSimTrajectoryPointContainer();
   positionRecord -> push_back(new G4TrajectoryPoint(aTrack->GetPosition()));

   momentum       = aTrack->GetMomentum();
   vertexPosition = aTrack->GetPosition();
   globalTime     = aTrack->GetGlobalTime();


   // G4cout << G4endl << "###### Leaving QweakSimTrajectory::QweakSimTrajectory(aTrack)" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory::QweakSimTrajectory(QweakSimTrajectory & right)
    : G4VTrajectory()
{
  ParticleName          = right.ParticleName;
  fpParticleDefinition  = right.fpParticleDefinition;
  PDGCharge             = right.PDGCharge;
  PDGEncoding           = right.PDGEncoding;
  fTrackID              = right.fTrackID;
  fParentID             = right.fParentID;

  positionRecord = new QweakSimTrajectoryPointContainer();

  for(int i=0;i<(int)right.positionRecord->size();i++)
  {
    G4TrajectoryPoint* rightPoint = (G4TrajectoryPoint*)((*(right.positionRecord))[i]);

    positionRecord->push_back(new G4TrajectoryPoint(*rightPoint));
  }

  momentum       = right.momentum;
  vertexPosition = right.vertexPosition;
  globalTime     = right.globalTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTrajectory::~QweakSimTrajectory()
{
  size_t i;
  for(i=0;i<positionRecord->size();i++){
    delete  (*positionRecord)[i];
  }
  positionRecord->clear();

  delete positionRecord;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrajectory::ShowTrajectory(std::ostream& os) const
{

  os << G4endl << "TrackID =" << fTrackID 
     << " : ParentID=" << fParentID << G4endl;

  os << "Particle name : " << ParticleName << "  PDG code : " << PDGEncoding
     << "  Charge : " << PDGCharge << G4endl;

  os << "Original momentum : " <<
      G4BestUnit(momentum,"Energy") << G4endl;

  os << "Vertex : "        << G4BestUnit(vertexPosition,"Length")
     << "  Global time : " << G4BestUnit(globalTime,"Time") << G4endl;

  os << "  Current trajectory has " << positionRecord->size() 
     << " points." << G4endl;

   for( size_t i=0 ; i < positionRecord->size() ; i++){
       G4TrajectoryPoint* aTrajectoryPoint = (G4TrajectoryPoint*)((*positionRecord)[i]);

       G4cout << "Point[" << i << "]" << " Position= " << aTrajectoryPoint->GetPosition() << G4endl;
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrajectory::DrawTrajectory(G4int) const
{
 //  G4cout << G4endl << "###### Calling QweakSimTrajectory::DrawTrajectory()" << G4endl << G4endl;

    //if(!forceDraw && (!drawit || forceNoDraw))

//    if( (forceNoDraw == true))
//         return;

  // If i_mode>=0, draws a trajectory as a polyline (blue for
  // positive, red for negative, green for neutral) and, if i_mode!=0,
  // adds markers - yellow circles for step points and magenta squares
  // for auxiliary points, if any - whose screen size in pixels is
  // given by abs(i_mode)/1000.  E.g: i_mode = 5000 gives easily
  // visible markers.

   G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

   G4ThreeVector pos;
   G4Polyline    pPolyline;

   for (int i = 0; i < (int) positionRecord->size() ; i++) {

       G4TrajectoryPoint* aTrajectoryPoint = (G4TrajectoryPoint*)((*positionRecord)[i]);
       pos = aTrajectoryPoint->GetPosition();
       pPolyline.push_back( pos );
   }


   G4Colour colour(0.75,0.75,0.75);    // LightGray

   G4Colour red      ( 255/255.,   0/255.,   0/255.);
   G4Colour blue     (   0/255.,   0/255., 255/255.);   
   G4Colour green    (   0/255., 255/255.,   0/255.);
   G4Colour yellow   ( 255/255., 255/255.,   0/255.);

   G4Colour white    ( 255/255., 255/255., 255/255.);
   
   G4Colour orange   ( 255/255., 127/255.,   0/255.);
   G4Colour magenta  ( 237/255., 173/255., 255/255.);		
   G4Colour magenta1 ( 104/255.,  49/255.,  94/255.);



   // Default colors for particlea
        if ( PDGCharge < 0.) {colour = red;}
   else if ( PDGCharge > 0.) {colour = blue;}
   else                      
   {   
       //G4cout << "%%%%% We have something neutral here !!!" << G4endl;
       colour = green;
   }
   
        if (fpParticleDefinition == G4Gamma     ::GammaDefinition()     )  {
	    //G4cout << "%%%%% We have a green Gamma here !!!" << G4endl;
	    colour = green;} 
        if (fpParticleDefinition == G4Electron  ::ElectronDefinition()  )  
	    {
	    //G4cout << "%%%%% We have a red Electron here !!!" << G4endl;
	    colour = red;  
	    //colour = white;  
	    } 
        if (fpParticleDefinition == G4Positron  ::PositronDefinition()  )  
	    {
	    //G4cout << "%%%%% We have a blue Positron here !!!" << G4endl;
	    colour = blue; 
	    } 

//    else if (fpParticleDefinition == G4MuonMinus ::MuonMinusDefinition()
//           ||fpParticleDefinition == G4MuonPlus  ::MuonPlusDefinition()) ) colour = G4Colour(1.,0.,1.);      // Magenta
//
//    else if(fpParticleDefinition->GetParticleType()=="meson")
//    {
//       if(PDGCharge!=0.)
//          colour = yellow;
//       else
//          colour = G4Colour(0.5,0.,0.);  // HalfRed
//    }
//    else if(fpParticleDefinition->GetParticleType()=="baryon")
//    {
//       if(PDGCharge!=0.)
//          colour = orange; // Orange
//       else
//          colour = G4Colour(0.5,0.39,0.);// HalfOrange
//    }

      if( fpParticleDefinition == G4Neutron       ::NeutronDefinition())       
      { 
	  //G4cout << "%%%%% We have a white Neutron here !!!" << G4endl;
	  colour = white;   
      }
      if( fpParticleDefinition == G4Proton        ::ProtonDefinition())        
      {
	  //G4cout << "%%%%% We have an orange Proton here !!!" << G4endl;
	  colour = orange;  
      }
      if( fpParticleDefinition == G4OpticalPhoton ::OpticalPhotonDefinition()) 
      { 
	  //G4cout << "%%%%% We have a magenta OpticalPhoton here !!!" << G4endl;  
	  colour = magenta; 
      }

   G4VisAttributes attribs(colour);
   pPolyline.SetVisAttributes(attribs);

  // if(pVVisManager) 
   pVVisManager->Draw(pPolyline);


  // G4cout << G4endl << "###### Leaving QweakSimTrajectory::DrawTrajectory()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrajectory::AppendStep(const G4Step* aStep)
{
   positionRecord->push_back( new G4TrajectoryPoint(aStep->GetPostStepPoint()->GetPosition() ));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ParticleDefinition* QweakSimTrajectory::GetParticleDefinition()
{
   return (G4ParticleTable::GetParticleTable()->FindParticle(ParticleName));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTrajectory::MergeTrajectory(G4VTrajectory* secondTrajectory)
{
  if(!secondTrajectory) return;

  QweakSimTrajectory* seco = (QweakSimTrajectory*)secondTrajectory;
  G4int ent = seco->GetPointEntries();

  for(int i=1;i<ent;i++) // initial point of the second trajectory should not be merged
  {
    positionRecord->push_back((*(seco->positionRecord))[i]);
  }

  delete (*seco->positionRecord)[0];

  seco->positionRecord->clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTrajectory.cc,v $
//      Revision 1.4  2005/12/28 23:09:53  grimm
//      Testing: added some bool variables taken from the LXe example for dis/enabling user trajectory storage
//
//      Revision 1.3  2005/12/27 19:15:43  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
