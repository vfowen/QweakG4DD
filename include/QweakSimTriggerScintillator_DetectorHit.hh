
// QweakSimTriggerScintillator_DetectorHit.hh
// Klaus Grimm
// 2005-12-27 
  
#ifndef QweakSimTriggerScintillator_DetectorHit_h
#define QweakSimTriggerScintillator_DetectorHit_h 

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTriggerScintillator_DetectorHit : public G4VHit
{
  public:

      QweakSimTriggerScintillator_DetectorHit();
      QweakSimTriggerScintillator_DetectorHit(G4int detector_id);
      virtual ~QweakSimTriggerScintillator_DetectorHit();
      QweakSimTriggerScintillator_DetectorHit(const QweakSimTriggerScintillator_DetectorHit &right);
      const QweakSimTriggerScintillator_DetectorHit& operator=(const QweakSimTriggerScintillator_DetectorHit &right);
      int operator==(const QweakSimTriggerScintillator_DetectorHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

	  inline float x();
	  inline float y();

      virtual void Draw();
      virtual void Print();
  
private:

  G4int    DetectorID;  // octant number
  G4double time;

  G4int TrackID;

  G4ThreeVector localPos;
  G4ThreeVector worldPos;

  G4ThreeVector localMomentum;
  G4ThreeVector worldMomentum;

  G4String      particleName;
  G4int         particleType;
  
  G4ThreeVector    cellPos;
  G4RotationMatrix cellRot;
  const G4LogicalVolume* pLogV;

  G4ThreeVector originVertexPosition;        
  G4ThreeVector originVertexMomentumDirection;
  G4double      originVertexKineticEnergy;
  G4double      originVertexTotalEnergy;

  G4ThreeVector currentMomentumDirection;
  G4double      currentKineticEnergy;
  G4double      currentTotalEnergy;

  G4double      primaryQ2;
  G4double      crossSection;
  G4double      crossSectionWeight;

  G4double	depositedEnergy;

public:

  inline void   StoreDepositedEnergy(G4double dpeg)    {depositedEnergy = dpeg;}
  inline void     AddDepositedEnergy(G4double dpeg)    {depositedEnergy += dpeg;}
  inline G4double GetHitDepositedEnergy() const       {return depositedEnergy;}
  
  inline void   StoreTrackID(G4int tid)    { TrackID = tid; }
  inline G4int GetTrackID() const { return TrackID; }

  inline void   StoreGlobalTime(G4double t)    { time = t; }
  inline G4double GetGlobalTime() const { return time; }
  
  inline void     StoreParticleName(G4String pn)   {particleName = pn;}
  inline G4String   GetParticleName() const {return particleName;}

  void     StoreParticleType(G4int pt)   {particleType = pt;}
  G4int   GetParticleType() const {return particleType;}
  
  //------
  inline void        StoreLocalPosition(G4ThreeVector xyz) { localPos = xyz; }
  inline G4ThreeVector GetLocalPosition()     const { return localPos; }
  
  inline void        StoreWorldPosition(G4ThreeVector xyz) { worldPos = xyz; }
  inline G4ThreeVector GetWorldPosition()     const { return worldPos; }
  //------
  inline void          StoreLocalMomentum(G4ThreeVector lpxyz) { localMomentum = lpxyz; }
  inline G4ThreeVector   GetLocalMomentum()      const {  return localMomentum; }
  
  inline void          StoreWorldMomentum(G4ThreeVector gpxyz) { worldMomentum = gpxyz; }
  inline G4ThreeVector   GetWorldMomentum()       const { return worldMomentum; }
  //------
  inline void        StoreCellPosition(G4ThreeVector xyz) { cellPos = xyz; }
  inline G4ThreeVector GetCellPosition()     const { return cellPos; }
  
  inline void           StoreCellRotation(G4RotationMatrix rmat) { cellRot = rmat; }
  inline G4RotationMatrix GetCellRotation()         const { return cellRot; }
  
  inline void                 StoreLogVolume(G4LogicalVolume* val) { pLogV = val; }
  inline const G4LogicalVolume* GetLogVolume()        const { return pLogV; }
  //------
  inline void        StoreOriginVertexPosition(G4ThreeVector oxyz) { originVertexPosition  = oxyz; }
  inline G4ThreeVector GetOriginVertexPosition()     const { return  originVertexPosition; }
  
  inline void        StoreOriginVertexMomentumDirection(G4ThreeVector opxyz) { originVertexMomentumDirection  = opxyz; }
  inline G4ThreeVector GetOriginVertexMomentumDirection()      const { return  originVertexMomentumDirection; }

  inline void   StoreOriginVertexKineticEnergy(G4double oekin) { originVertexKineticEnergy  = oekin; }
  inline G4double GetOriginVertexKineticEnergy() const {  return originVertexKineticEnergy; }

  inline void   StoreOriginVertexTotalEnergy(G4double oetot) { originVertexTotalEnergy  = oetot; }
  inline G4double GetOriginVertexTotalEnergy() const {  return originVertexTotalEnergy; }

  //------

  inline void        StoreMomentumDirection(G4ThreeVector pxyz) { currentMomentumDirection  = pxyz; }
  inline G4ThreeVector GetMomentumDirection()      const { return currentMomentumDirection; }

  inline void   StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
  inline G4double GetKineticEnergy() const { return currentKineticEnergy; }

  inline void   StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
  inline G4double GetTotalEnergy() const { return currentTotalEnergy; }

  inline void     StorePrimaryQ2(G4double q2)   { primaryQ2 = q2; }
  inline G4double   GetPrimaryQ2() const { return primaryQ2; }

  inline void     StoreCrossSection(G4double cs)  {crossSection = cs;}
  inline G4double   GetCrossSection() const {return crossSection;}

  inline void     StoreCrossSectionWeight(G4double csw)  {crossSectionWeight = csw;}
  inline G4double   GetCrossSectionWeight() const {return crossSectionWeight;}


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<QweakSimTriggerScintillator_DetectorHit> QweakSimTriggerScintillator_DetectorHitsCollection;

extern G4Allocator<QweakSimTriggerScintillator_DetectorHit>  QweakSimTriggerScintillator_DetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimTriggerScintillator_DetectorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) QweakSimTriggerScintillator_DetectorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimTriggerScintillator_DetectorHit::operator delete(void* aHit)
{
   QweakSimTriggerScintillator_DetectorHitAllocator.FreeSingle((QweakSimTriggerScintillator_DetectorHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_DetectorHit.hh,v $
//      Revision 1.2  2005/12/27 19:27:53  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
