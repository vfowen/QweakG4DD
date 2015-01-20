//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_WirePlaneEvent.hh

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:33:13 $

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
   \class QweakSimUserVDC_WirePlaneEvent

   \ingroup root
    
   \brief ROOT Subtree structure for VDC WirePlaneEvent

   Region3.ChamberFront.WirePlane.xyz

   Region3.ChamberBack.WirePlane.xyz

 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_WirePlaneEvent_h
#define QweakSimUserVDC_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_WirePlaneEvent : public TObject
{

private:

  std::vector <Int_t>	PackageID;				///< Package number
  std::vector <Int_t>   TrackID;                ///< ID of the track from which this hit was generated
  std::vector <Float_t> GlobalTimeOfHit;        ///< Global time when this hit was generated

  Int_t NbOfHits;                               ///< Number of hits in this plane
  Int_t HasBeenHit;                             ///< Has this plane been hit? 0 = no, 5 = yes
 
  /// \name Position of the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector <Float_t> LocalPositionX; ///< (cm)
  std::vector <Float_t> LocalPositionY; ///< (cm)
  std::vector <Float_t> LocalPositionZ; ///< (cm)
  //@}
  
  /// \name Position of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> GlobalPositionX; ///< (cm)
  std::vector <Float_t> GlobalPositionY; ///< (cm)
  std::vector <Float_t> GlobalPositionZ; ///< (cm)
  //@}

  /// \name Momentum at the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector <Float_t> LocalMomentumX; ///< (MeV)
  std::vector <Float_t> LocalMomentumY; ///< (MeV)
  std::vector <Float_t> LocalMomentumZ; ///< (MeV)
  //@}

  /// \name Momentum of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> GlobalMomentumX; ///< (MeV)
  std::vector <Float_t> GlobalMomentumY; ///< (MeV)
  std::vector <Float_t> GlobalMomentumZ; ///< (MeV)
  std::vector <Float_t> GlobalThetaAngle;///< (degrees)
  std::vector <Float_t> GlobalPhiAngle;  ///< (degrees, but 90 degrees rotated to keep things interesting)
  //@}

  /// \name Position in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> OriginVertexPositionX; ///< (cm)
  std::vector <Float_t> OriginVertexPositionY; ///< (cm)
  std::vector <Float_t> OriginVertexPositionZ; ///< (cm)
  //@}

  /// \name Direction in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> OriginVertexMomentumDirectionX;
  std::vector <Float_t> OriginVertexMomentumDirectionY;
  std::vector <Float_t> OriginVertexMomentumDirectionZ;
  std::vector <Float_t> OriginVertexThetaAngle; ///< (degrees)
  std::vector <Float_t> OriginVertexPhiAngle;   ///< (degrees)
  //@}

  /// \name Total and kinetic energy at the original vertex of the track from which this hit was generated
  //@{
  std::vector <Float_t> OriginVertexTotalEnergy;        ///< (MeV)
  std::vector <Float_t> OriginVertexKineticEnergy;      ///< (MeV)
  //@}

  /// \name Particle name and type at the hit
  //@{
  std::vector <TString> ParticleName; ///< Name of the particle that caused this hit
  std::vector <Int_t>   ParticleType; ///< \ref Lund_type of the particle that caused this hit (until r4757 this used the \ref geant3_type of the particle)
  //@}

  /// \name Total and kinetic energy of the track at the hit
  //@{
  std::vector <Float_t> TotalEnergy;    ///< (MeV)
  std::vector <Float_t> KineticEnergy;  ///< (MeV)
  //@}

public:
  
  // Constructor
  QweakSimUserVDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_WirePlaneEvent();

  void     Initialize();
  void     Clear(const Option_t* = 0);

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StorePackageID(Int_t pid)    { PackageID.push_back(pid); }
  std::vector <Int_t>      GetPackageID() const {return PackageID;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  std::vector <Int_t>      GetTrackID() const {return TrackID;}


  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  std::vector <TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  std::vector <Int_t>      GetParticleType() const {return  ParticleType;}
    

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  std::vector <Float_t>    GetGlobalTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  std::vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  std::vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}

  void     StoreHasBeenHit(Int_t nu)      { HasBeenHit = nu; }
  Int_t     GetHasBeenHit() const {return HasBeenHit;}

  //-----------------
  void     StoreLocalPositionX(Float_t lx)   { LocalPositionX.push_back(lx); }
  std::vector <Float_t>    GetLocalPositionX() const {return LocalPositionX;}

  void     StoreLocalPositionY(Float_t ly)   { LocalPositionY.push_back(ly); }
  std::vector <Float_t>    GetLocalPositionY() const {return LocalPositionY;}

  void     StoreLocalPositionZ(Float_t lz)   { LocalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetLocalPositionZ() const {return LocalPositionZ;}
  //---
  void     StoreGlobalPositionX(Float_t lx)   { GlobalPositionX.push_back(lx); }
  std::vector <Float_t>    GetGlobalPositionX() const {return GlobalPositionX;}

  void     StoreGlobalPositionY(Float_t ly)   { GlobalPositionY.push_back(ly); }
  std::vector <Float_t>    GetGlobalPositionY() const {return GlobalPositionY;}

  void     StoreGlobalPositionZ(Float_t lz)   { GlobalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetGlobalPositionZ() const {return GlobalPositionZ;}

  //-----------------

  void     StoreLocalMomentumX(Float_t lpx)   { LocalMomentumX.push_back(lpx); }
  std::vector <Float_t>    GetLocalMomentumX() const {return LocalMomentumX;}

  void     StoreLocalMomentumY(Float_t lpy)   { LocalMomentumY.push_back(lpy); }
  std::vector <Float_t>    GetLocalMomentumY() const {return LocalMomentumY;}

  void     StoreLocalMomentumZ(Float_t lpz)   { LocalMomentumZ.push_back(lpz); }
  std::vector <Float_t>    GetLocalMomentumZ() const {return LocalMomentumZ;}
  //---
  void     StoreGlobalMomentumX(Float_t gpx)   { GlobalMomentumX.push_back(gpx); }
  std::vector <Float_t>    GetGlobalMomentumX() const {return GlobalMomentumX;}

  void     StoreGlobalMomentumY(Float_t gpy)   { GlobalMomentumY.push_back(gpy); }
  std::vector <Float_t>    GetGlobalMomentumY() const {return GlobalMomentumY;}

  void     StoreGlobalMomentumZ(Float_t gpz)   { GlobalMomentumZ.push_back(gpz); }
  std::vector <Float_t>    GetGlobalMomentumZ() const {return GlobalMomentumZ;}


  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}

  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX.push_back(vx); }
  std::vector <Float_t>    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY.push_back(vy); }
  std::vector <Float_t>    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ.push_back(vz); }
  std::vector <Float_t>    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX.push_back(vx); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY.push_back(vy); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ.push_back(vz); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy.push_back(ekin); }
  std::vector <Float_t>    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy.push_back(etot); }
  std::vector <Float_t>    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //-----------------

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_WirePlaneEvent,1)

};  // end class QweakSimUserVDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
