
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_DetectorEvent.hh
   $Revision: 1.3 $	
   $Date: 2006/01/06 20:31:24 $
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
   \class QweakSimUserCerenkov_DetectorEvent 
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov DetectorEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/06 20:31:24 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_DetectorEvent_h
#define QweakSimUserCerenkov_DetectorEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_DetectorEvent : public TObject
{

private:

  std::vector<Int_t>   DetectorID; ///< ID of the detector in which this hit was registered
  Int_t   TrackID;    ///< ID of the track from which this hit was generated

  std::vector<Float_t> GlobalTimeOfHit;      ///< Global time when this hit was generated (ns)

  Int_t HasBeenHit;             ///< Has this detector been hit? 0 = no, 5 = yes
  std::vector<Int_t> EdgeEventFlag;          ///< Was the distance between hit and exit position below 1.5 cm? 0 = no, 1 = yes
  Int_t NbOfHits;               ///< Number of hits in this detector

  Int_t SecondaryParticleCount; ///< Number of secondary particles
  Int_t SecondaryElectronCount; ///< Number of secondary electrons
  Int_t SecondaryPhotonCount;   ///< Number of secondary photons
  Int_t SecondaryPositronCount; ///< Number of secondary positrons

  Int_t OpticalPhotonCount;     ///< Number of optical photons

  /// \name Position in local coordinates of original vertex of the secondary in this event
  /// The global coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> SecPartLocalOriginX;
  std::vector<Float_t> SecPartLocalOriginY;
  std::vector<Float_t> SecPartLocalOriginZ;
  //@}

  /// \name Momentum in local coordinates of original vertex of the secondary in this event
  /// The global coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> SecPartLocalMomentumX;
  std::vector<Float_t> SecPartLocalMomentumY;
  std::vector<Float_t> SecPartLocalMomentumZ;
  //@}

  std::vector<Float_t> SecPartLocalEnergy;
  std::vector<Float_t> SecPartLocalType;

  std::vector<Double_t> CerenkovPhotonEnergy;
  
  /// \name Position of the hit in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> HitLocalPositionX; ///< (cm)
  std::vector<Float_t> HitLocalPositionY; ///< (cm)
  std::vector<Float_t> HitLocalPositionZ; ///< (cm)
  //@}

  /// \name Position where the track exits the volume in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> HitLocalExitPositionX; ///< (cm)
  std::vector<Float_t> HitLocalExitPositionY; ///< (cm)
  std::vector<Float_t> HitLocalExitPositionZ; ///< (cm)
  //@}

  /// \name Position of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector<Float_t> HitGlobalPositionX;    ///< (cm)
  std::vector<Float_t> HitGlobalPositionY;    ///< (cm)
  std::vector<Float_t> HitGlobalPositionZ;    ///< (cm)
  //@}

  /// \name Position in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector<Float_t> OriginVertexPositionX; ///< (cm)
  std::vector<Float_t> OriginVertexPositionY; ///< (cm)
  std::vector<Float_t> OriginVertexPositionZ; ///< (cm)
  //@}

  /// \name Direction in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector<Float_t> OriginVertexMomentumDirectionX;
  std::vector<Float_t> OriginVertexMomentumDirectionY;
  std::vector<Float_t> OriginVertexMomentumDirectionZ;
  std::vector<Float_t> OriginVertexThetaAngle;       ///< (degrees)
  std::vector<Float_t> OriginVertexPhiAngle;         ///< (degrees)
  //@}

  std::vector<Float_t> OriginVertexKineticEnergy;
  std::vector<Float_t> OriginVertexTotalEnergy;

  /// \name Direction of the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> LocalMomentumX;      ///< (GeV/c)
  std::vector<Float_t> LocalMomentumY;      ///< (GeV/c)
  std::vector<Float_t> LocalMomentumZ;      ///< (GeV/c)
  std::vector<Float_t> LocalThetaAngle;     ///< (degrees)
  std::vector<Float_t> LocalPhiAngle;       ///< (degrees, but 90 degrees rotated to keep things interesting)
  //@}

  /// \name Direction of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector<Float_t> GlobalMomentumX;      ///< (GeV/c)
  std::vector<Float_t> GlobalMomentumY;      ///< (GeV/c)
  std::vector<Float_t> GlobalMomentumZ;      ///< (GeV/c)
  std::vector<Float_t> GlobalThetaAngle;     ///< (degrees)
  std::vector<Float_t> GlobalPhiAngle;       ///< (degrees, but 90 degrees rotated to keep things interesting)
  //@}

  /// \name Particle name, type, id, parentID at the hit
  //@{
  std::vector<TString> ParticleName;         ///< Name of the particle type of this hit
  std::vector<Int_t>   ParticleType;         ///< \ref Lund_type of the particle type of this hit
  std::vector<Int_t>   ParticleID;           ///< Id of this hit
  std::vector<Int_t>   ParentID;             ///< Id of the parent of this hit
  std::vector<TString> CreatorProcessName;   ///< Process name that created this hit
  //@}

  /// \name Polarization of the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> PolarizationX;        ///< (dimensionless, normalized)
  std::vector<Float_t> PolarizationY;        ///< (dimensionless, normalized)
  std::vector<Float_t> PolarizationZ;        ///< (dimensionless, normalized)
  std::vector<Float_t> LongitudinalPolarization; ///< (dimensionless, normalized)
  std::vector<Float_t> TransversePolarization;  ///< (dimensionless, normalized)
  std::vector<Float_t> TransversePolarizationX; ///< (dimensionless, normalized)
  std::vector<Float_t> TransversePolarizationY; ///< (dimensionless, normalized)
  std::vector<Float_t> TransversePolarizationZ; ///< (dimensionless, normalized)
  std::vector<Float_t> TransversePolarizationPhiAngle; ///< (degrees)

  //@}

  /// \name Total and kinetic energy of the track at the hit
  //@{
  std::vector<Float_t> TotalEnergy;          ///< (MeV)
  std::vector<Float_t> KineticEnergy;        ///< (MeV)
  //@}

public:
  
  // Constructor
  QweakSimUserCerenkov_DetectorEvent();
  // Destructor 
  virtual ~QweakSimUserCerenkov_DetectorEvent();

  void Initialize();

  //-----------------
  void     StoreDetectorID(Int_t did)  { DetectorID.push_back(did); }
  std::vector<Int_t>      GetDetectorID() const {return DetectorID;}
  //-----------------

  void     StoreTrackID(Int_t tid)  { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}

  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  std::vector<TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  std::vector<Int_t>      GetParticleType() const {return  ParticleType;}

  void     StoreParentID(Int_t Pid)      { ParentID.push_back(Pid); }
  std::vector<Int_t>      GetParentID() const {return  ParentID;}

  void     StoreCreatorProcessName(TString name)      { CreatorProcessName.push_back(name); }
  std::vector<TString>      GetCreatorProcessName() const {return  CreatorProcessName;}
  
  void     StoreParticleID(Int_t pid)      { ParticleID.push_back(pid); }
  std::vector<Int_t>      GetParticleID() const {return  ParticleID;}
  
  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  std::vector<Float_t>    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  std::vector<Float_t>    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  std::vector<Float_t>    GetKineticEnergy() const {return KineticEnergy;}

  //-----------------

  void     StorePolarizationX(Float_t px)   { PolarizationX.push_back(px); }
  std::vector<Float_t>    GetPolarizationX() const {return PolarizationX;}

  void     StorePolarizationY(Float_t py)   { PolarizationY.push_back(py); }
  std::vector<Float_t>    GetPolarizationY() const {return PolarizationY;}

  void     StorePolarizationZ(Float_t pz)   { PolarizationZ.push_back(pz); }
  std::vector<Float_t>    GetPolarizationZ() const {return PolarizationZ;}

  void     StoreLongitudinalPolarization(Float_t pl)   { LongitudinalPolarization.push_back(pl); }
  std::vector<Float_t>    GetLongitudinalPolarization() const {return LongitudinalPolarization;}

  void     StoreTransversePolarization(Float_t pt)   { TransversePolarization.push_back(pt); }
  std::vector<Float_t>    GetTransversePolarization() const {return TransversePolarization;}

  void     StoreTransversePolarizationX(Float_t pt)   { TransversePolarizationX.push_back(pt); }
  std::vector<Float_t>    GetTransversePolarizationX() const {return TransversePolarizationX;}

  void     StoreTransversePolarizationY(Float_t pt)   { TransversePolarizationY.push_back(pt); }
  std::vector<Float_t>    GetTransversePolarizationY() const {return TransversePolarizationY;}

  void     StoreTransversePolarizationZ(Float_t pt)   { TransversePolarizationZ.push_back(pt); }
  std::vector<Float_t>    GetTransversePolarizationZ() const {return TransversePolarizationZ;}

  void     StoreTransversePolarizationPhiAngle(Float_t phi)   { TransversePolarizationPhiAngle.push_back(phi); }
  std::vector<Float_t>    GetTransversePolarizationPhiAngle() const {return TransversePolarizationPhiAngle;}

  //-----------------

  void     StoreDetectorHasBeenHit(Int_t n)      { HasBeenHit = n; }
  Int_t      GetDetectorHasBeenHit() const {return HasBeenHit;}
  //-----------------
  void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
  Int_t      GetDetectorNbOfHits() const {return  NbOfHits;}
  //-----------------
  void     StoreDetectorLocalPositionX(Float_t lx)   { HitLocalPositionX.push_back(lx); }
  std::vector<Float_t>    GetDetectorLocalPositionX() const {return HitLocalPositionX;}

  void     StoreDetectorLocalPositionY(Float_t ly)   { HitLocalPositionY.push_back(ly); }
  std::vector<Float_t>    GetDetectorLocalPositionY() const {return HitLocalPositionY;}

  void     StoreDetectorLocalPositionZ(Float_t lz)   { HitLocalPositionZ.push_back(lz); }
  std::vector<Float_t>    GetDetectorLocalPositionZ() const {return HitLocalPositionZ;}
  //-----------------
  void     StoreDetectorLocalExitPositionX(Float_t lx)   { HitLocalExitPositionX.push_back(lx); }
  std::vector<Float_t>    GetDetectorLocalExitPositionX() const {return HitLocalExitPositionX;}

  void     StoreDetectorLocalExitPositionY(Float_t ly)   { HitLocalExitPositionY.push_back(ly); }
  std::vector<Float_t>    GetDetectorLocalExitPositionY() const {return HitLocalExitPositionY;}

  void     StoreDetectorLocalExitPositionZ(Float_t lz)   { HitLocalExitPositionZ.push_back(lz); }
  std::vector<Float_t>    GetDetectorLocalExitPositionZ() const {return HitLocalExitPositionZ;}
  //---
  void     StoreDetectorGlobalPositionX(Float_t lx)   { HitGlobalPositionX.push_back(lx); }
  std::vector<Float_t>    GetDetectorGlobalPositionX() const {return HitGlobalPositionX;}

  void     StoreDetectorGlobalPositionY(Float_t ly)   { HitGlobalPositionY.push_back(ly); }
  std::vector<Float_t>    GetDetectorGlobalPositionY() const {return HitGlobalPositionY;}

  void     StoreDetectorGlobalPositionZ(Float_t lz)   { HitGlobalPositionZ.push_back(lz); }
  std::vector<Float_t>    GetDetectorGlobalPositionZ() const {return HitGlobalPositionZ;}
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX.push_back(vx); }
  std::vector<Float_t>    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY.push_back(vy); }
  std::vector<Float_t>    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ.push_back(vz); }
  std::vector<Float_t>    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX.push_back(vx); }
  std::vector<Float_t>    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY.push_back(vy); }
  std::vector<Float_t>    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ.push_back(vz); }
  std::vector<Float_t>    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle.push_back(theta); }
  std::vector<Float_t>    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle.push_back(phi); }
  std::vector<Float_t>    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy.push_back(ekin); }
  std::vector<Float_t>    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy.push_back(etot); }
  std::vector<Float_t>    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}

  //----------------

  void     StoreLocalMomentumX(Float_t px) { LocalMomentumX.push_back(px); }
  std::vector<Float_t>    GetLocalMomentumX() const  {return LocalMomentumX;}

  void     StoreLocalMomentumY(Float_t py) { LocalMomentumY.push_back(py); }
  std::vector<Float_t>    GetLocalMomentumY() const  {return LocalMomentumY;}

  void     StoreLocalMomentumZ(Float_t pz) { LocalMomentumZ.push_back(pz); }
  std::vector<Float_t>    GetLocalMomentumZ() const  {return LocalMomentumZ;}

  void     StoreLocalThetaAngle(Float_t theta) { LocalThetaAngle.push_back(theta); }
  std::vector<Float_t>    GetLocalThetaAngle() const  {return LocalThetaAngle;}

  void     StoreLocalPhiAngle(Float_t phi)  { LocalPhiAngle.push_back(phi); }
  std::vector<Float_t>    GetLocalPhiAngle() const {return LocalPhiAngle;}

  //----------------

  void     StoreGlobalMomentumX(Float_t px) { GlobalMomentumX.push_back(px); }
  std::vector<Float_t>    GetGlobalMomentumX() const  {return GlobalMomentumX;}

  void     StoreGlobalMomentumY(Float_t py) { GlobalMomentumY.push_back(py); }
  std::vector<Float_t>    GetGlobalMomentumY() const  {return GlobalMomentumY;}

  void     StoreGlobalMomentumZ(Float_t pz) { GlobalMomentumZ.push_back(pz); }
  std::vector<Float_t>    GetGlobalMomentumZ() const  {return GlobalMomentumZ;}

  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  std::vector<Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  std::vector<Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}

  //----------------

  void AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
				 Float_t XM, Float_t YM, Float_t ZM,
				 Float_t energy, Int_t type);

  void     StoreEdgeEventFlag(Int_t flag) {EdgeEventFlag.push_back(flag);};
  std::vector<Int_t>    GetEdgeEventFlag() {return EdgeEventFlag;};

  void     StoreOpticalPhotonCount(Int_t cnt){OpticalPhotonCount = cnt;};
  Int_t GetOpticalPhotonCount() {return OpticalPhotonCount;}

  void StoreCerenkovPhotonEnergy(Double_t eng) {CerenkovPhotonEnergy.push_back(eng);};
  std::vector<Double_t> GetCerenkovPhotonEnergy() {return CerenkovPhotonEnergy;}

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserCerenkov_DetectorEvent,1)

};  // end class QweakSimUserCerenkov_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_DetectorEvent.hh,v $
//      Revision 1.3  2006/01/06 20:31:24  grimm
//      Added KineticEnergy, TotalEnergy, ParticleType, and ParticleName into the root tree
//
//      Revision 1.2  2005/12/27 19:28:31  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

