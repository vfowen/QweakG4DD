/*

   \file QweakSimLumiMessenger.cc
   \author Wade Duvall

*/

#include "QweakSimLumiMessenger.hh"
#include "QweakSimLumiDetector.hh"
#include "QweakSimMessengerDefinition.hh"

QweakSimLumiMessenger::QweakSimLumiMessenger(QweakSimLumiDetector* theLumi):myLumi(theLumi) {
    /* Set directory for lumi control. */
    LumiDir = new G4UIdirectory("/Lumi/");
    LumiDir->SetGuidance("Lumi detector control");

    /* Change position of lumi. */
    USLumi_SetPositionInX_Cmd = new G4UIcmdWithADoubleAndUnit("/Lumi/SetUSPositionInX", this);
    USLumi_SetPositionInX_Cmd->SetGuidance("Set the X positiion of the USLumi");
    USLumi_SetPositionInX_Cmd->SetParameterName("Size", true);
    USLumi_SetPositionInX_Cmd->SetUnitCategory("Length");
    USLumi_SetPositionInX_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    USLumi_SetPositionInY_Cmd = new G4UIcmdWithADoubleAndUnit("/Lumi/SetUSPositionInY", this);
    USLumi_SetPositionInY_Cmd->SetGuidance("Set the Y positiion of the USLumi");
    USLumi_SetPositionInY_Cmd->SetParameterName("Size", true);
    USLumi_SetPositionInY_Cmd->SetUnitCategory("Length");
    USLumi_SetPositionInY_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    USLumi_SetPositionInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/Lumi/SetUSPositionInZ", this);
    USLumi_SetPositionInZ_Cmd->SetGuidance("Set the Z positiion of the USLumi");
    USLumi_SetPositionInZ_Cmd->SetParameterName("Size", true);
    USLumi_SetPositionInZ_Cmd->SetUnitCategory("Length");
    USLumi_SetPositionInZ_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    /* Enable Lumis. */
    USLumi_SetEnabled_Cmd = new G4UIcmdWithoutParameter("/Lumi/USEnable", this);
    USLumi_SetEnabled_Cmd->SetGuidance("Enables the USLumis");
    USLumi_SetEnabled_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    /* Disable Lumis. */
    USLumi_SetDisabled_Cmd = new G4UIcmdWithoutParameter("/Lumi/USDisable", this);
    USLumi_SetDisabled_Cmd->SetGuidance("Disables the USLumis");
    USLumi_SetDisabled_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

QweakSimLumiMessenger::~QweakSimLumiMessenger() {
    if(USLumi_SetPositionInX_Cmd) delete USLumi_SetPositionInX_Cmd;
    if(USLumi_SetPositionInY_Cmd) delete USLumi_SetPositionInY_Cmd;
    if(USLumi_SetPositionInZ_Cmd) delete USLumi_SetPositionInZ_Cmd;

    if(USLumi_SetEnabled_Cmd) delete USLumi_SetEnabled_Cmd;
    if(USLumi_SetDisabled_Cmd) delete USLumi_SetDisabled_Cmd;

    if(LumiDir) delete LumiDir;
}

void QweakSimLumiMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    G4cout << "=== Calling QweakSimLumiMessenger::SetNewValue() " << newValue << G4endl;

    if(command == USLumi_SetPositionInX_Cmd) {
        G4cout << "=== Messenger: Setting USLumi X position to " << newValue << G4endl;
        myLumi->SetUSLumi_PositionInX(USLumi_SetPositionInX_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == USLumi_SetPositionInY_Cmd) {
        G4cout << "=== Messenger: Setting USLumi Y position to " << newValue << G4endl;
        myLumi->SetUSLumi_PositionInY(USLumi_SetPositionInY_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == USLumi_SetPositionInZ_Cmd) {
        G4cout << "=== Messenger: Setting USLumi Z position to " << newValue << G4endl;
        myLumi->SetUSLumi_PositionInZ(USLumi_SetPositionInZ_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == USLumi_SetEnabled_Cmd) {
        G4cout << "=== Messenger: ENABLE the USLumi" << G4endl;
        myLumi->SetUSLumi_Enabled();
    }
    
    if(command == USLumi_SetDisabled_Cmd) {
        G4cout << "=== Messenger: DISABLE the USLumi" << G4endl;
        myLumi->SetUSLumi_Disabled();
    }
    
    G4cout << "=== Leaving QweakSimLumiMessenger::SetNewValue() " << newValue << G4endl;
}
