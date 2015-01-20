//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimBeamLineMessenger.cc
   $Revision: 1.2 $	
   $Date: 2011/10/19 12:44 $
   \author Peiqing Wang 

*/
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimBeamLineMessenger.hh"

// user includes
#include "QweakSimBeamLine.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimBeamLineMessenger::QweakSimBeamLineMessenger(QweakSimBeamLine* myTar)
:myBeamLine(myTar)
{ 
 // BeamLine related
  BeamLineDir = new G4UIdirectory("/BeamLine/");
  BeamLineDir -> SetGuidance("beamline control.");
       
  BeamLineZPosCmd =  new G4UIcmdWithADoubleAndUnit("/BeamLine/SetCenterPositionInZ",this);
  BeamLineZPosCmd->SetGuidance("Set the Z position of the target center"); 
  BeamLineZPosCmd->SetParameterName("Size",true);
  //TargZPosCmd->SetRange("Size>=0.");
  BeamLineZPosCmd->SetUnitCategory("Length");
  BeamLineZPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BeamLineMatCmd = new G4UIcmdWithAString("/BeamLine/SetBeamLineMaterial",this);
  BeamLineMatCmd->SetGuidance("Select Material of the BeamLine.");
  BeamLineMatCmd->SetParameterName("choice",false);
  BeamLineMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimBeamLineMessenger::~QweakSimBeamLineMessenger()
{
  delete BeamLineZPosCmd;
  delete BeamLineMatCmd;
  delete BeamLineDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimBeamLineMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimBeamLineMessenger::SetNewValue() " << newValue << G4endl;

  if( command == BeamLineZPosCmd )
   {
     G4cout << "#### Messenger: Setting BeamLine Z position to " << newValue << G4endl;

     myBeamLine->SetBeamLineCenterPositionInZ(BeamLineZPosCmd->GetNewDoubleValue(newValue));
   }

  if( command == BeamLineMatCmd )
  { 
      G4cout << "#### Messenger: Setting BeamLine Material to " << newValue << G4endl;
      
      myBeamLine->SetBeamLineMaterial(newValue);
  }


  G4cout << "#### Leaving QweakSimBeamLineMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

