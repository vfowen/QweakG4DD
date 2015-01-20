//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTrackingActionMessenger.cc

   $Revision: 1.1 $	
   $Date: 2006/01/06 04:46:45 $

   \author Klaus Hans Grimm   
   \author Peiqing Wang

*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTrackingActionMessenger.hh"

// user includes
#include "QweakSimTrackingAction.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTrackingActionMessenger::QweakSimTrackingActionMessenger(QweakSimTrackingAction* myTA)
:myTrackingAction(myTA)
{ 
 // TrackingAction related
  TrackingActionDir = new G4UIdirectory("/TrackingAction/");
  TrackingActionDir -> SetGuidance("TrackingAction control.");

  TrackingFlag_Cmd =  new G4UIcmdWithAnInteger("/TrackingAction/TrackingFlag",this);
  TrackingFlag_Cmd->SetGuidance("Select tracking flag"); 
  TrackingFlag_Cmd->SetGuidance(" 0 : Track primary electrons only");
  TrackingFlag_Cmd->SetGuidance(" 1 : Track primary electrons and optical photons only"); 
  TrackingFlag_Cmd->SetGuidance(" 2 : Track all particles except optical photons");
  TrackingFlag_Cmd->SetGuidance(" 3 : Track all particles"); 
  TrackingFlag_Cmd->SetParameterName("Store",true);
  TrackingFlag_Cmd->SetDefaultValue(0);
  TrackingFlag_Cmd->SetRange("Store >=0 && Store <= 3");
  TrackingFlag_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTrackingActionMessenger::~QweakSimTrackingActionMessenger()
{
  delete TrackingFlag_Cmd;
  delete TrackingActionDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTrackingActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimTrackingActionMessenger::SetNewValue() " << newValue << G4endl;

  if( command == TrackingFlag_Cmd )
   {
     G4cout << "#### Messenger: Setting Tracking Flag to " << newValue << G4endl;

     myTrackingAction->SetTrackingFlag(TrackingFlag_Cmd->GetNewIntValue(newValue));
   }

  G4cout << "#### Leaving QweakSimTrackingActionMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

