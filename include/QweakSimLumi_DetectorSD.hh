#ifndef QweakSimLumi_DetectorSD_h
#define QweakSimLumi_DetectorSD_h 1

#include "QweakSimLumi_DetectorHit.hh"
#include "QweakSimSensitiveDetectorDeclaration.hh"

class QweakSimLumi_DetectorSD : public G4VSensitiveDetector {
    public:
        QweakSimLumi_DetectorSD(G4String name);
        ~QweakSimLumi_DetectorSD();

        void Initialize(G4HCofThisEvent* HCE);
        G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
        void EndOfEvent(G4HCofThisEvent* HCE);

    private:
        QweakSimLumi_DetectorHitsCollection* Lumi_DetectorHitsCollection;
        G4int Lumi_CollectionID;
};

#endif
