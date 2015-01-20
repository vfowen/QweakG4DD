
// QweakSimPMTOnly_DetectorSD.hh
// Martin McHugh
// 2013-07-20

/////// --------------------------------------------------------------------

#ifndef QweakSimPMTOnly_DetectorSD_h
#define QweakSimPMTOnly_DetectorSD_h 

//--- user includes
#include "QweakSimPMTOnly_DetectorHit.hh"
#include "QweakSimSensitiveDetectorDeclaration.hh"



/////// --------------------------------------------------------------------

class QweakSimPMTOnly_DetectorSD : public G4VSensitiveDetector
{
	
public:
    QweakSimPMTOnly_DetectorSD(G4String name);
    ~QweakSimPMTOnly_DetectorSD();
	
    void   Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void   EndOfEvent(G4HCofThisEvent* HCE);
	
private:
	
    QweakSimPMTOnly_DetectorHitsCollection*  PMTOnly_DetectorHitsCollection;
    G4int  PMTOnly_CollectionID;
	
};



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
