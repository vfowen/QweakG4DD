//=============================================================================
//
//  File     QweakSimPionWallMessenger.cc
//  Revision 1.0
//  Date     07/23/2012
//  Author   James Dowd
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimPionWallMessenger.hh"

//  user includes
#include "QweakSimPionWall.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

QweakSimPionWallMessenger::QweakSimPionWallMessenger(QweakSimPionWall* thePionWall)
:myPionWall(thePionWall)
{
  PionWallDir = new G4UIdirectory("/PionWall/");
  PionWallDir -> SetGuidance("Pion Wall control.");
  
  //--------------------------------------------------
  
  PionWall_SetThicknessInX_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetThicknessInX",this);
  PionWall_SetThicknessInX_Cmd->SetGuidance("Set the thickness of the Pion Wall in the X direction");
  PionWall_SetThicknessInX_Cmd->SetParameterName("Size",true);
  PionWall_SetThicknessInX_Cmd->SetUnitCategory("Length");
  PionWall_SetThicknessInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //--------------------------------------------------
  
  PionWall_SetThicknessInY_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetThicknessInY",this);
  PionWall_SetThicknessInY_Cmd->SetGuidance("Set the thickness of the Pion Wall in the Y direction");
  PionWall_SetThicknessInY_Cmd->SetParameterName("Size",true);
  PionWall_SetThicknessInY_Cmd->SetUnitCategory("Length");
  PionWall_SetThicknessInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //--------------------------------------------------
  
  PionWall_SetThicknessInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetThicknessInZ",this);
  PionWall_SetThicknessInZ_Cmd->SetGuidance("Set the thickness of the Pion Wall in the Z direction");
  PionWall_SetThicknessInZ_Cmd->SetParameterName("Size",true);
  PionWall_SetThicknessInZ_Cmd->SetUnitCategory("Length");
  PionWall_SetThicknessInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------

  PionWall_SetOffsetX_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetPositionOffsetX",this);
  PionWall_SetOffsetX_Cmd->SetGuidance("Set the position offset of the Pion Wall in the X direction");
  PionWall_SetOffsetX_Cmd->SetParameterName("Size",true);
  PionWall_SetOffsetX_Cmd->SetUnitCategory("Length");
  PionWall_SetOffsetX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------

  PionWall_SetOffsetY_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetPositionOffsetY",this);
  PionWall_SetOffsetY_Cmd->SetGuidance("Set the position offset of the Pion Wall in the Y direction");
  PionWall_SetOffsetY_Cmd->SetParameterName("Size",true);
  PionWall_SetOffsetY_Cmd->SetUnitCategory("Length");
  PionWall_SetOffsetY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------

  PionWall_SetOffsetZ_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetPositionOffsetZ",this);
  PionWall_SetOffsetZ_Cmd->SetGuidance("Set the position offset of the Pion Wall in the Z direction");
  PionWall_SetOffsetZ_Cmd->SetParameterName("Size",true);
  PionWall_SetOffsetZ_Cmd->SetUnitCategory("Length");
  PionWall_SetOffsetZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------
  
  PionWall_SetEnabled_Cmd = new G4UIcmdWithoutParameter("/PionWall/Enable",this);
  PionWall_SetEnabled_Cmd->SetGuidance("Enables the Pion Wall");
  PionWall_SetEnabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------
  
  PionWall_SetDisabled_Cmd = new G4UIcmdWithoutParameter("/PionWall/Disable",this);
  PionWall_SetDisabled_Cmd->SetGuidance("Disables the Pion Wall");
  PionWall_SetDisabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  
}

QweakSimPionWallMessenger::~QweakSimPionWallMessenger()
{

  if (PionWall_SetThicknessInX_Cmd)  delete PionWall_SetThicknessInX_Cmd;
  if (PionWall_SetThicknessInY_Cmd)  delete PionWall_SetThicknessInY_Cmd;
  if (PionWall_SetThicknessInZ_Cmd)  delete PionWall_SetThicknessInZ_Cmd;
  if (PionWall_SetOffsetX_Cmd)       delete PionWall_SetOffsetX_Cmd;
  if (PionWall_SetOffsetY_Cmd)       delete PionWall_SetOffsetY_Cmd;
  if (PionWall_SetOffsetZ_Cmd)       delete PionWall_SetOffsetZ_Cmd;
  if (PionWall_SetEnabled_Cmd)       delete PionWall_SetEnabled_Cmd;
  if (PionWall_SetDisabled_Cmd)      delete PionWall_SetDisabled_Cmd;
  
  if (PionWallDir)                   delete PionWallDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimPionWallMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  G4cout << "#### Messenger:  QweakSimPionWallMessenger::SetNewValue() " << newValue << G4endl;

  if ( command == PionWall_SetThicknessInX_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall X thickness to " << newValue << G4endl;
    
    myPionWall->SetPionWall_LengthInX(PionWall_SetThicknessInX_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetThicknessInY_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall Y thickness to " << newValue << G4endl;
    
    myPionWall->SetPionWall_LengthInY(PionWall_SetThicknessInY_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetThicknessInZ_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall Z thickness to " << newValue << G4endl;
    
    myPionWall->SetPionWall_LengthInZ(PionWall_SetThicknessInZ_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetOffsetX_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall X Position Offset to " << newValue << G4endl;
    
    myPionWall->SetPionWall_Position_Offset_X(PionWall_SetOffsetX_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetOffsetY_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall Y Position Offset to " << newValue << G4endl;
    
    myPionWall->SetPionWall_Position_Offset_Y(PionWall_SetOffsetY_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetOffsetZ_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall Z Position Offset to " << newValue << G4endl;
    
    myPionWall->SetPionWall_Position_Offset_Z(PionWall_SetOffsetZ_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetEnabled_Cmd )
  {
    G4cout << "#### Messenger:  Pion Wall ENABLED" << G4endl;

    myPionWall->SetEnabled();
  }

    if ( command == PionWall_SetDisabled_Cmd )
  {
    G4cout << "#### Messenger:  Pion Wall DISABLED" << G4endl;

    myPionWall->SetDisabled();
  }

  //---------------------------------------------------------------
}

