
// QweakSimTarget_DetectorHit.hh
// Wouter Deconinck
// 2014-10-07

/////// --------------------------------------------------------------------

#ifndef QweakSimTarget_DetectorHit_h
#define QweakSimTarget_DetectorHit_h 1

//--- user includes
#include "QweakSimHit.hh"

/////// --------------------------------------------------------------------

class QweakSimTarget_DetectorHit : public G4VHit
{
	
public:
	
    //--- Constructor
    QweakSimTarget_DetectorHit();
	
    //--- Destructor
    virtual ~QweakSimTarget_DetectorHit();

    //--- Copy Constructor
    QweakSimTarget_DetectorHit(const QweakSimTarget_DetectorHit &right);

    //--- Assignment Operator
    const QweakSimTarget_DetectorHit& operator=(const QweakSimTarget_DetectorHit &right);

    int operator==(const QweakSimTarget_DetectorHit &right) const;

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
	
    G4ThreeVector worldPos;
    G4ThreeVector localPos;
    G4ThreeVector localExitPos;
    G4ThreeVector originVertexPosition;
	
    G4ThreeVector worldMomentum;
    G4ThreeVector localMomentum;
    G4ThreeVector currentMomentumDirection;
    G4ThreeVector originVertexMomentumDirection;
	
    G4double      originVertexKineticEnergy;
    G4double      originVertexTotalEnergy;
	
    G4double      currentKineticEnergy;
    G4double      currentTotalEnergy;
	
    //--- Target deposited energy
    G4double      depositedEnergy;

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
	
    //--------------- Target deposited energy
	
    inline void   StoreDepositedEnergy(G4double dpeg)    {depositedEnergy = dpeg;}
    inline void     AddDepositedEnergy(G4double dpeg)    {depositedEnergy += dpeg;}
    inline G4double GetHitDepositedEnergy() const       {return depositedEnergy;}
	
	
    //---
    inline void   StoreCellPosition(G4ThreeVector xyz)      { cellPos = xyz; }
    inline G4ThreeVector GetCellPosition() const         {return cellPos;}
	
    inline void   StoreCellRotation(G4RotationMatrix rmat)  { cellRot = rmat; }
    inline G4RotationMatrix GetCellRotation() const      {return cellRot;}
	
    inline void   StoreLogVolume(G4LogicalVolume* val)      { pLogV = val; }
    inline const G4LogicalVolume* GetLogVolume() const   {return pLogV;}
	
};

/////// --------------------------------------------------------------------

typedef G4THitsCollection<QweakSimTarget_DetectorHit> QweakSimTarget_DetectorHitsCollection;

extern G4Allocator<QweakSimTarget_DetectorHit>  QweakSimTarget_DetectorHitAllocator;

/////// --------------------------------------------------------------------

inline void* QweakSimTarget_DetectorHit::operator new(size_t)
{
    void* aHit;
    aHit = (void*) QweakSimTarget_DetectorHitAllocator.MallocSingle();
    return aHit;
}

/////// --------------------------------------------------------------------

inline void QweakSimTarget_DetectorHit::operator delete(void* aHit)
{
    QweakSimTarget_DetectorHitAllocator.FreeSingle((QweakSimTarget_DetectorHit*) aHit);
}

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
