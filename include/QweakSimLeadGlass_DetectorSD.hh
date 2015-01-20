
// QweakSimLeadGlass_DetectorSD.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlass_DetectorSD_h
#define QweakSimLeadGlass_DetectorSD_h 

//--- user includes
#include "QweakSimLeadGlass_DetectorHit.hh"
#include "QweakSimSensitiveDetectorDeclaration.hh"



/////// --------------------------------------------------------------------

class QweakSimLeadGlass_DetectorSD : public G4VSensitiveDetector
{
	
public:
    QweakSimLeadGlass_DetectorSD(G4String name);
    ~QweakSimLeadGlass_DetectorSD();
	
    void   Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
    void   EndOfEvent(G4HCofThisEvent* HCE);
	
private:
	
    QweakSimLeadGlass_DetectorHitsCollection*  LeadGlass_DetectorHitsCollection;
    G4int  LeadGlass_CollectionID;
	
};



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
