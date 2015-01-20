//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserTriggerScintillator_DetectorEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:30:53 $
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
   \class QweakSimUserTriggerScintillator_DetectorEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Trigger Scintillator DetectorEvent
    
 */
//=============================================================================
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserTriggerScintillator_DetectorEvent_h
#define QweakSimUserTriggerScintillator_DetectorEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserTriggerScintillator_DetectorEvent : public TObject
{

private:

  /// \todo add DetectorID
  Int_t TrackID;                ///< ID of the track from which this hit was generated

  Float_t GlobalTimeOfHit;      ///< Global time when this hit was generated

  Int_t HasBeenHit;             ///< Has this detector been hit? 0 = no, 5 = yes
  Int_t EdgeEventFlag;          ///< (not used)
  Int_t NbOfHits;               ///< Number of hits in this detector
  Int_t SecondaryElectronCount;


  std::vector <Float_t> SecElecLocalOriginX;
  std::vector <Float_t> SecElecLocalOriginY;
  std::vector <Float_t> SecElecLocalOriginZ;

  std::vector <Float_t> SecElecLocalMomentumX;
  std::vector <Float_t> SecElecLocalMomentumY;
  std::vector <Float_t> SecElecLocalMomentumZ;

  std::vector <Float_t> SecElecLocalEnergy;
  
  /// \name Position of the hit in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  Float_t HitLocalPositionX;
  Float_t HitLocalPositionY;
  Float_t HitLocalPositionZ;
  //@}

  /// \name Position where the hit exits the detector in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  Float_t HitLocalExitPositionX;
  Float_t HitLocalExitPositionY;
  Float_t HitLocalExitPositionZ;
  //@}

  /// \name Position of the hit in global coordinates (cm)
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t HitGlobalPositionX;
  Float_t HitGlobalPositionY;
  Float_t HitGlobalPositionZ;
  //@}

  /// \name Position in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexPositionX;
  Float_t OriginVertexPositionY;
  Float_t OriginVertexPositionZ;
  //@}

  /// \name Direction in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexMomentumDirectionX;
  Float_t OriginVertexMomentumDirectionY;
  Float_t OriginVertexMomentumDirectionZ;
  Float_t OriginVertexThetaAngle;       ///< (degrees)
  Float_t OriginVertexPhiAngle;         ///< (degrees)
  //@}

  /// \name Original vertex kinetic and total energy of the track from which this hit was generated (where the track started)
  //@{
  Float_t OriginVertexKineticEnergy;
  Float_t OriginVertexTotalEnergy;
  Float_t LocalVertexTotalEnergy;
  //@}

  /// \name Direction of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t GlobalThetaAngle;     ///< (degrees)
  Float_t GlobalPhiAngle;       ///< (degrees, but 90 degrees rotated to keep things interesting)
  //@}

  /// \name Particle name and type at the hit
  //@{
  std::vector <TString> ParticleName; ///< Name of the particle that caused this hit
  std::vector <Int_t>   ParticleType; ///< \ref Lund_type of the particle that caused this hit (until r4757 this used the \ref geant3_type of the particle)
  //@}

  std::vector<Float_t> DepositedEnergy;		//--- deposited energy in one step
  Float_t TotalDepositedEnergy;			//--- event total
    
public:
  
  // Constructor
  QweakSimUserTriggerScintillator_DetectorEvent();
  // Destructor 
  virtual ~QweakSimUserTriggerScintillator_DetectorEvent();

  void Initialize();

  //-----------------
  void     StoreTrackID(Int_t tid)  { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit = gtime; }
  Float_t    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}
  
  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  std::vector <TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  std::vector <Int_t>      GetParticleType() const {return  ParticleType;}
  
  //-----------------
  void     StoreDetectorHasBeenHit(Int_t n)      { HasBeenHit = n; }
  Int_t      GetDetectorHasBeenHit() const {return HasBeenHit;}
  //-----------------
  void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
  Int_t      GetDetectorNbOfHits() const {return  NbOfHits;}
  //-----------------
  void     StoreDetectorLocalPositionX(Float_t lx)   { HitLocalPositionX = lx; }
  Float_t    GetDetectorLocalPositionX() const {return HitLocalPositionX;}

  void     StoreDetectorLocalPositionY(Float_t ly)   { HitLocalPositionY = ly; }
  Float_t    GetDetectorLocalPositionY() const {return HitLocalPositionY;}

  void     StoreDetectorLocalPositionZ(Float_t lz)   { HitLocalPositionZ = lz; }
  Float_t    GetDetectorLocalPositionZ() const {return HitLocalPositionZ;}
  //-----------------
  void     StoreDetectorLocalExitPositionX(Float_t lx)   { HitLocalExitPositionX = lx; }
  Float_t    GetDetectorLocalExitPositionX() const {return HitLocalExitPositionX;}

  void     StoreDetectorLocalExitPositionY(Float_t ly)   { HitLocalExitPositionY = ly; }
  Float_t    GetDetectorLocalExitPositionY() const {return HitLocalExitPositionY;}

  void     StoreDetectorLocalExitPositionZ(Float_t lz)   { HitLocalExitPositionZ = lz; }
  Float_t    GetDetectorLocalExitPositionZ() const {return HitLocalExitPositionZ;}
  //---
  void     StoreDetectorGlobalPositionX(Float_t lx)   { HitGlobalPositionX = lx; }
  Float_t    GetDetectorGlobalPositionX() const {return HitGlobalPositionX;}

  void     StoreDetectorGlobalPositionY(Float_t ly)   { HitGlobalPositionY = ly; }
  Float_t    GetDetectorGlobalPositionY() const {return HitGlobalPositionY;}

  void     StoreDetectorGlobalPositionZ(Float_t lz)   { HitGlobalPositionZ = lz; }
  Float_t    GetDetectorGlobalPositionZ() const {return HitGlobalPositionZ;}
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX = vx; }
  Float_t    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY = vy; }
  Float_t    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ = vz; }
  Float_t    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX = vx; }
  Float_t    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY = vy; }
  Float_t    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ = vz; }
  Float_t    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle = theta; }
  Float_t    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle = phi; }
  Float_t    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy = ekin; }
  Float_t    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy = etot; }
  Float_t    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}

  void     StoreDetectorLocalVertexTotalEnergy(Float_t etot) { LocalVertexTotalEnergy = etot; };
  Float_t    GetDetectorLocalVertexTotalEnergy() {return LocalVertexTotalEnergy;};

  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle = theta; }
  Float_t    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle = phi; }
  Float_t    GetGlobalPhiAngle() const {return GlobalPhiAngle;}


    //--- deposited energy in TS in one step
    void   StoreDepositedEnergy(Float_t dpeg)    { 
      DepositedEnergy.push_back(dpeg); 
      TotalDepositedEnergy += dpeg;
    }
    std::vector<Float_t>  GetDepositedEnergy() const      {return DepositedEnergy;}
	
    //--- total deposited energy in TS in one event
    void     StoreTotalEnergyDeposit(Float_t eng)   { TotalDepositedEnergy = eng; }
    Float_t    GetTotalEnergyDeposit()   const {return TotalDepositedEnergy;}

  void AddSecondaryElectronEvent(Float_t XO, Float_t YO, Float_t ZO,
      Float_t XM, Float_t YM, Float_t ZM,
      Float_t energy);

  void     StoreEdgeEventFlag(Int_t flag) {EdgeEventFlag = flag;};
  Int_t    GetEdgeEventFlag() {return EdgeEventFlag;};

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserTriggerScintillator_DetectorEvent,1)

};  // end class QweakSimUserTriggerScintillator_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserTriggerScintillator_DetectorEvent.hh,v $
//      Revision 1.2  2005/12/27 19:30:53  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
