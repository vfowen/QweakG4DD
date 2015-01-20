
// QweakSimPMTOnlyMessenger.cc
// Marty McHugh
// 2013-06-11

/////// --------------------------------------------------------------------

#include "QweakSimPMTOnlyMessenger.hh"

//--- user includes
#include "QweakSimPMTOnly.hh"
#include "QweakSimMessengerDefinition.hh"



/////// --------------------------------------------------------------------

QweakSimPMTOnlyMessenger::QweakSimPMTOnlyMessenger(QweakSimPMTOnly* thePMTOnly)
:myPMTOnly(thePMTOnly)
{ 
	
    PMTOnlyDir = new G4UIdirectory("/PMTOnly/");
    PMTOnlyDir -> SetGuidance("Lead Glass Detector control.");
	
    //--- Material
	
    PMTOnly_SetMaterial_Cmd =  new G4UIcmdWithAString("/PMTOnly/SetMaterial",this);
    PMTOnly_SetMaterial_Cmd -> SetGuidance("Select Material of the PMTOnly.");
    PMTOnly_SetMaterial_Cmd -> SetParameterName("choice",false);
    PMTOnly_SetMaterial_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Position
    //--- Set	
    PMTOnly_SetCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetCenterPositionInX",this);
    PMTOnly_SetCenterPositionInX_Cmd -> SetGuidance("Set the X position of the PMTOnly"); 
    PMTOnly_SetCenterPositionInX_Cmd -> SetParameterName("Size",true);
    PMTOnly_SetCenterPositionInX_Cmd -> SetUnitCategory("Length");
    PMTOnly_SetCenterPositionInX_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    PMTOnly_SetCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetCenterPositionInY",this);
    PMTOnly_SetCenterPositionInY_Cmd -> SetGuidance("Set the Y position of the PMTOnly"); 
    PMTOnly_SetCenterPositionInY_Cmd -> SetParameterName("Size",true);
    PMTOnly_SetCenterPositionInY_Cmd -> SetUnitCategory("Length");
    PMTOnly_SetCenterPositionInY_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    PMTOnly_SetCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetCenterPositionInZ",this);
    PMTOnly_SetCenterPositionInZ_Cmd -> SetGuidance("Set the Z position of the PMTOnly"); 
    PMTOnly_SetCenterPositionInZ_Cmd -> SetParameterName("Size",true);
    PMTOnly_SetCenterPositionInZ_Cmd -> SetUnitCategory("Length");
    PMTOnly_SetCenterPositionInZ_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);

    //--- Get
    PMTOnly_FindMotherCenter_Cmd =  new G4UIcmdWithoutParameter("/PMTOnly/FindMotherCenter", this);
    PMTOnly_FindMotherCenter_Cmd -> SetGuidance("Find Center of PMTOnly Volumes");
    PMTOnly_FindMotherCenter_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);

    //--- Rotation
	
    PMTOnly_SetTiltAngleInX_Cmd = new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetTiltAngleInX",this);
    PMTOnly_SetTiltAngleInX_Cmd -> SetGuidance("Set the X tilting angle of the PMTOnly"); 
    PMTOnly_SetTiltAngleInX_Cmd -> SetParameterName("Angle",true);
    PMTOnly_SetTiltAngleInX_Cmd -> SetDefaultUnit("degree");
    PMTOnly_SetTiltAngleInX_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    PMTOnly_SetTiltAngleInY_Cmd = new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetTiltAngleInY",this);
    PMTOnly_SetTiltAngleInY_Cmd -> SetGuidance("Set the Y tilting angle of the PMTOnly"); 
    PMTOnly_SetTiltAngleInY_Cmd -> SetParameterName("Angle",true);
    PMTOnly_SetTiltAngleInY_Cmd -> SetDefaultUnit("degree");
    PMTOnly_SetTiltAngleInY_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    PMTOnly_SetTiltAngleInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/PMTOnly/SetTiltAngleInZ",this);
    PMTOnly_SetTiltAngleInZ_Cmd -> SetGuidance("Set the Z tilting angle of the PMTOnly"); 
    PMTOnly_SetTiltAngleInZ_Cmd -> SetParameterName("Angle",true);
    PMTOnly_SetTiltAngleInZ_Cmd -> SetDefaultUnit("degree");
    PMTOnly_SetTiltAngleInZ_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Enable
	
    PMTOnly_SetEnabled_Cmd =  new G4UIcmdWithoutParameter("/PMTOnly/Enable",this);
    PMTOnly_SetEnabled_Cmd -> SetGuidance("Enables the PMTOnly");
    PMTOnly_SetEnabled_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
    //--- Disable
	
    PMTOnly_SetDisabled_Cmd =  new G4UIcmdWithoutParameter("/PMTOnly/Disable",this);
    PMTOnly_SetDisabled_Cmd -> SetGuidance("Disables the PMTOnly");
    PMTOnly_SetDisabled_Cmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
}



/////// --------------------------------------------------------------------

QweakSimPMTOnlyMessenger::~QweakSimPMTOnlyMessenger()
{
    if (PMTOnly_SetMaterial_Cmd)             delete PMTOnly_SetMaterial_Cmd;
	
    if (PMTOnly_SetCenterPositionInX_Cmd)    delete PMTOnly_SetCenterPositionInX_Cmd;
    if (PMTOnly_SetCenterPositionInY_Cmd)    delete PMTOnly_SetCenterPositionInY_Cmd;
    if (PMTOnly_SetCenterPositionInZ_Cmd)    delete PMTOnly_SetCenterPositionInZ_Cmd;

    if (PMTOnly_FindMotherCenter_Cmd) 	     delete PMTOnly_FindMotherCenter_Cmd;
	
    if (PMTOnly_SetEnabled_Cmd)              delete PMTOnly_SetEnabled_Cmd;
    if (PMTOnly_SetDisabled_Cmd)             delete PMTOnly_SetDisabled_Cmd;
	
    if (PMTOnlyDir)                          delete PMTOnlyDir;

}



/////// --------------------------------------------------------------------

void QweakSimPMTOnlyMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    G4cout << "=== Calling QweakSimPMTOnlyMessenger::SetNewValue() " << newValue << G4endl;
	
    //--- Set New Material
	
    if (command == PMTOnly_SetMaterial_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly Material to " << newValue << G4endl;	
        myPMTOnly -> SetPMTOnly_Material(newValue);
    }
	
    //--- Set New Position
	
    if (command == PMTOnly_SetCenterPositionInX_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly X position to " << newValue << G4endl;	
        myPMTOnly -> SetPMTOnly_CenterPositionInX(PMTOnly_SetCenterPositionInX_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == PMTOnly_SetCenterPositionInY_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly Y position to " << newValue << G4endl;	
        myPMTOnly -> SetPMTOnly_CenterPositionInY(PMTOnly_SetCenterPositionInY_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == PMTOnly_SetCenterPositionInZ_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly Z position to " << newValue << G4endl;	
        myPMTOnly -> SetPMTOnly_CenterPositionInZ(PMTOnly_SetCenterPositionInZ_Cmd -> GetNewDoubleValue(newValue));
    }
	
	
    //--- Find New Position
    if (command == PMTOnly_FindMotherCenter_Cmd) 
    {
        G4cout << "=== Messenger: Finding PMTOnly Center position" << G4endl;	
        myPMTOnly -> FindPMTOnly_MotherCenter();
    }

    //--- Set New Tilting Anngle
	
    if (command == PMTOnly_SetTiltAngleInX_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly X tilting angle to " << newValue << G4endl;
        myPMTOnly -> SetPMTOnly_TiltAngleInX(PMTOnly_SetTiltAngleInX_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == PMTOnly_SetTiltAngleInY_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly Y tilting angle to " << newValue << G4endl;
        myPMTOnly -> SetPMTOnly_TiltAngleInY(PMTOnly_SetTiltAngleInY_Cmd -> GetNewDoubleValue(newValue));
    }
	
    if (command == PMTOnly_SetTiltAngleInZ_Cmd)
    {
        G4cout << "=== Messenger: Setting PMTOnly Z tilting angle to " << newValue << G4endl;
        myPMTOnly -> SetPMTOnly_TiltAngleInZ(PMTOnly_SetTiltAngleInZ_Cmd -> GetNewDoubleValue(newValue));
    }
	
    //--- Enable
	
    if (command == PMTOnly_SetEnabled_Cmd)
    {
        G4cout << "=== Messenger: ENABLE the PMTOnly" << G4endl;
        myPMTOnly -> SetPMTOnly_Enabled();
    }
	
    //----Disable
	
    if (command == PMTOnly_SetDisabled_Cmd)
    {
        G4cout << "=== Messenger: DISABLE the PMTOnly" << G4endl;
        myPMTOnly -> SetPMTOnly_Disabled();
    }  
	
    G4cout << "=== Leaving QweakSimPMTOnlyMessenger::SetNewValue() " << newValue << G4endl;
}



/////// --------------------------------------------------------------------

