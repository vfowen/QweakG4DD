//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_DriftCellHit.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:32:12 $
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
   \class QweakSimVDC_DriftCellHit
    
   \brief Region 3 Vertical Drift Chamber Drift Cell Hit

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
//  Update Date:      $Date: 2005/12/27 19:32:12 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_DriftCellHit_h
#define QweakSimVDC_DriftCellHit_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimVDC_DriftCellHit : public G4VHit
{
  public:

      QweakSimVDC_DriftCellHit();
      QweakSimVDC_DriftCellHit(G4int dc_id);
      virtual ~QweakSimVDC_DriftCellHit();
      QweakSimVDC_DriftCellHit(const QweakSimVDC_DriftCellHit &right);
      const QweakSimVDC_DriftCellHit& operator=(const QweakSimVDC_DriftCellHit &right);
      int operator==(const QweakSimVDC_DriftCellHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

	  inline float x();
	  inline float y();

      virtual void Draw();
      virtual void Print();
  
private:
  G4int driftCellID;
  G4int driftCellPlaneID;
  G4double time;

  G4ThreeVector localPos;
  G4ThreeVector worldPos;

  G4ThreeVector    cellPos;
  G4RotationMatrix cellRot;
  const G4LogicalVolume* pLogV;

  G4ThreeVector originVertexPosition;        
  G4ThreeVector originVertexMomentumDirection;
  G4double      originVertexKineticEnergy;

  G4ThreeVector currentMomentumDirection;
  G4double      currentKineticEnergy;
  G4double      currentTotalEnergy;

  G4double      dcWidthOnFrame; 
  G4double      dcFullThickness;
  G4double      dcUPlaneWireAngle;
  G4double      dcVPlaneWireAngle;

  public:
      inline void StoreDriftCellID(G4int dc_id) { driftCellID = dc_id; }
      inline G4int GetDriftCellID() const { return driftCellID; }

      inline void StoreDriftCellPlaneID(G4int dcplane_id) { driftCellPlaneID = dcplane_id; }
      inline G4int GetDriftCellPlaneID() const { return driftCellPlaneID; }

      inline void StoreTime(G4double t) { time = t; }
      inline G4double GetTime() const { return time; }
      inline void StoreLocalPos(G4ThreeVector xyz) { localPos = xyz; }
      inline G4ThreeVector GetLocalPos() const { return localPos; }
      inline void StoreWorldPos(G4ThreeVector xyz) { worldPos = xyz; }
      inline G4ThreeVector GetWorldPos() const { return worldPos; }


      inline void StoreCellPos(G4ThreeVector xyz) { cellPos = xyz; }
      inline G4ThreeVector GetCellPos() const { return cellPos; }
      inline void StoreCellRot(G4RotationMatrix rmat) { cellRot = rmat; }
      inline G4RotationMatrix GetCellRot() const { return cellRot; }
      inline void StoreLogV(G4LogicalVolume* val) { pLogV = val; }
      inline const G4LogicalVolume* GetLogV() const { return pLogV; }


      inline void StoreOriginVertexPosition(G4ThreeVector xyz) { originVertexPosition  = xyz; }
      inline G4ThreeVector GetOriginVertexPosition() const { return originVertexPosition; }
      inline void StoreOriginVertexMomentumDirection(G4ThreeVector pxyz) { originVertexMomentumDirection  = pxyz; }
      inline G4ThreeVector GetOriginVertexMomentumDirection() const { return originVertexMomentumDirection; }
      inline void StoreOriginVertexKineticEnergy(G4double ekin) { originVertexKineticEnergy  = ekin; }
      inline G4double GetOriginVertexKineticEnergy() const { return originVertexKineticEnergy; }

      inline void StoreMomentumDirection(G4ThreeVector pxyz) { currentMomentumDirection  = pxyz; }
      inline G4ThreeVector GetMomentumDirection() const { return currentMomentumDirection; }
      inline void StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
      inline G4double GetKineticEnergy() const { return currentKineticEnergy; }
      inline void StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
      inline G4double GetTotalEnergy() const { return currentTotalEnergy; }

      inline void StoreDCWidthOnFrame(G4double dcw) { dcWidthOnFrame  = dcw; }
      inline G4double GetDCWidthOnFrame() const { return dcWidthOnFrame; }
      inline void StoreDCFullThickness(G4double dct) { dcFullThickness  = dct; }
      inline G4double GetDCFullThickness() const { return dcFullThickness; }
      inline void StoreDCUPlaneWireAngle(G4double dca) { dcUPlaneWireAngle  = dca; }
      inline G4double GetDCUPlaneWireAngle() const { return dcUPlaneWireAngle; }
      inline void StoreDCVPlaneWireAngle(G4double dca) { dcVPlaneWireAngle  = dca; }
      inline G4double GetDCVPlaneWireAngle() const { return dcVPlaneWireAngle; }
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<QweakSimVDC_DriftCellHit> QweakSimVDC_DriftCellHitsCollection;

extern G4Allocator<QweakSimVDC_DriftCellHit> QweakSimVDC_DriftCellHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimVDC_DriftCellHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)QweakSimVDC_DriftCellHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimVDC_DriftCellHit::operator delete(void* aHit)
{
  QweakSimVDC_DriftCellHitAllocator.FreeSingle((QweakSimVDC_DriftCellHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellHit.hh,v $
//      Revision 1.2  2005/12/27 19:32:12  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 


