//=============================================================================
//
//  File     QweakSimWShuttersMessenger.cc
//  Revision 1.0
//  Date     02/06/2012
//  Author   Kurtis Bartlett
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimWShuttersMessenger.hh"

//  user includes
#include "QweakSimWShutters.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

QweakSimWShuttersMessenger::QweakSimWShuttersMessenger(QweakSimWShutters* theWShutters,G4int n)
:myWShutters(theWShutters)
{
  //WShuttersDir = new G4UIdirectory("/WShutters/");

  G4String wshutters = "/WShutters" + G4UIcommand::ConvertToString(n);
  WShuttersDir = new  G4UIdirectory(G4String("/WShutters"+ wshutters + "/"));
  WShuttersDir -> SetGuidance("Tungsten Shutters control.");

  //--------------------------------------------------

  //WShutters_SetThicknessInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/WShutters/SetThicknessInZ",this);
  //WShutters_SetThicknessInZ_Cmd->SetGuidance("Set the thickness of the WShutters in the Z direction");
  //WShutters_SetThicknessInZ_Cmd->SetParameterName("Size",true);
  //WShutters_SetThicknessInZ_Cmd->SetUnitCategory("Length");
  //WShutters_SetThicknessInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //-------------------------------------------------

  WShutters_SetEnabled_Cmd = new G4UIcmdWithoutParameter(G4String("/WShutters" + wshutters + "/Enable"),this);
  WShutters_SetEnabled_Cmd->SetGuidance("Enables the WShutters");
  WShutters_SetEnabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //-------------------------------------------------

  WShutters_SetDisabled_Cmd = new G4UIcmdWithoutParameter(G4String("/WShutters" + wshutters + "/Disable"),this);
  WShutters_SetDisabled_Cmd->SetGuidance("Disables the WShutters");
  WShutters_SetDisabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}

QweakSimWShuttersMessenger::~QweakSimWShuttersMessenger()
{

  //if (WShutters_SetThicknessInZ_Cmd)  delete WShutters_SetThicknessInZ_Cmd;
  if (WShutters_SetEnabled_Cmd)       delete WShutters_SetEnabled_Cmd;
  if (WShutters_SetDisabled_Cmd)      delete WShutters_SetDisabled_Cmd;

  if (WShuttersDir)                   delete WShuttersDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimWShuttersMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  G4cout << "#### Messenger:  QweakSimWShuttersMessenger::SetNewValue() " << newValue << G4endl;

  //if ( command == WShutters_SetThicknessInZ_Cmd )
  //{
  //  G4cout << "#### Messenger: Setting WShutters Z thickness to " << newValue << G4endl;

  //  myWShutters->SetWShutters_LengthInZ(WShutters_SetThicknessInZ_Cmd->GetNewDoubleValue(newValue));
  //}

  //---------------------------------------------------------------

  if ( command == WShutters_SetEnabled_Cmd )
  {
    G4cout << "#### Messenger:  WShutters ENABLED" << G4endl;

    myWShutters->SetEnabled();
  }

    if ( command == WShutters_SetDisabled_Cmd )
  {
    G4cout << "#### Messenger:  WShutters DISABLED" << G4endl;

    myWShutters->SetDisabled();
  }

  //---------------------------------------------------------------
}

