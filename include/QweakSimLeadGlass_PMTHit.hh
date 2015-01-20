
// QweakSimLeadGlass_PMTHit.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlass_PMTHit_h
#define QweakSimLeadGlass_PMTHit_h 

//--- user includes
#include "QweakSimHit.hh"



/////// --------------------------------------------------------------------

class QweakSimLeadGlass_PMTHit : public G4VHit
{
	
public:
	
    QweakSimLeadGlass_PMTHit();
    QweakSimLeadGlass_PMTHit(G4int detector_id);
	
    virtual ~QweakSimLeadGlass_PMTHit();

    QweakSimLeadGlass_PMTHit(const QweakSimLeadGlass_PMTHit &right);
    const QweakSimLeadGlass_PMTHit & operator=(const QweakSimLeadGlass_PMTHit &right);
    int operator==(const QweakSimLeadGlass_PMTHit &right) const;
	
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
	
    inline float x();
    inline float y();
	
    //virtual void Draw();
    //virtual void Print();
	
private:
	
    G4int    PMTID;
    G4double currentPhotonEnergy;
	
public:
	
    inline void StorePMTID(G4int pmt_id) { PMTID = pmt_id; }
    inline G4int GetPMTID() const { return PMTID; }
	
    inline void   StorePhotonEnergy(G4double eng) { currentPhotonEnergy  = eng; }
    inline G4double GetPhotonEnergy() const { return currentPhotonEnergy; }
	
};



/////// --------------------------------------------------------------------

typedef G4THitsCollection<QweakSimLeadGlass_PMTHit> QweakSimLeadGlass_PMTHitsCollection;

extern G4Allocator<QweakSimLeadGlass_PMTHit>  QweakSimLeadGlass_PMTHitAllocator;



/////// --------------------------------------------------------------------

inline void* QweakSimLeadGlass_PMTHit::operator new(size_t)
{
    void* aHit;
    aHit = (void*) QweakSimLeadGlass_PMTHitAllocator.MallocSingle();
    return aHit;
}



/////// --------------------------------------------------------------------

inline void QweakSimLeadGlass_PMTHit::operator delete(void* aHit)
{
    QweakSimLeadGlass_PMTHitAllocator.FreeSingle((QweakSimLeadGlass_PMTHit*) aHit);
}



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
