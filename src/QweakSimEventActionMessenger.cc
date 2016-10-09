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

  physProcCmd = new G4UIcmdWithAnInteger("/PhysicsProcesses/settingFlag",this);
  physProcCmd->SetGuidance("int with the form: a*2^0+b*2^1");
  physProcCmd->SetGuidance("   if you want to debugPrint a=1");
  physProcCmd->SetGuidance("   if you want to modify trajectory b=1");
  physProcCmd->SetParameterName("settingFlag", false);

  physProcAnCmd = new G4UIcmdWithAnInteger("/PhysicsProcesses/setAN",this);
  physProcAnCmd->SetGuidance("val<0 use twoPhoton AN * abs(val)");
  physProcAnCmd->SetGuidance("val>0 use Mott AN * abs(val)");
  physProcAnCmd->SetGuidance("val=0 use Mott+2photon");
  physProcAnCmd->SetParameterName("setAN", false);

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
  if (physProcCmd)              delete physProcCmd;
  if (physProcAnCmd)            delete physProcAnCmd;
  
  G4cout << G4endl << "###### Leaving QweakSimEventActionMessenger::~QweakSimEventActionMessenger() " << G4endl << G4endl;
}

// ----------------------------------------------------------------------------

void QweakSimEventActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if ( command == theTriggerShowCommand )
  {
    theEventAction->ShowTrigger();
  }else if ( command == theTriggerEnableCommand )
  {
    theEventAction->EnableTrigger(newValue);
  }else if ( command == theTriggerDisableCommand )
  {
    theEventAction->DisableTrigger(newValue);
  }else if ( command == thePrintHitsCommand )
  {
    theEventAction->SetPrintHits(thePrintHitsCommand->GetNewBoolValue(newValue));  
  }else if( command == physProcCmd ){
    G4int flag=physProcCmd->GetNewIntValue(newValue);
    theEventAction->SetPhysicsProcFlag(flag);

    G4cout<<G4endl<<G4endl<<__LINE__<<"\t"<<__PRETTY_FUNCTION__<<G4endl;
    if( (flag & 0x1)==0x1 )
      G4cout<<"\tGet ready for some huge output!!! debugPrint is on!"<<G4endl;
    else
      G4cout<<"\tNo debugPrint!"<<G4endl;
    if( (flag & 0x2)==0x2 )
      G4cout<<"\tWill modify trajectory"<<G4endl;
    else
      G4cout<<"\tWon't modify trajectory"<<G4endl;
    G4cout<<G4endl<<G4endl;
  }else if( command == physProcAnCmd ){
    G4int val = physProcAnCmd->GetNewIntValue(newValue);
    G4cout<<G4endl<<G4endl<<__LINE__<<"\t"<<__PRETTY_FUNCTION__<<G4endl;
    G4cout<<"setting AN flag to "<<val<<G4endl<<G4endl;
    theEventAction->SetAnFlag(val);
  }else{
    G4cerr<<__LINE__<<"\t"<<__PRETTY_FUNCTION__<<G4endl
	  <<command<<" has no definition"<<G4endl;
  }
}
