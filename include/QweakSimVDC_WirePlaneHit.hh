//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_WirePlaneHit.hh

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:40:49 $

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
   \class QweakSimVDC_WirePlaneHit
    
   \brief Handling of a U-WirePlane and/or V-WirePlane Hit of the VDC.

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_WirePlaneHit_h
#define QweakSimVDC_WirePlaneHit_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimVDC_WirePlaneHit : public G4VHit
{
  public:

      QweakSimVDC_WirePlaneHit();
      QweakSimVDC_WirePlaneHit(G4int vdc_id, G4int wireplane_ID);
      virtual ~QweakSimVDC_WirePlaneHit();
      QweakSimVDC_WirePlaneHit(const QweakSimVDC_WirePlaneHit &right);
      const QweakSimVDC_WirePlaneHit& operator=(const QweakSimVDC_WirePlaneHit &right);
      int operator==(const QweakSimVDC_WirePlaneHit &right) const;

      void *operator new(size_t);
      void operator delete(void *aHit);

      virtual void Draw();
      virtual void Print();

private:
  
  G4int         vdcID;
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

  G4String      particleName;
  G4int         particleType;

public:

  void  StoreVDCID(G4int vdc_ID)  { vdcID = vdc_ID; }
  G4int   GetVDCID() const { return vdcID; }
  
  void  StoreWirePlaneID(G4int wireplane_ID) { wireplaneID = wireplane_ID; }
  G4int   GetWirePlaneID()      const { return wireplaneID; }
  //------  
  void     StoreGlobalTime(G4double t)    { time = t; }
  G4double   GetGlobalTime() const { return time; }
  //------
  void          StoreLocalPosition(G4ThreeVector lxyz) { localPos = lxyz; }
  G4ThreeVector   GetLocalPosition()      const { return localPos; }
  
  void          StoreWorldPosition(G4ThreeVector gxyz) {  worldPos = gxyz; }
  G4ThreeVector   GetWorldPosition()       const { return worldPos; }
  //------
  void          StoreLocalMomentum(G4ThreeVector lpxyz) { localMomentum = lpxyz; }
  G4ThreeVector   GetLocalMomentum()      const {  return localMomentum; }
  
  void          StoreWorldMomentum(G4ThreeVector gpxyz) { worldMomentum = gpxyz; }
  G4ThreeVector   GetWorldMomentum()       const { return worldMomentum; }
  //------
  void          StoreOriginVertexPosition(G4ThreeVector xyz) { originVertexPosition = xyz; }
  G4ThreeVector   GetOriginVertexPosition()     const { return originVertexPosition; }
  
  void          StoreOriginVertexMomentumDirection(G4ThreeVector pxyz) { originVertexMomentumDirection = pxyz; }
  G4ThreeVector   GetOriginVertexMomentumDirection()      const { return originVertexMomentumDirection; }
  
  void     StoreOriginVertexKineticEnergy(G4double ekin) { originVertexKineticEnergy = ekin; }
  G4double   GetOriginVertexKineticEnergy() const { return originVertexKineticEnergy; }
  
  void     StoreOriginVertexTotalEnergy(G4double et) { originVertexTotalEnergy = et; }
  G4double   GetOriginVertexTotalEnergy() const { return originVertexTotalEnergy; }

  //------
  void     StorePrimaryEventNumber(G4int en)   { primaryEventNumber = en; }
  G4int      GetPrimaryEventNumber() const { return  primaryEventNumber; }
  //------
  void     StorePrimaryQ2(G4double q2)   { primaryQ2 = q2; }
  G4double   GetPrimaryQ2() const { return primaryQ2; }

  void     StoreCrossSection(G4double cs)  {crossSection = cs;}
  G4double   GetCrossSection() const {return crossSection;}

  void     StoreCrossSectionWeight(G4double csw)  {crossSectionWeight = csw;}
  G4double   GetCrossSectionWeight() const {return crossSectionWeight;}


  void     StoreParticleName(G4String pn)   {particleName = pn;}
  G4String   GetParticleName() const {return particleName;}

  void     StoreParticleType(G4int pt)   {particleType = pt;}
  G4int   GetParticleType() const {return particleType;}

  void     StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
  G4double   GetKineticEnergy() const { return currentKineticEnergy; }

  void     StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
  G4double   GetTotalEnergy() const { return currentTotalEnergy; }


  };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<QweakSimVDC_WirePlaneHit> QweakSimVDC_WirePlane_HitsCollection;

extern G4Allocator<QweakSimVDC_WirePlaneHit> QweakSimVDC_WirePlane_HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimVDC_WirePlaneHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)QweakSimVDC_WirePlane_HitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimVDC_WirePlaneHit::operator delete(void* aHit)
{
  QweakSimVDC_WirePlane_HitAllocator.FreeSingle((QweakSimVDC_WirePlaneHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

