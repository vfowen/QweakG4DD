
// QweakSimPMTOnly_PMTSD.hh
// Martin McHugh
// 2013-08-01


#ifndef QweakSimPMTOnly_PMTSD_h
#define QweakSimPMTOnly_PMTSD_h 

//--- user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimPMTOnly_PMTHit.hh"
#include "QweakSimTrajectory.hh"
/////// --------------------------------------------------------------------

//--- user classes
class QweakSimUserInformation;

/////// --------------------------------------------------------------------
class QweakSimPMTOnly_PMTSD : public G4VSensitiveDetector
{
	
  public:
    QweakSimPMTOnly_PMTSD(G4String name, QweakSimUserInformation *userInfo);
    ~QweakSimPMTOnly_PMTSD();
	
    void Initialize(G4HCofThisEvent* HCE);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
    
    //A version of processHits that keeps aStep constant
    G4bool ProcessHits_constStep(const G4Step*, G4TouchableHistory* );
    
    void EndOfEvent(G4HCofThisEvent* HCE);
    QweakSimTrajectory* GetParentTrajectory(G4int parentID);
    	
  private:

    QweakSimUserInformation* myUserInfo; 
    QweakSimPMTOnly_PMTHitsCollection*  PMTOnly_PMTHitsCollection;
    G4int PMTOnlyPMT_CollectionID;
	
};


/////// --------------------------------------------------------------------

#endif

