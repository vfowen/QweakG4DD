
// QweakSimLeadGlass_PMTSD.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlass_PMTSD_h
#define QweakSimLeadGlass_PMTSD_h 

//--- user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"



/////// --------------------------------------------------------------------

//--- user classes
class QweakSimLeadGlass_PMTHitsCollection;



/////// --------------------------------------------------------------------

class QweakSimLeadGlass_PMTSD : public G4VSensitiveDetector
{
	
public:
    QweakSimLeadGlass_PMTSD(G4String name);
    ~QweakSimLeadGlass_PMTSD();
	
    void Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
    void EndOfEvent(G4HCofThisEvent* HCE);
	
private:
	
    QweakSimLeadGlass_PMTHitsCollection*  LeadGlass_PMTHitsCollection;
    G4int LeadGlassPMT_CollectionID;
	
};


/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
