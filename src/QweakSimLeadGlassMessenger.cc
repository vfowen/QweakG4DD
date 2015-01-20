
// QweakSimLeadGlassMessenger.cc
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#include "QweakSimLeadGlassMessenger.hh"

//--- user includes
#include "QweakSimLeadGlass.hh"
#include "QweakSimMessengerDefinition.hh"



/////// --------------------------------------------------------------------

QweakSimLeadGlassMessenger::QweakSimLeadGlassMessenger(QweakSimLeadGlass* theLeadGlass)
:myLeadGlass(theLeadGlass)
{ 
	
    LeadGlassDir = new G4UIdirectory("/LeadGlass/");
    LeadGlassDir -> SetGuidance("Lead Glass Detector control.");
	
    //--- Material
	
    LeadGlass_SetMaterial_Cmd =  new G4UIcmdWithAString("/LeadGlass/SetMaterial",this);
    LeadGlass_SetMaterial_Cmd -> SetGuidance("Select Material of the LeadGlass.");
    LeadGlass_SetMaterial_Cmd -> SetParameterName("choice",false);
    LeadGlass_SetMaterial_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Position
	
    LeadGlass_SetCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetCenterPositionInX",this);
    LeadGlass_SetCenterPositionInX_Cmd -> SetGuidance("Set the X position of the LeadGlass"); 
    LeadGlass_SetCenterPositionInX_Cmd -> SetParameterName("Size",true);
    LeadGlass_SetCenterPositionInX_Cmd -> SetUnitCategory("Length");
    LeadGlass_SetCenterPositionInX_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    LeadGlass_SetCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetCenterPositionInY",this);
    LeadGlass_SetCenterPositionInY_Cmd -> SetGuidance("Set the Y position of the LeadGlass"); 
    LeadGlass_SetCenterPositionInY_Cmd -> SetParameterName("Size",true);
    LeadGlass_SetCenterPositionInY_Cmd -> SetUnitCategory("Length");
    LeadGlass_SetCenterPositionInY_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    LeadGlass_SetCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetCenterPositionInZ",this);
    LeadGlass_SetCenterPositionInZ_Cmd -> SetGuidance("Set the Z position of the LeadGlass"); 
    LeadGlass_SetCenterPositionInZ_Cmd -> SetParameterName("Size",true);
    LeadGlass_SetCenterPositionInZ_Cmd -> SetUnitCategory("Length");
    LeadGlass_SetCenterPositionInZ_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Rotation
	
    LeadGlass_SetTiltAngleInX_Cmd = new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetTiltAngleInX",this);
    LeadGlass_SetTiltAngleInX_Cmd -> SetGuidance("Set the X tilting angle of the LeadGlass"); 
    LeadGlass_SetTiltAngleInX_Cmd -> SetParameterName("Angle",true);
    LeadGlass_SetTiltAngleInX_Cmd -> SetDefaultUnit("degree");
    LeadGlass_SetTiltAngleInX_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    LeadGlass_SetTiltAngleInY_Cmd = new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetTiltAngleInY",this);
    LeadGlass_SetTiltAngleInY_Cmd -> SetGuidance("Set the Y tilting angle of the LeadGlass"); 
    LeadGlass_SetTiltAngleInY_Cmd -> SetParameterName("Angle",true);
    LeadGlass_SetTiltAngleInY_Cmd -> SetDefaultUnit("degree");
    LeadGlass_SetTiltAngleInY_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    LeadGlass_SetTiltAngleInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/LeadGlass/SetTiltAngleInZ",this);
    LeadGlass_SetTiltAngleInZ_Cmd -> SetGuidance("Set the Z tilting angle of the LeadGlass"); 
    LeadGlass_SetTiltAngleInZ_Cmd -> SetParameterName("Angle",true);
    LeadGlass_SetTiltAngleInZ_Cmd -> SetDefaultUnit("degree");
    LeadGlass_SetTiltAngleInZ_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Enable
	
    LeadGlass_SetEnabled_Cmd =  new G4UIcmdWithoutParameter("/LeadGlass/Enable",this);
    LeadGlass_SetEnabled_Cmd -> SetGuidance("Enables the LeadGlass");
    LeadGlass_SetEnabled_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Disable
	
    LeadGlass_SetDisabled_Cmd =  new G4UIcmdWithoutParameter("/LeadGlass/Disable",this);
    LeadGlass_SetDisabled_Cmd -> SetGuidance("Disables the LeadGlass");
    LeadGlass_SetDisabled_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
}



/////// --------------------------------------------------------------------

QweakSimLeadGlassMessenger::~QweakSimLeadGlassMessenger()
{
    if (LeadGlass_SetMaterial_Cmd)             delete LeadGlass_SetMaterial_Cmd;
	
    if (LeadGlass_SetCenterPositionInX_Cmd)    delete LeadGlass_SetCenterPositionInX_Cmd;
    if (LeadGlass_SetCenterPositionInY_Cmd)    delete LeadGlass_SetCenterPositionInY_Cmd;
    if (LeadGlass_SetCenterPositionInZ_Cmd)    delete LeadGlass_SetCenterPositionInZ_Cmd;
	
    if (LeadGlass_SetEnabled_Cmd)              delete LeadGlass_SetEnabled_Cmd;
    if (LeadGlass_SetDisabled_Cmd)             delete LeadGlass_SetDisabled_Cmd;
	
    if (LeadGlassDir)                          delete LeadGlassDir;

}



/////// --------------------------------------------------------------------

void QweakSimLeadGlassMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    G4cout << "=== Calling QweakSimLeadGlassMessenger::SetNewValue() " << newValue << G4endl;
	
    //--- Set New Material
	
    if (command == LeadGlass_SetMaterial_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass Material to " << newValue << G4endl;	
        myLeadGlass -> SetLeadGlass_Material(newValue);
    }
	
    //--- Set New Position
	
    if (command == LeadGlass_SetCenterPositionInX_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass X position to " << newValue << G4endl;	
        myLeadGlass -> SetLeadGlass_CenterPositionInX(LeadGlass_SetCenterPositionInX_Cmd -> GetNewDoubleValue(newValue));
    }
	
	if (command == LeadGlass_SetCenterPositionInY_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass Y position to " << newValue << G4endl;	
        myLeadGlass -> SetLeadGlass_CenterPositionInY(LeadGlass_SetCenterPositionInY_Cmd -> GetNewDoubleValue(newValue));
    }
	
	if (command == LeadGlass_SetCenterPositionInZ_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass Z position to " << newValue << G4endl;	
        myLeadGlass -> SetLeadGlass_CenterPositionInZ(LeadGlass_SetCenterPositionInZ_Cmd -> GetNewDoubleValue(newValue));
    }
	
    //--- Set New Tilting Anngle
	
    if (command == LeadGlass_SetTiltAngleInX_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass X tilting angle to " << newValue << G4endl;
        myLeadGlass -> SetLeadGlass_TiltAngleInX(LeadGlass_SetTiltAngleInX_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == LeadGlass_SetTiltAngleInY_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass Y tilting angle to " << newValue << G4endl;
        myLeadGlass -> SetLeadGlass_TiltAngleInY(LeadGlass_SetTiltAngleInY_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == LeadGlass_SetTiltAngleInZ_Cmd)
    {
        G4cout << "=== Messenger: Setting LeadGlass Z tilting angle to " << newValue << G4endl;
        myLeadGlass -> SetLeadGlass_TiltAngleInZ(LeadGlass_SetTiltAngleInZ_Cmd -> GetNewDoubleValue(newValue));
    }
	
    //--- Enable
	
    if (command == LeadGlass_SetEnabled_Cmd)
    {
        G4cout << "=== Messenger: ENABLE the LeadGlass" << G4endl;
        myLeadGlass -> SetLeadGlass_Enabled();
    }
	
    //----Disable
	
	if (command == LeadGlass_SetDisabled_Cmd)
    {
        G4cout << "=== Messenger: DISABLE the LeadGlass" << G4endl;
        myLeadGlass -> SetLeadGlass_Disabled();
    }  
	
    G4cout << "=== Leaving QweakSimLeadGlassMessenger::SetNewValue() " << newValue << G4endl;
}



/////// --------------------------------------------------------------------

