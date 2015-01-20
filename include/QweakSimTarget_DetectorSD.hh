
// QweakSimTarget_DetectorSD.hh
// Wouter Deconinck
// 20134-10-07

/////// --------------------------------------------------------------------

#ifndef QweakSimTarget_DetectorSD_h
#define QweakSimTarget_DetectorSD_h

//--- user includes
#include "QweakSimTarget_DetectorHit.hh"
#include "QweakSimSensitiveDetectorDeclaration.hh"



/////// --------------------------------------------------------------------

class QweakSimTarget_DetectorSD : public G4VSensitiveDetector
{
	
public:
    QweakSimTarget_DetectorSD(G4String name);
    virtual ~QweakSimTarget_DetectorSD() { };
	
    void   Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void   EndOfEvent(G4HCofThisEvent* HCE);
	
private:
	
    QweakSimTarget_DetectorHitsCollection*  Target_DetectorHitsCollection;
    G4int  Target_CollectionID;
	
};



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
