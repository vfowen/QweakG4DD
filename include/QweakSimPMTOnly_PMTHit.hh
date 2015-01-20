
// QweakSimPMTOnly_PMTHit.hh
// Martin McHugh
// 2013-08-01

/////// --------------------------------------------------------------------

#ifndef QweakSimPMTOnly_PMTHit_h
#define QweakSimPMTOnly_PMTHit_h 

//--- user includes
#include "QweakSimHit.hh"

/////// --------------------------------------------------------------------

class QweakSimPMTOnly_PMTHit : public G4VHit
{
	
  public:
	
    QweakSimPMTOnly_PMTHit();
    QweakSimPMTOnly_PMTHit(const QweakSimPMTOnly_PMTHit &right);
	
    virtual ~QweakSimPMTOnly_PMTHit();

    const QweakSimPMTOnly_PMTHit & operator=(const QweakSimPMTOnly_PMTHit &right);
    int operator==(const QweakSimPMTOnly_PMTHit &right) const;
	
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
	
  private:
	
    G4int    myHitID;
    G4double currentPhotonEnergy;
	
  public:
  
    inline void StoreHitID(G4int hitID) { myHitID = hitID; }
    inline G4int GetHitID() const { return myHitID; }
    	
    inline void StorePhotonEnergy(G4double eng) { currentPhotonEnergy  = eng; }
    inline G4double GetPhotonEnergy() const { return currentPhotonEnergy; }
	
};

/////// --------------------------------------------------------------------

typedef G4THitsCollection<QweakSimPMTOnly_PMTHit> QweakSimPMTOnly_PMTHitsCollection;

extern G4Allocator<QweakSimPMTOnly_PMTHit>  QweakSimPMTOnly_PMTHitAllocator;

/////// --------------------------------------------------------------------

inline void* QweakSimPMTOnly_PMTHit::operator new(size_t)
{
    void* aHit;
    aHit = (void*) QweakSimPMTOnly_PMTHitAllocator.MallocSingle();
    return aHit;
}

/////// --------------------------------------------------------------------

inline void QweakSimPMTOnly_PMTHit::operator delete(void* aHit)
{
    QweakSimPMTOnly_PMTHitAllocator.FreeSingle((QweakSimPMTOnly_PMTHit*) aHit);
}

/////// --------------------------------------------------------------------

#endif

