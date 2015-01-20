
#ifndef QweakSimStackingAction_H
#define QweakSimStackingAction_H 1

// geant4 includes
#include "G4UserStackingAction.hh"

class QweakSimStackingAction : public G4UserStackingAction
{
public:
  QweakSimStackingAction() { };
  virtual ~QweakSimStackingAction() { };
  
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage() { };
  virtual void PrepareNewEvent() { };

private:
};

#endif
