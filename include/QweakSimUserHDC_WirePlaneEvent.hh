//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserHDC_WirePlaneEvent.hh

   $Date: Fri Jul  3 10:16:54 CDT 2009$

   \author Klaus Hans Grimm
   \author Jie Pan
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimUserHDC_WirePlaneEvent
    
   \ingroup root

   \brief ROOT Subtree structure for HDC WirePlaneEvent
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserHDC_WirePlaneEvent_h
#define QweakSimUserHDC_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_WirePlaneEvent : public TObject
{

private:

  std::vector <Int_t>	PackageID;				///< Package number
  std::vector <Int_t>   TrackID;                ///< ID of the track from which this hit was generated
  std::vector <Float_t> GlobalTimeOfHit;        ///< Global time when this hit was generated

  Int_t   NbOfHits;             ///< Number of hits in this plane
  Int_t   PlaneHasBeenHit;      ///< Has this plane been hit? 0 = no, 5 = yes

  /// \name Position of the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector <Float_t> PlaneLocalPositionX;
  std::vector <Float_t> PlaneLocalPositionY;
  std::vector <Float_t> PlaneLocalPositionZ;
  ///@}
  
  /// \name Position of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> PlaneGlobalPositionX;
  std::vector <Float_t> PlaneGlobalPositionY;
  std::vector <Float_t> PlaneGlobalPositionZ;
  //@}

  /// \name Momentum of the hit in local coordinates
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector <Float_t> PlaneLocalMomentumX;
  std::vector <Float_t> PlaneLocalMomentumY;
  std::vector <Float_t> PlaneLocalMomentumZ;
  //@}

  /// \name Momentum of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> PlaneGlobalMomentumX;
  std::vector <Float_t> PlaneGlobalMomentumY;
  std::vector <Float_t> PlaneGlobalMomentumZ;
  std::vector <Float_t> GlobalPhiAngle;
  std::vector <Float_t> GlobalThetaAngle;
  //@}

  /// \name Position in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  std::vector <Float_t> OriginVertexPositionX;
  std::vector <Float_t> OriginVertexPositionY;
  std::vector <Float_t> OriginVertexPositionZ;
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

  /// \name Particle name and type at the hit
  //@{
  std::vector <TString> ParticleName; ///< Name of the particle that caused this hit
  std::vector <Int_t>   ParticleType; ///< \ref Lund_type of the particle that caused this hit (until r4757 this used the \ref geant3_type of the particle)
  //@}
  
  /// \name Total and kinetic energy at the original vertex of the track from which this hit was generated
  //@{
  std::vector <Float_t> OriginVertexTotalEnergy;        ///< (MeV)
  std::vector <Float_t> OriginVertexKineticEnergy;      ///< (MeV)
  //@}

  /// \name Total and kinetic energy of the track at the hit
  //@{
  std::vector <Float_t> TotalEnergy;    ///< (MeV)
  std::vector <Float_t> KineticEnergy;  ///< (MeV)
  //@}

public:
  
  // Constructor
  QweakSimUserHDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserHDC_WirePlaneEvent();

  void     Initialize();
  void     Clear(const Option_t* = 0);

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StorePackageID(Int_t pid)    { PackageID.push_back(pid); }
    std::vector <Int_t>      GetPackageID() const {return PackageID;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  std::vector <Int_t>      GetTrackID() const {return TrackID;}

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  std::vector <Float_t>    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  //-----------------
  // Setter/Getter for X,U,V wire planes 

  void     StorePlaneHasBeenHit(Int_t nx)      { PlaneHasBeenHit = nx; }
  Int_t    GetPlaneHasBeenHit() const {return  PlaneHasBeenHit;}

  //-----------------
  void     StorePlaneLocalPositionX(Float_t lx)   { PlaneLocalPositionX.push_back(lx); }
  std::vector <Float_t>    GetPlaneLocalPositionX() const {return PlaneLocalPositionX;}

  void     StorePlaneLocalPositionY(Float_t ly)   { PlaneLocalPositionY.push_back(ly); }
  std::vector <Float_t>    GetPlaneLocalPositionY() const {return PlaneLocalPositionY;}

  void     StorePlaneLocalPositionZ(Float_t lz)   { PlaneLocalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetPlaneLocalPositionZ() const {return PlaneLocalPositionZ;}
  //---
  void     StorePlaneGlobalPositionX(Float_t gx)   { PlaneGlobalPositionX.push_back(gx); }
  std::vector <Float_t>    GetPlaneGlobalPositionX() const {return PlaneGlobalPositionX;}

  void     StorePlaneGlobalPositionY(Float_t gy)   { PlaneGlobalPositionY.push_back(gy); }
  std::vector <Float_t>    GetPlaneGlobalPositionY() const {return PlaneGlobalPositionY;}

  void     StorePlaneGlobalPositionZ(Float_t gz)   { PlaneGlobalPositionZ.push_back(gz); }
  std::vector <Float_t>    GetPlaneGlobalPositionZ() const {return PlaneGlobalPositionZ;}
  //-----------------
  void     StorePlaneLocalMomentumX(Float_t lpx)   { PlaneLocalMomentumX.push_back(lpx); }
  std::vector <Float_t>    GetPlaneLocalMomentumX() const {return  PlaneLocalMomentumX;}

  void     StorePlaneLocalMomentumY(Float_t lpy)   { PlaneLocalMomentumY.push_back(lpy); }
  std::vector <Float_t>    GetPlaneLocalMomentumY() const {return  PlaneLocalMomentumY;}

  void     StorePlaneLocalMomentumZ(Float_t lpz)   { PlaneLocalMomentumZ.push_back(lpz); }
  std::vector <Float_t>    GetPlaneLocalMomentumZ() const {return  PlaneLocalMomentumZ;}
  //---
  void     StorePlaneGlobalMomentumX(Float_t gpx)   { PlaneGlobalMomentumX.push_back(gpx); }
  std::vector <Float_t>    GetPlaneGlobalMomentumX() const {return  PlaneGlobalMomentumX;}

  void     StorePlaneGlobalMomentumY(Float_t gpy)   { PlaneGlobalMomentumY.push_back(gpy); }
  std::vector <Float_t>    GetPlaneGlobalMomentumY() const {return  PlaneGlobalMomentumY;}

  void     StorePlaneGlobalMomentumZ(Float_t gpz)   { PlaneGlobalMomentumZ.push_back(gpz); }
  std::vector <Float_t>    GetPlaneGlobalMomentumZ() const {return  PlaneGlobalMomentumZ;}
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
  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}
  
  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}
  //-----------------
  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  std::vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}
  
  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  std::vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}

  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  std::vector <TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  std::vector <Int_t>      GetParticleType() const {return  ParticleType;}
  

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserHDC_WirePlaneEvent,1)

};  // end class QweakSimUserHDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

