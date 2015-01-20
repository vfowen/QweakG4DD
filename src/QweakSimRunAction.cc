//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimRunAction.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:14:28 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimRunAction.hh"

// geant4 includes
#include "G4ios.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"

// user includes
#include "QweakSimAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimRunAction::QweakSimRunAction(QweakSimAnalysis* AN)
: runID(0), analysis(AN)
{
  G4cout << G4endl << "###### Calling/Leaving QweakSimRunAction::QweakSimRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimRunAction::~QweakSimRunAction()
{
  G4cout << G4endl << "###### Calling/Leaving QweakSimRunAction::~QweakSimRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << G4endl << "###### Calling QweakSimRunAction::BeginOfRunAction()" << G4endl << G4endl;

  // Get run number
  runID = aRun->GetRunID();

  // Print run number
  G4cout << "### Start of Run " << runID << G4endl;

  // Start analysis at begin of run
  analysis->BeginOfRun(aRun);
  analysis->SetNumberOfEventToBeProcessed(aRun->GetNumberOfEventToBeProcessed());

  // Visualization
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    }

  G4cout << G4endl << "###### Leaving QweakSimRunAction::BeginOfRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimRunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << G4endl << "###### Calling QweakSimRunAction::EndOfRunAction()" << G4endl << G4endl;

  // Get run number (
  if (runID != aRun->GetRunID())
    {
      G4cout << "### Run number has changed from " << runID << " to " << aRun->GetRunID() << "." << G4endl;
    }

  // Print run number
  G4cout << "### End of Run " << runID << G4endl;

  // End analysis procedure at end of run
  analysis->EndOfRun(aRun);

  // Visualization
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/viewer/update");
    }

  G4cout << G4endl << "###### Leaving QweakSimRunAction::EndOfRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int QweakSimRunAction::getRunID()
{
  return runID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


