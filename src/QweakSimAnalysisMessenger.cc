/*
 * QweakSimAnalysisMessenger.cc
 *
 *  Created on: May 19, 2011
 *      Author: wdconinc
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimAnalysisMessenger.hh"

// user includes
#include "QweakSimAnalysis.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimAnalysisMessenger::QweakSimAnalysisMessenger(QweakSimAnalysis* analysis)
: pAnalysis(analysis)
{
  G4cout << "###### Calling QweakSimAnalysisMessenger::QweakSimAnalysisMessenger() " << G4endl;

  fAnalysisDir = new G4UIdirectory("/Analysis/");
  fAnalysisDir->SetGuidance("Analysis control");

  fRootFileStemCmd = new G4UIcmdWithAString("/Analysis/RootFileStem",this);
  fRootFileStemCmd->SetGuidance("Set stem of file with output ROOT tree");
  fRootFileStemCmd->SetParameterName("RootFileStem",false);
  fRootFileStemCmd->SetDefaultValue("QwSim");
  fRootFileStemCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fRootFileNameCmd = new G4UIcmdWithAString("/Analysis/RootFileName",this);
  fRootFileNameCmd->SetGuidance("Set file name of output ROOT tree");
  fRootFileNameCmd->SetParameterName("RootFileName",false);
  fRootFileNameCmd->SetDefaultValue("QwSim.root");
  fRootFileNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  G4cout << "###### Leaving QweakSimAnalysisMessenger::QweakSimAnalysisMessenger() " << G4endl;
}

QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger()
{
  G4cout << "###### Calling QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger() " << G4endl;

  if (fRootFileStemCmd) delete fRootFileStemCmd;
  if (fRootFileNameCmd) delete fRootFileNameCmd;
  if (fAnalysisDir)     delete fAnalysisDir;

  G4cout << "###### Leaving QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger() " << G4endl;
}

void QweakSimAnalysisMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fRootFileStemCmd)
    {
      G4cout << "#### Messenger: Setting Analysis ROOT file stem to " << newValue << G4endl;
      pAnalysis->SetRootFileStem(newValue);
    }
  if (command == fRootFileNameCmd)
    {
      G4cout << "#### Messenger: Setting Analysis ROOT file name to " << newValue << G4endl;
      pAnalysis->SetRootFileName(newValue);
    }
}
