//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimShieldingWallMessenger.cc

   $Revision: 1.4 $	
   $Date: 2006/04/26 20:03:31 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/04/26 20:03:31 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimShieldingWallMessenger.hh"

// user includes
#include "QweakSimShieldingWall.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimShieldingWallMessenger::QweakSimShieldingWallMessenger(QweakSimShieldingWall* theShieldingWall)
:myShieldingWall(theShieldingWall)
{ 
 // ShieldingWall related
  DetectorHutDir = new G4UIdirectory("/DetectorHut/");
  DetectorHutDir -> SetGuidance("Detector Hut Control.");

  VisibilityDir = new G4UIdirectory("/DetectorHut/Visibility/");
  VisibilityDir -> SetGuidance("Detector Hut Visibility Control.");

  CollimatorWallDir = new G4UIdirectory("/DetectorHut/CollimatorWall/");
  CollimatorWallDir -> SetGuidance("Collimator Wall Control.");
       
  CollimatorWallZPosCmd =  new G4UIcmdWithADoubleAndUnit("/DetectorHut/CollimatorWall/SetCenterPositionInZ",this);
  CollimatorWallZPosCmd->SetGuidance("Set the Z position of the Collimator Wall center"); 
  CollimatorWallZPosCmd->SetParameterName("Size",true);
  CollimatorWallZPosCmd->SetUnitCategory("Length");
  CollimatorWallZPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  CollimatorWallMatCmd = new G4UIcmdWithAString("/DetectorHut/CollimatorWall/SetCollimatorWallMaterial",this);
  CollimatorWallMatCmd->SetGuidance("Select Material of the CollimatorWall.");
  CollimatorWallMatCmd->SetParameterName("choice",false);
  CollimatorWallMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ShowCollimatorWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowCollimatorWall",this);
  ShowCollimatorWall_Cmd->SetGuidance("Make the Shielding Wall visible");
  ShowCollimatorWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideCollimatorWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideCollimatorWall",this);
  HideCollimatorWall_Cmd->SetGuidance("Make the Collimator Wall invisible");
  HideCollimatorWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShowFrontWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowFrontWall",this);
  ShowFrontWall_Cmd->SetGuidance("Make the Front Wall visible");
  ShowFrontWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideFrontWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideFrontWall",this);
  HideFrontWall_Cmd->SetGuidance("Make the Front Wall invisible");
  HideFrontWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShowBackWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowBackWall",this);
  ShowBackWall_Cmd->SetGuidance("Make the Back Wall visible");
  ShowBackWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideBackWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideBackWall",this);
  HideBackWall_Cmd->SetGuidance("Make the Back Wall invisible");
  HideBackWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShowLeftWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowLeftWall",this);
  ShowLeftWall_Cmd->SetGuidance("Make the Left Wall visible");
  ShowLeftWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideLeftWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideLeftWall",this);
  HideLeftWall_Cmd->SetGuidance("Make the Left Wall invisible");
  HideLeftWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  ShowRightWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowRightWall",this);
  ShowRightWall_Cmd->SetGuidance("Make the Right Wall visible");
  ShowRightWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideRightWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideRightWall",this);
  HideRightWall_Cmd->SetGuidance("Make the Right Wall invisible");
  HideRightWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShowTopWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/ShowTopWall",this);
  ShowTopWall_Cmd->SetGuidance("Make the Top Wall visible");
  ShowTopWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //
  HideTopWall_Cmd = new G4UIcmdWithoutParameter("/DetectorHut/Visibility/HideTopWall",this);
  HideTopWall_Cmd->SetGuidance("Make the Top Wall invisible");
  HideTopWall_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimShieldingWallMessenger::~QweakSimShieldingWallMessenger()
{


    delete CollimatorWallMatCmd;
    delete CollimatorWallZPosCmd;
    delete ShowCollimatorWall_Cmd;
    delete HideCollimatorWall_Cmd;

    delete ShowFrontWall_Cmd;
    delete HideFrontWall_Cmd;

    delete ShowBackWall_Cmd;
    delete HideBackWall_Cmd;

    delete ShowLeftWall_Cmd;
    delete HideLeftWall_Cmd;

    delete ShowRightWall_Cmd;
    delete HideRightWall_Cmd;

    delete VisibilityDir;
    delete CollimatorWallDir;
    delete DetectorHutDir;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWallMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimShieldingWallMessenger::SetNewValue() " << newValue << G4endl;

 //-----------------------------------------------------------------------

  if( command == CollimatorWallZPosCmd )
   {
     G4cout << "#### Messenger: Setting CollimatorWall Z position to " << newValue << G4endl;

     myShieldingWall->SetCollimatorWall_CenterPositionInZ(CollimatorWallZPosCmd->GetNewDoubleValue(newValue));
   }

  if( command == CollimatorWallMatCmd )
  { 
      G4cout << "#### Messenger: Setting CollimatorWall Material to " << newValue << G4endl;
      
      myShieldingWall->SetCollimatorWallMaterial(newValue);
  }

  //-----------------------------------------------------------------------

  if( command == ShowCollimatorWall_Cmd )
  { 
      G4cout << "#### Messenger: Show CollimatorWall " << G4endl;
      
      myShieldingWall->ShowCollimatorWall();
  }

  if( command == HideCollimatorWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide CollimatorWall " << G4endl;

       myShieldingWall->HideCollimatorWall();
   }

  //-----------------------------------------------------------------------

  if( command == ShowFrontWall_Cmd )
  { 
      G4cout << "#### Messenger: Show FrontWall " << G4endl;
      
      myShieldingWall->ShowFrontWall();
  }

  if( command == HideFrontWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide FrontWall " << G4endl;

       myShieldingWall->HideFrontWall();
   }

  //-----------------------------------------------------------------------

  if( command == ShowBackWall_Cmd )
  { 
      G4cout << "#### Messenger: Show BackWall " << G4endl;

      myShieldingWall->ShowBackWall();
  }

  if( command == HideBackWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide BackWall " << G4endl;

       myShieldingWall->HideBackWall();
   }

  //-----------------------------------------------------------------------

  if( command == ShowLeftWall_Cmd )
  { 
      G4cout << "#### Messenger: Show LeftWall " << G4endl;

      myShieldingWall->ShowBeamLeftSideWall();
  }

  if( command == HideLeftWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide LeftWall " << G4endl;

       myShieldingWall->HideBeamLeftSideWall();
   }

  //-----------------------------------------------------------------------

  if( command == ShowRightWall_Cmd )
  { 
      G4cout << "#### Messenger: Show RightWall " << G4endl;

      myShieldingWall->ShowBeamRightSideWall();
  }

  if( command == HideRightWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide RightWall " << G4endl;

       myShieldingWall->HideBeamRightSideWall();
   }

  //-----------------------------------------------------------------------


  if( command == ShowTopWall_Cmd )
  { 
      G4cout << "#### Messenger: Show TopWall " << G4endl;

      myShieldingWall->ShowTopWall();
  }

  if( command == HideTopWall_Cmd )
   { 
       G4cout << "#### Messenger: Hide TopWall " << G4endl;

       myShieldingWall->HideTopWall();
   }

  //-----------------------------------------------------------------------

  G4cout << "#### Leaving QweakSimShieldingWallMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimShieldingWallMessenger.cc,v $
//      Revision 1.4  2006/04/26 20:03:31  grimm
//      Added commands for (un)hiding the walls of the shielding detector hut
//
//      Revision 1.3  2006/01/18 20:20:45  grimm
//      Added visibility functions: ShowShieldingWall(), HideShieldingWall()
//
//      Revision 1.2  2005/12/27 19:14:49  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
