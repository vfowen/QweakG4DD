
// QweakSimLeadGlass_DetectorHit.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlass_DetectorHit_h
#define QweakSimLeadGlass_DetectorHit_h 1

//--- user includes
#include "QweakSimHit.hh"



/////// --------------------------------------------------------------------

class QweakSimLeadGlass_DetectorHit : public G4VHit
{
	
public:
	
    //--- Constructor
    QweakSimLeadGlass_DetectorHit();
    QweakSimLeadGlass_DetectorHit(G4int detector_id);
	
    //--- Destructor
    virtual ~QweakSimLeadGlass_DetectorHit();
	
    //--- Copy Constructor
    QweakSimLeadGlass_DetectorHit(const QweakSimLeadGlass_DetectorHit &right);
	
    //--- Assignment Operator
    const QweakSimLeadGlass_DetectorHit& operator=(const QweakSimLeadGlass_DetectorHit &right);
	
    int operator==(const QweakSimLeadGlass_DetectorHit &right) const;
	
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
	
    inline float x();
    inline float y();
	
    //--- methods
    virtual void Draw();
    virtual void Print();
	
private:
	
    G4int         detectorID;
	
    G4int         primaryEventNumber;
	
    G4double      trackID;
	
    G4String      particleName;
    G4int         particleType;
	
    G4double      time;
	
    G4int         hasBeenHit;
    G4int         edgeEventFlag;
    G4int         nbOfHits;
	
    //G4int       secondaryElectronCount;
	
    G4ThreeVector worldPos;
    G4ThreeVector localPos;
    G4ThreeVector localExitPos;
    G4ThreeVector originVertexPosition;
	
    G4ThreeVector worldMomentum;
    G4ThreeVector localMomentum;
    G4ThreeVector currentMomentumDirection;
    G4ThreeVector originVertexMomentumDirection;
	
    //--- calculated in Event Action
    //G4double      originVertexThetaAngle;
    //G4double      originVertexPhiAngle;
	
    G4double      originVertexKineticEnergy;
    G4double      originVertexTotalEnergy;
	
    G4double      currentKineticEnergy;
    G4double      currentTotalEnergy;
	
    //G4double      primaryQ2;
    //G4double      crossSection;
    //G4double      crossSectionWeight;
	
    //--- calculated in Event Action
    //G4double      globalThetaAngle;
    //G4double      globalPhiAngle;
	
    //--- LeadGlass deposited energy
    G4double      depositedEnergyHit;

	
    G4ThreeVector          cellPos;
    G4RotationMatrix       cellRot;
    const G4LogicalVolume* pLogV;


public:
	
    //----------------- PrimaryEventNumber
	
    inline void StorePrimaryEventNumber(G4int pen)     { primaryEventNumber = pen; }
    inline G4int  GetPrimaryEventNumber() const    {return primaryEventNumber;}
	
    //----------------- TrackID
	
    inline void   StoreTrackID(G4double tid)       { trackID = tid; }
    inline G4double GetTrackID() const        {return trackID;}
	
    //----------------- PrarticleName & ParticleType
	
    inline void   StoreParticleName(G4String pn)   {particleName = pn;}
    inline G4String GetParticleName() const   {return particleName;}
	
    inline void   StoreParticleType(G4int pt)      {particleType = pt;}
    inline G4int    GetParticleType() const   {return particleType;}
	
    //----------------- GlobalTimeOfHit
	
    inline void   StoreGlobalTime(G4double t)      { time = t; }
    inline G4double GetGlobalTime() const     {return time;}
	
    //----------------- HasBeenHit & EdgeEventFlag & NbOfHits
	
    inline void  StoreHasBeenHit(G4int n)         { hasBeenHit = n; }
    inline G4int   GetHasBeenHit() const       {return hasBeenHit;}
	
    inline void  StoreEdgeEventFlag(G4int flag)   { edgeEventFlag = flag; }
    inline G4int   GetEdgeEventFlag() const    {return edgeEventFlag;}

    inline void  StoreNbOfHits(G4int nd)          { nbOfHits = nd; }
    inline G4int   GetNbOfHits() const         {return  nbOfHits;}
	
    //----------------- Position
	
    //--- GlobalPosition
    inline void  StoreWorldPosition(G4ThreeVector xyz)         { worldPos = xyz; }
    inline G4ThreeVector GetWorldPosition() const         {return worldPos;}
	
    //--- LocalPosition
    inline void  StoreLocalPosition(G4ThreeVector xyz)         { localPos = xyz; }
    inline G4ThreeVector GetLocalPosition() const         {return localPos;}
	
    //--- LoclaExitPosition
    inline void  StoreLocalExitPosition(G4ThreeVector xyz)     { localExitPos = xyz; }
    inline G4ThreeVector GetLocalExitPosition() const     {return localExitPos;}
	
    //--- OriginVertexPosition
    inline void  StoreOriginVertexPosition(G4ThreeVector oxyz) { originVertexPosition = oxyz; }
    inline G4ThreeVector GetOriginVertexPosition() const  {return  originVertexPosition;}

    //----------------- Momentum
	
    //--- GlobalMomentum
    inline void  StoreWorldMomentum(G4ThreeVector gpxyz)     { worldMomentum = gpxyz; }
    inline G4ThreeVector GetWorldMomentum() const       {return worldMomentum;}
	
    //--- LocalMomentum
    inline void  StoreLocalMomentum(G4ThreeVector lpxyz)     { localMomentum = lpxyz; }
    inline G4ThreeVector GetLocalMomentum() const       {return localMomentum;}
	
    //--- LocalVertexMomentumDirection
    inline void  StoreMomentumDirection(G4ThreeVector pxyz)  { currentMomentumDirection = pxyz; }
    inline G4ThreeVector GetMomentumDirection() const   {return currentMomentumDirection;}

    //--- OriginVertexMomentumDirection
    inline void  StoreOriginVertexMomentumDirection(G4ThreeVector opxyz)  { originVertexMomentumDirection = opxyz; }
    inline G4ThreeVector GetOriginVertexMomentumDirection() const   {return originVertexMomentumDirection;}
	
    //---------------- OriginVertexThetaAngle & PhiAngle
	
    //inline void   StoreOriginVertexThetaAngle(G4double thetag)   { originVertexThetaAngle = thetag; }
    //inline G4double GetOriginVertexThetaAngle() const      {return originVertexThetaAngle;}
	
    //inline void   StoreOriginVertexPhiAngle(G4double phiag)      { originVertexPhiAngle = phiag; }
    //inline G4double GetOriginVertexPhiAngle() const        {return originVertexPhiAngle;}
	
    //---------------- OriginVertexKineticEnergy & TotalEnergy
	
    inline void   StoreOriginVertexKineticEnergy(G4double oekin)   { originVertexKineticEnergy = oekin; }
    inline G4double GetOriginVertexKineticEnergy() const       {return originVertexKineticEnergy;}
	
    inline void   StoreOriginVertexTotalEnergy(G4double oetot)     { originVertexTotalEnergy = oetot; }
    inline G4double GetOriginVertexTotalEnergy() const         {return originVertexTotalEnergy;}	
	
    //---------------- LocalVertexKineticEnergy & TotalEnergy
	
    inline void   StoreKineticEnergy(G4double ekin)   { currentKineticEnergy = ekin; }
    inline G4double GetKineticEnergy() const       {return currentKineticEnergy;}
	
    inline void   StoreTotalEnergy(G4double etot)     { currentTotalEnergy = etot; }
    inline G4double GetTotalEnergy() const         {return currentTotalEnergy;}
	
    //---------------- 
	
    //inline void   StorePrimaryQ2(G4double q2)              { primaryQ2 = q2; }
    //inline G4double GetPrimaryQ2() const               {return primaryQ2;}
	
    //inline void   StoreCrossSection(G4double cs)           { crossSection = cs; }
    //inline G4double GetCrossSection() const            {return crossSection;}
	
    //inline void   StoreCrossSectionWeight(G4double csw)    { crossSectionWeight = csw; }
    //inline G4double GetCrossSectionWeight() const      {return crossSectionWeight;}
	
    //---------------- LocalThetaAngle & PhiAngle
	
    //inline void   StoreGlobalThetaAngle(G4double gthetag)   { globalThetaAngle = gthetag; }
    //inline G4double GetGlobalThetaAngle() const       {return globalThetaAngle;}
	
    //inline void   StoreGlobalPhiAngle(G4double gphiag)      { globalPhiAngle = gphiag; }
    //inline G4double GetGlobalPhiAngle() const         {return globalPhiAngle;}
	
    //--------------- LeadGlass deposited energy
	
    inline void   StoreHitDepositedEnergy(G4double dpeg) { depositedEnergyHit = dpeg; }
    inline G4double GetHitDepositedEnergy() const {return depositedEnergyHit;}
	
	
    //---
    inline void   StoreCellPosition(G4ThreeVector xyz)      { cellPos = xyz; }
    inline G4ThreeVector GetCellPosition() const         {return cellPos;}
	
    inline void   StoreCellRotation(G4RotationMatrix rmat)  { cellRot = rmat; }
    inline G4RotationMatrix GetCellRotation() const      {return cellRot;}
	
    inline void   StoreLogVolume(G4LogicalVolume* val)      { pLogV = val; }
    inline const G4LogicalVolume* GetLogVolume() const   {return pLogV;}
	
	
};



/////// --------------------------------------------------------------------

typedef G4THitsCollection<QweakSimLeadGlass_DetectorHit> QweakSimLeadGlass_DetectorHitsCollection;

extern G4Allocator<QweakSimLeadGlass_DetectorHit>  QweakSimLeadGlass_DetectorHitAllocator;



/////// --------------------------------------------------------------------

inline void* QweakSimLeadGlass_DetectorHit::operator new(size_t)
{
    void* aHit;
    aHit = (void*) QweakSimLeadGlass_DetectorHitAllocator.MallocSingle();
    return aHit;
}



/////// --------------------------------------------------------------------

inline void QweakSimLeadGlass_DetectorHit::operator delete(void* aHit)
{
    QweakSimLeadGlass_DetectorHitAllocator.FreeSingle((QweakSimLeadGlass_DetectorHit*) aHit);
}



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------

