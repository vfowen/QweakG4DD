
// QweakSimUserPMTOnly_DetectorEvent.hh
// Martin McHugh
// 2013-07-20

/////// --------------------------------------------------------------------

#ifndef QweakSimUserPMTOnly_DetectorEvent_h
#define QweakSimUserPMTOnly_DetectorEvent_h

/////// --------------------------------------------------------------------

//--- system includes
#include <vector>

//--- root includes
#include "TObject.h"
#include "TString.h"


/////// --------------------------------------------------------------------

class QweakSimUserPMTOnly_DetectorEvent : public TObject
{
	
private:
		
    Int_t                PrimaryEventNumber;
	
    std::vector<Float_t> TrackID;
    std::vector<TString> ParticleName;
    std::vector<Int_t>   ParticleType;
	
    std::vector<Float_t> GlobalTimeOfHit;
	
    Int_t                HasBeenHit;
    std::vector<Int_t>   EdgeEventFlag;
    Int_t                NbOfHits;
    
    Int_t                SecondaryElectronCount;
	
    std::vector<Float_t> HitGlobalPositionX;
    std::vector<Float_t> HitGlobalPositionY;
    std::vector<Float_t> HitGlobalPositionZ;
	
    std::vector<Float_t> HitLocalPositionX;
    std::vector<Float_t> HitLocalPositionY;
    std::vector<Float_t> HitLocalPositionZ;
	
    std::vector<Float_t> HitLocalExitPositionX;
    std::vector<Float_t> HitLocalExitPositionY;
    std::vector<Float_t> HitLocalExitPositionZ;
	
    std::vector<Float_t> OriginVertexPositionX;
    std::vector<Float_t> OriginVertexPositionY;
    std::vector<Float_t> OriginVertexPositionZ;
	
    std::vector<Float_t> LocalVertexMomentumDirectionX;
    std::vector<Float_t> LocalVertexMomentumDirectionY;
    std::vector<Float_t> LocalVertexMomentumDirectionZ;
	
    std::vector<Float_t> OriginVertexMomentumDirectionX;
    std::vector<Float_t> OriginVertexMomentumDirectionY;
    std::vector<Float_t> OriginVertexMomentumDirectionZ;
	
    std::vector<Float_t> OriginVertexThetaAngle;
    std::vector<Float_t> OriginVertexPhiAngle;
	
    std::vector<Float_t> OriginVertexKineticEnergy;
    std::vector<Float_t> OriginVertexTotalEnergy;
	
    std::vector<Float_t> LocalVertexKineticEnergy;
    std::vector<Float_t> LocalVertexTotalEnergy;
	
    std::vector<Float_t> GlobalPhiAngle;
    std::vector<Float_t> GlobalThetaAngle;
	
    //--- deposited energy in the PMTOnly in one step
    std::vector<Float_t> DepositedEnergy;

    //--- total deposited energy in the PMTOnly in one event
    Float_t TotalDepositedEnergy;
	
public:
	
    //--- Constructor
    QweakSimUserPMTOnly_DetectorEvent();

    //--- Destructor 
    virtual ~QweakSimUserPMTOnly_DetectorEvent();
 
    //void SetTree(TTree *data);
    void Initialize();
	
    //----------------- PrimaryEventNumber
	
    void StorePrimaryEventNumber(Int_t pen)     { PrimaryEventNumber = pen; }
    Int_t  GetPrimaryEventNumber() const    {return PrimaryEventNumber;}
	
    //----------------- TrackID
	
    void   StoreTrackID(Float_t tid)        { TrackID.push_back(tid); }
    std::vector<Float_t>  GetTrackID() const      {return TrackID;}
	
    //----------------- ParticleName & ParticleType
	
    void   StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
    std::vector<TString>  GetParticleName() const    {return  ParticleName;}
	
    void   StoreParticleType(Int_t pt)       { ParticleType.push_back(pt); }
    std::vector<Int_t>    GetParticleType() const    {return  ParticleType;}
	
    //----------------- GlobalTimeOfHit
	
    void   StoreGlobalTimeOfHit(Float_t gtime)   { GlobalTimeOfHit.push_back(gtime); }
    std::vector<Float_t>  GetGloablTimeOfHit() const       {return GlobalTimeOfHit;}
	
    //----------------- HasBeenHit & EdgeEventFlag & NbOfHits
	
    void  StoreDetectorHasBeenHit(Int_t n)    { HasBeenHit = n; }
    Int_t   GetDetectorHasBeenHit() const  {return HasBeenHit;}
	
    void  StoreEdgeEventFlag(Int_t flag)      { EdgeEventFlag.push_back(flag); }
    std::vector<Int_t>   GetEdgeEventFlag() const       {return EdgeEventFlag;}
	
    void  StoreDetectorNbOfHits(Int_t nd)     { NbOfHits = nd; }
    Int_t   GetDetectorNbOfHits() const    {return  NbOfHits;}
	
    //----------------- HitGlobalPosition
	
    void   StoreDetectorGlobalPositionX(Float_t lx)     { HitGlobalPositionX.push_back(lx); }
    std::vector<Float_t>  GetDetectorGlobalPositionX() const     {return HitGlobalPositionX;}
	
    void   StoreDetectorGlobalPositionY(Float_t ly)     { HitGlobalPositionY.push_back(ly); }
    std::vector<Float_t>  GetDetectorGlobalPositionY() const     {return HitGlobalPositionY;}
	
    void   StoreDetectorGlobalPositionZ(Float_t lz)     { HitGlobalPositionZ.push_back(lz); }
    std::vector<Float_t>  GetDetectorGlobalPositionZ() const     {return HitGlobalPositionZ;}
	
    //----------------- HitLocalPosition
	
    void   StoreDetectorLocalPositionX(Float_t lx)   { HitLocalPositionX.push_back(lx); }
    std::vector<Float_t>  GetDetectorLocalPositionX() const    {return HitLocalPositionX;}
	
    void   StoreDetectorLocalPositionY(Float_t ly)   { HitLocalPositionY.push_back(ly); }
    std::vector<Float_t>  GetDetectorLocalPositionY() const    {return HitLocalPositionY;}
	
    void   StoreDetectorLocalPositionZ(Float_t lz)   { HitLocalPositionZ.push_back(lz); }
    std::vector<Float_t>  GetDetectorLocalPositionZ() const    {return HitLocalPositionZ;}
	
    //----------------- HitLocalExitPosition
	
    void   StoreDetectorLocalExitPositionX(Float_t lx)    { HitLocalExitPositionX.push_back(lx); }
    std::vector<Float_t>  GetDetectorLocalExitPositionX() const     {return HitLocalExitPositionX;}

    void   StoreDetectorLocalExitPositionY(Float_t ly)    { HitLocalExitPositionY.push_back(ly); }
    std::vector<Float_t>  GetDetectorLocalExitPositionY() const     {return HitLocalExitPositionY;}
	
    void   StoreDetectorLocalExitPositionZ(Float_t lz)    { HitLocalExitPositionZ.push_back(lz); }
    std::vector<Float_t>  GetDetectorLocalExitPositionZ() const     {return HitLocalExitPositionZ;}
	
    //----------------- OriginVertexPosition
	
    void   StoreOriginVertexPositionX(Float_t vx)     { OriginVertexPositionX.push_back(vx); }
    std::vector<Float_t>  GetOriginVertexPositionX() const     {return OriginVertexPositionX;}
	
    void   StoreOriginVertexPositionY(Float_t vy)     { OriginVertexPositionY.push_back(vy); }
    std::vector<Float_t>  GetOriginVertexPositionY() const     {return OriginVertexPositionY;}
	
    void   StoreOriginVertexPositionZ(Float_t vz)     { OriginVertexPositionZ.push_back(vz); }
    std::vector<Float_t>  GetOriginVertexPositionZ() const     {return OriginVertexPositionZ;}
	
    //----------------- LocalVertexMomentumDirection
	
    void   StoreLocalVertexMomentumDirectionX(Float_t vx)     { LocalVertexMomentumDirectionX.push_back(vx); }
    std::vector<Float_t>  GetLocalVertexMomentumDirectionX() const     {return LocalVertexMomentumDirectionX;}
	
    void   StoreLocalVertexMomentumDirectionY(Float_t vy)     { LocalVertexMomentumDirectionY.push_back(vy); }
    std::vector<Float_t>  GetLocalVertexMomentumDirectionY() const     {return LocalVertexMomentumDirectionY;}
	
    void   StoreLocalVertexMomentumDirectionZ(Float_t vz)     { LocalVertexMomentumDirectionZ.push_back(vz); }
    std::vector<Float_t>  GetLocalVertexMomentumDirectionZ() const     {return LocalVertexMomentumDirectionZ;}
	
    //----------------- OrinVertexMomentumDirection
	
    void   StoreOriginVertexMomentumDirectionX(Float_t vx)     { OriginVertexMomentumDirectionX.push_back(vx); }
    std::vector<Float_t>  GetOriginVertexMomentumDirectionX() const     {return OriginVertexMomentumDirectionX;}

    void   StoreOriginVertexMomentumDirectionY(Float_t vy)     { OriginVertexMomentumDirectionY.push_back(vy); }
    std::vector<Float_t>  GetOriginVertexMomentumDirectionY() const     {return OriginVertexMomentumDirectionY;}

    void   StoreOriginVertexMomentumDirectionZ(Float_t vz)     { OriginVertexMomentumDirectionZ.push_back(vz); }
    std::vector<Float_t>  GetOriginVertexMomentumDirectionZ() const     {return OriginVertexMomentumDirectionZ;}
 
    //----------------- OriginVertexThetaAngle & PhiAngle

    void   StoreOriginVertexThetaAngle(Float_t theta)    { OriginVertexThetaAngle.push_back(theta); }
    std::vector<Float_t>  GetOriginVertexThetaAngle() const       {return OriginVertexThetaAngle;}
 
    void   StoreOriginVertexPhiAngle(Float_t phi)        { OriginVertexPhiAngle.push_back(phi); }
    std::vector<Float_t>  GetOriginVertexPhiAngle() const         {return OriginVertexPhiAngle;}
 
    //----------------- OrigiVertexKineticEnergy & TotalEnergy
	
    void   StoreOriginVertexKineticEnergy(Float_t ekin)    { OriginVertexKineticEnergy.push_back(ekin); }
    std::vector<Float_t>  GetOriginVertexKineticEnergy() const      {return OriginVertexKineticEnergy;}
	
    void   StoreOriginVertexTotalEnergy(Float_t etot)      { OriginVertexTotalEnergy.push_back(etot); }
    std::vector<Float_t>  GetOriginVertexTotalEnergy() const        {return OriginVertexTotalEnergy;}
	
    //----------------- LocalVertexKinetcEnergy & TotalEnergy
	
    void   StoreDetectorLocalVertexKineticEnergy(Float_t ekin)    { LocalVertexKineticEnergy.push_back(ekin); }
    std::vector<Float_t>  GetDetectorLocalVertexKineticEnergy() const       {return LocalVertexKineticEnergy;}

    void   StoreDetectorLocalVertexTotalEnergy(Float_t etot)    { LocalVertexTotalEnergy.push_back(etot); }
    std::vector<Float_t>  GetDetectorLocalVertexTotalEnergy() const       {return LocalVertexTotalEnergy;}
	
    //----------------- GlobalThetaAngle & PhiAngle
	
    void   StoreGlobalThetaAngle(Float_t theta)    { GlobalThetaAngle.push_back(theta); }
    std::vector<Float_t>  GetGlobalThetaAngle() const       {return GlobalThetaAngle;}
	
    void   StoreGlobalPhiAngle(Float_t phi)        { GlobalPhiAngle.push_back(phi); }
    std::vector<Float_t>  GetGlobalPhiAngle() const         {return GlobalPhiAngle;}
	
    //----------------- PMTOnly deposited energy
	
    //--- deposited energy in the PMTOnly in one step
    void   StoreDepositedEnergy(Float_t dpeg)    { 
      DepositedEnergy.push_back(dpeg); 
      TotalDepositedEnergy += dpeg;
    }
    std::vector<Float_t>  GetDepositedEnergy() const      {return DepositedEnergy;}
	
    //--- total deposited energy in the PMTOnly in one event
    void     StoreTotalEnergyDeposit(Float_t eng)   { TotalDepositedEnergy = eng; }
    Float_t    GetTotalEnergyDeposit()   const {return TotalDepositedEnergy;}
	
    // define a new Class known to ROOT  
    ClassDef(QweakSimUserPMTOnly_DetectorEvent,1)
	
};  // end class QweakSimUserPMTOnly_DetectorEvent 


/////// --------------------------------------------------------------------

#endif 

/////// --------------------------------------------------------------------

