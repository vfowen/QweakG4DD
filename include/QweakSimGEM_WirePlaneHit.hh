//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimGEM_WirePlaneHit.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:38:19 $
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
   \class QweakSimGEM_WirePlaneHit
    
   \brief Handling of a Readoutplane Hit of the GEM detector
     (I know there is no wire plane ... just for consistent class names )

   Placeholder for a long explaination
    
 */
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimGEM_WirePlaneHit_h
#define QweakSimGEM_WirePlaneHit_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimGEM_WirePlaneHit : public G4VHit
{
  public:

      QweakSimGEM_WirePlaneHit();
      QweakSimGEM_WirePlaneHit(G4int GEM_id, G4int wireplane_ID);
      virtual ~QweakSimGEM_WirePlaneHit();

      QweakSimGEM_WirePlaneHit(const QweakSimGEM_WirePlaneHit &right);
      const QweakSimGEM_WirePlaneHit& operator=(const QweakSimGEM_WirePlaneHit &right);
      int operator==(const QweakSimGEM_WirePlaneHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

	  inline float x();
	  inline float y();

      virtual void Draw();
      virtual void Print();

private:
  
  G4int         GEMID;
  G4int         wireplaneID;
  G4double      time;

  G4ThreeVector localPos;
  G4ThreeVector worldPos;

  G4ThreeVector localMomentum;
  G4ThreeVector worldMomentum;
  
  G4ThreeVector originVertexPosition;
  G4ThreeVector originVertexMomentumDirection;
  G4double      originVertexKineticEnergy;
  G4double      originVertexTotalEnergy;

  G4double      currentKineticEnergy;
  G4double      currentTotalEnergy;

  G4double      primaryQ2;
  G4double      crossSection;
  G4double      crossSectionWeight;

  G4int         primaryEventNumber;

public:

  inline void  StoreGEMID(G4int GEM_ID)  { GEMID = GEM_ID; }
  inline G4int   GetGEMID() const { return GEMID; }
  
  inline void  StoreWirePlaneID(G4int wireplane_ID) { wireplaneID = wireplane_ID; }
  inline G4int   GetWirePlaneID()      const { return wireplaneID; }
  //------  
  inline void     StoreGlobalTime(G4double t)    { time = t; }
  inline G4double   GetGlobalTime() const { return time; }
  //------
  inline void          StoreLocalPosition(G4ThreeVector lxyz) { localPos = lxyz; }
  inline G4ThreeVector   GetLocalPosition()      const { return localPos; }
  
  inline void          StoreWorldPosition(G4ThreeVector gxyz) {  worldPos = gxyz; }
  inline G4ThreeVector   GetWorldPosition()       const { return worldPos; }
  //------
  inline void          StoreLocalMomentum(G4ThreeVector lpxyz) { localMomentum = lpxyz; }
  inline G4ThreeVector   GetLocalMomentum()      const {  return localMomentum; }
  
  inline void          StoreWorldMomentum(G4ThreeVector gpxyz) { worldMomentum = gpxyz; }
  inline G4ThreeVector   GetWorldMomentum()       const { return worldMomentum; }
  //------
  inline void          StoreOriginVertexPosition(G4ThreeVector xyz) { originVertexPosition = xyz; }
  inline G4ThreeVector   GetOriginVertexPosition()     const { return originVertexPosition; }
  
  inline void          StoreOriginVertexMomentumDirection(G4ThreeVector pxyz) { originVertexMomentumDirection = pxyz; }
  inline G4ThreeVector   GetOriginVertexMomentumDirection()      const { return originVertexMomentumDirection; }
  
  inline void     StoreOriginVertexKineticEnergy(G4double ekin) { originVertexKineticEnergy = ekin; }
  inline G4double   GetOriginVertexKineticEnergy() const { return originVertexKineticEnergy; }

  inline void     StoreOriginVertexTotalEnergy(G4double et) { originVertexTotalEnergy = et; }
  inline G4double   GetOriginVertexTotalEnergy() const { return originVertexTotalEnergy; }

  //------
  inline void     StorePrimaryEventNumber(G4int en)   { primaryEventNumber = en; }
  inline G4int      GetPrimaryEventNumber() const { return  primaryEventNumber; }
  //------
  inline void     StorePrimaryQ2(G4double q2)   { primaryQ2 = q2; }
  inline G4double   GetPrimaryQ2() const { return primaryQ2; }

  inline void     StoreCrossSection(G4double cs)  {crossSection = cs;}
  inline G4double   GetCrossSection() const {return crossSection;}

  inline void     StoreCrossSectionWeight(G4double csw)  {crossSectionWeight = csw;}
  inline G4double   GetCrossSectionWeight() const {return crossSectionWeight;}

  inline void     StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
  inline G4double   GetKineticEnergy() const { return currentKineticEnergy; }

  inline void     StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
  inline G4double   GetTotalEnergy() const { return currentTotalEnergy; }

  };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<QweakSimGEM_WirePlaneHit> QweakSimGEM_WirePlane_HitsCollection;

extern G4Allocator<QweakSimGEM_WirePlaneHit> QweakSimGEM_WirePlane_HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimGEM_WirePlaneHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)QweakSimGEM_WirePlane_HitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimGEM_WirePlaneHit::operator delete(void* aHit)
{
  QweakSimGEM_WirePlane_HitAllocator.FreeSingle((QweakSimGEM_WirePlaneHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

