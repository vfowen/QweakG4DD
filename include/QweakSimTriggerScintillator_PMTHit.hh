//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTriggerScintillator_PMTHit.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:07 $
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
   \class QweakSimTriggerScintillator_PMTHit
    
   \brief Handling of a Photomultiplier Hit of the Trigger Scintillator detector

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
//  Update Date:      $Date: 2005/12/27 19:28:07 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
#ifndef QweakSimTriggerScintillator_PMTHit_h
#define QweakSimTriggerScintillator_PMTHit_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimTriggerScintillator_PMTHit : public G4VHit
{
public:
  
  QweakSimTriggerScintillator_PMTHit();
  QweakSimTriggerScintillator_PMTHit(G4int detector_id);
  virtual ~QweakSimTriggerScintillator_PMTHit();
  
  QweakSimTriggerScintillator_PMTHit(const QweakSimTriggerScintillator_PMTHit &right);
  const QweakSimTriggerScintillator_PMTHit & operator=(const QweakSimTriggerScintillator_PMTHit &right);
  int operator==(const QweakSimTriggerScintillator_PMTHit &right) const;
  
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
  
  inline float x();
  inline float y();

  //virtual void Draw();
  //virtual void Print();
  
private:
  G4int    PMTID;
  G4double      currentPhotonEnergy;
  
  public:

  inline void StorePMTID(G4int pmt_id) { PMTID = pmt_id; }
  inline G4int GetPMTID() const { return PMTID; }

  inline void   StorePhotonEnergy(G4double eng) { currentPhotonEnergy  = eng; }
  inline G4double GetPhotonEnergy() const { return currentPhotonEnergy; }

 };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<QweakSimTriggerScintillator_PMTHit> QweakSimTriggerScintillator_PMTHitsCollection;

extern G4Allocator<QweakSimTriggerScintillator_PMTHit>  QweakSimTriggerScintillator_PMTHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* QweakSimTriggerScintillator_PMTHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) QweakSimTriggerScintillator_PMTHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void QweakSimTriggerScintillator_PMTHit::operator delete(void* aHit)
{
   QweakSimTriggerScintillator_PMTHitAllocator.FreeSingle((QweakSimTriggerScintillator_PMTHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_PMTHit.hh,v $
//      Revision 1.2  2005/12/27 19:28:07  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
