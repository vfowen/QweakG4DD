//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimEventActionMessenger.cc

   $Revision: 1.0 $
   $Date: 2009/10/17 20:02:16 $

   \author Wouter Deconinck

*/
//=============================================================================

#include "QweakSimEventActionMessenger.hh"

// user include
#include "QweakSimEventAction.hh"
#include "QweakSimMessengerDefinition.hh"

// ----------------------------------------------------------------------------

QweakSimEventActionMessenger::QweakSimEventActionMessenger(QweakSimEventAction* anEventAction)
  : theEventAction(anEventAction)
{
  G4cout << G4endl << "###### Calling QweakSimEventActionMessenger::QweakSimEventActionMessenger() " << G4endl << G4endl;

  theTriggerDir = new G4UIdirectory( "/Trigger/" );
  theTriggerDir->SetGuidance("Software trigger.");

  theTriggerShowCommand = new G4UIcmdWithoutParameter("/Trigger/Show", this);
  theTriggerShowCommand->SetGuidance("List trigger conditions.");
  theTriggerShowCommand->AvailableForStates(G4State_PreInit,G4State_Idle);

  theTriggerEnableCommand = new G4UIcmdWithAString("/Trigger/Enable", this);
  theTriggerEnableCommand->SetParameterName("trigger condition", false);
  theTriggerEnableCommand->SetDefaultValue("3fold");
  theTriggerEnableCommand->SetGuidance("Enable trigger condition.");
  theTriggerEnableCommand->AvailableForStates(G4State_Idle);

  theTriggerDisableCommand = new G4UIcmdWithAString("/Trigger/Disable", this);
  theTriggerDisableCommand->SetParameterName("trigger condition", false);
  theTriggerDisableCommand->SetDefaultValue("3fold");
  theTriggerDisableCommand->SetGuidance("Disable trigger condition.");
  theTriggerDisableCommand->AvailableForStates(G4State_Idle);

  thePrintHitsCommand = new G4UIcmdWithABool("/Trigger/PrintHits", this);
  thePrintHitsCommand->SetParameterName("printhits",true);
  thePrintHitsCommand->SetDefaultValue("true");
  thePrintHitsCommand->AvailableForStates(G4State_Init,G4State_Idle);

  G4cout << G4endl << "###### Leaving QweakSimEventActionMessenger::QweakSimEventActionMessenger() " << G4endl << G4endl;
}

// ----------------------------------------------------------------------------

QweakSimEventActionMessenger::~QweakSimEventActionMessenger()
{
  G4cout << G4endl << "###### Calling QweakSimEventActionMessenger::~QweakSimEventActionMessenger() " << G4endl << G4endl;

  if (theTriggerShowCommand)    delete theTriggerShowCommand;
  if (theTriggerEnableCommand)  delete theTriggerEnableCommand;
  if (theTriggerDisableCommand) delete theTriggerDisableCommand;
  if (thePrintHitsCommand)      delete thePrintHitsCommand;
  if (theTriggerDir)            delete theTriggerDir;

  G4cout << G4endl << "###### Leaving QweakSimEventActionMessenger::~QweakSimEventActionMessenger() " << G4endl << G4endl;
}

// ----------------------------------------------------------------------------

void QweakSimEventActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if ( command == theTriggerShowCommand )
  {
    theEventAction->ShowTrigger();
  }
  if ( command == theTriggerEnableCommand )
  {
    theEventAction->EnableTrigger(newValue);
  }
  if ( command == theTriggerDisableCommand )
  {
    theEventAction->DisableTrigger(newValue);
  }
  if ( command == thePrintHitsCommand )
  {
    theEventAction->SetPrintHits(thePrintHitsCommand->GetNewBoolValue(newValue));
  }
}
