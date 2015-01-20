//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTrajectory.hh
   $Revision: 1.3 $	
   $Date: 2005/12/28 23:09:41 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimTrajectory
    
   \brief Stores the information about the various tracks. 

   It can be viewed as a perfect track reconstruction in a hypothetical perfect Qweak setup

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/28 23:09:41 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTrajectory_h
#define QweakSimTrajectory_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>

// geant4 includes
#include "G4Allocator.hh"
#include "G4VTrajectory.hh"

// geant4 classes
class G4Track;
class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef std::vector<G4VTrajectoryPoint*> QweakSimTrajectoryPointContainer;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTrajectory : public G4VTrajectory
{

//--------
   public:
//--------

// Constructor/Destructor

   QweakSimTrajectory();

   QweakSimTrajectory(const G4Track* aTrack);
   QweakSimTrajectory(QweakSimTrajectory &);
   virtual ~QweakSimTrajectory();

// Operators
   inline void* operator new(size_t);
   inline void  operator delete(void*);
   inline int operator == (const QweakSimTrajectory& right) const
   {return (this==&right);}

// Get/Set functions
   inline G4int GetTrackID() const
   { return fTrackID; }
   inline G4int GetParentID() const
   { return fParentID; }
   inline G4String GetParticleName() const
   { return ParticleName; }
   inline G4double GetCharge() const
   { return PDGCharge; }
   inline G4int GetPDGEncoding() const
   { return PDGEncoding; }
   inline G4ThreeVector GetInitialMomentum() const
   { return InitialMomentum; }

   virtual int GetPointEntries() const
       { return positionRecord->size(); }
   virtual G4VTrajectoryPoint* GetPoint(G4int i) const 
       { return (*positionRecord)[i]; }

// Other member functions
//   virtual void ShowTrajectory() const;
   virtual void ShowTrajectory(std::ostream& os=G4cout) const;
   virtual void DrawTrajectory(G4int i_mode=0) const;
   virtual void AppendStep(const G4Step* aStep);
   virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);

   // From LXe example
   void SetDrawTrajectory(G4bool b){drawit=b;}
   void SetForceDrawTrajectory(G4bool b){forceDraw=b;}
   void SetForceNoDrawTrajectory(G4bool b){forceNoDraw=b;}

   G4ParticleDefinition* GetParticleDefinition();

//---------
   private:
//---------

  QweakSimTrajectoryPointContainer* positionRecord;
  G4int fTrackID;
  G4int fParentID;
  G4ParticleDefinition* fpParticleDefinition;
  G4String ParticleName;
  G4double PDGCharge;
  G4int    PDGEncoding;
// FIXME not initialized !!!
  G4ThreeVector InitialMomentum;

  G4ThreeVector  momentum;
  G4ThreeVector  vertexPosition;
  G4double       globalTime;

// From LXe example
  G4bool drawit;
  G4bool forceNoDraw;
  G4bool forceDraw;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern G4Allocator<QweakSimTrajectory> myTrajectoryAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimTrajectory::operator new(size_t)
{
  void* aTrajectory;
  aTrajectory = (void*)myTrajectoryAllocator.MallocSingle();
  return aTrajectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimTrajectory::operator delete(void* aTrajectory)
{
  myTrajectoryAllocator.FreeSingle((QweakSimTrajectory*)aTrajectory);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTrajectory.hh,v $
//      Revision 1.3  2005/12/28 23:09:41  grimm
//      Testing: added some bool variables taken from the LXe example for dis/enabling user trajectory storage
//
//      Revision 1.2  2005/12/27 19:27:38  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
