//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimGEMMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:10:09 $

   \author Klaus Hans Grimm   

*/
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGEMMessenger.hh"

// user includes
#include "QweakSimGEM.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGEMMessenger::QweakSimGEMMessenger(QweakSimGEM* theGEM)
:myGEM(theGEM)
{ 
 // GEM related
  GEMDir = new G4UIdirectory("/GEM/");
  GEMDir -> SetGuidance("GEM control.");

  //--------------------

  GEM_FrontCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetFrontCenterPositionInX",this);
  GEM_FrontCenterPositionInX_Cmd->SetGuidance("Set the X position of the GEM Front container center"); 
  GEM_FrontCenterPositionInX_Cmd->SetParameterName("Size",true);
  GEM_FrontCenterPositionInX_Cmd->SetUnitCategory("Length");
  GEM_FrontCenterPositionInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_FrontCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetFrontCenterPositionInY",this);
  GEM_FrontCenterPositionInY_Cmd->SetGuidance("Set the Y position of the GEM Front container center"); 
  GEM_FrontCenterPositionInY_Cmd->SetParameterName("Size",true);
  GEM_FrontCenterPositionInY_Cmd->SetUnitCategory("Length");
  GEM_FrontCenterPositionInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_FrontCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetFrontCenterPositionInZ",this);
  GEM_FrontCenterPositionInZ_Cmd->SetGuidance("Set the Z position of the GEM Front container center"); 
  GEM_FrontCenterPositionInZ_Cmd->SetParameterName("Size",true);
  GEM_FrontCenterPositionInZ_Cmd->SetUnitCategory("Length");
  GEM_FrontCenterPositionInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //--------------------

  GEM_BackCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetBackCenterPositionInX",this);
  GEM_BackCenterPositionInX_Cmd->SetGuidance("Set the X position of the GEM Back container center"); 
  GEM_BackCenterPositionInX_Cmd->SetParameterName("Size",true);
  GEM_BackCenterPositionInX_Cmd->SetUnitCategory("Length");
  GEM_BackCenterPositionInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_BackCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetBackCenterPositionInY",this);
  GEM_BackCenterPositionInY_Cmd->SetGuidance("Set the Y position of the GEM Back container center"); 
  GEM_BackCenterPositionInY_Cmd->SetParameterName("Size",true);
  GEM_BackCenterPositionInY_Cmd->SetUnitCategory("Length");
  GEM_BackCenterPositionInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_BackCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetBackCenterPositionInZ",this);
  GEM_BackCenterPositionInZ_Cmd->SetGuidance("Set the Z position of the GEM Back container center"); 
  GEM_BackCenterPositionInZ_Cmd->SetParameterName("Size",true);
  GEM_BackCenterPositionInZ_Cmd->SetUnitCategory("Length");
  GEM_BackCenterPositionInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //--------------------

  GEM_MasterContainerMatCmd = new G4UIcmdWithAString("/GEM/SetMasterContainerMaterial",this);
  GEM_MasterContainerMatCmd->SetGuidance("Select Material of the GEM MasterContainer.");
  GEM_MasterContainerMatCmd->SetParameterName("choice",false);
  GEM_MasterContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_SubContainerMatCmd = new G4UIcmdWithAString("/GEM/SetSubContainerMaterial",this);
  GEM_SubContainerMatCmd->SetGuidance("Select Material of the GEM MasterContainer.");
  GEM_SubContainerMatCmd->SetParameterName("choice",false);
  GEM_SubContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//   GEM_FoilMatCmd = new G4UIcmdWithAString("/GEM/SetFoilMaterial",this);
//   GEM_FoilMatCmd->SetGuidance("Select Material of the GEM Foil.");
//   GEM_FoilMatCmd->SetParameterName("choice",false);
//   GEM_FoilMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GEM_FrameMatCmd = new G4UIcmdWithAString("/GEM/SetFrameMaterial",this);
  GEM_FrameMatCmd->SetGuidance("Select Material of the GEM Frame.");
  GEM_FrameMatCmd->SetParameterName("choice",false);
  GEM_FrameMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//   GEM_WirePlaneMatCmd = new G4UIcmdWithAString("/GEM/SetWirePlaneMaterial",this);
//   GEM_WirePlaneMatCmd->SetGuidance("Select Material of the GEM WirePlane.");
//   GEM_WirePlaneMatCmd->SetParameterName("choice",false);
//   GEM_WirePlaneMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  GEM_FrontChamber_RotationAngleInPhi_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetFrontChamberRotationAngleInPhi",this);
  GEM_FrontChamber_RotationAngleInPhi_Cmd ->SetGuidance("Set the Front GEM rotation angle in phi"); 
  GEM_FrontChamber_RotationAngleInPhi_Cmd ->SetParameterName("Size",true);
  GEM_FrontChamber_RotationAngleInPhi_Cmd ->SetUnitCategory("Angle");
  GEM_FrontChamber_RotationAngleInPhi_Cmd ->AvailableForStates(G4State_PreInit,G4State_Idle);


  GEM_BackChamber_RotationAngleInPhi_Cmd =  new G4UIcmdWithADoubleAndUnit("/GEM/SetBackChamberRotationAngleInPhi",this);
  GEM_BackChamber_RotationAngleInPhi_Cmd ->SetGuidance("Set the Back GEM rotation angle in phi"); 
  GEM_BackChamber_RotationAngleInPhi_Cmd ->SetParameterName("Size",true);
  GEM_BackChamber_RotationAngleInPhi_Cmd ->SetUnitCategory("Angle");
  GEM_BackChamber_RotationAngleInPhi_Cmd ->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGEMMessenger::~QweakSimGEMMessenger()
{

 // if (GEM_WirePlaneMatCmd)        delete GEM_WirePlaneMatCmd;
 // if (GEM_FoilMatCmd)             delete GEM_FoilMatCmd;  
  if (GEM_FrameMatCmd)            delete GEM_FrameMatCmd;  
  if (GEM_SubContainerMatCmd)     delete GEM_SubContainerMatCmd;
  if (GEM_MasterContainerMatCmd)  delete GEM_MasterContainerMatCmd;

  if (GEM_FrontCenterPositionInX_Cmd) delete GEM_FrontCenterPositionInX_Cmd;
  if (GEM_FrontCenterPositionInY_Cmd) delete GEM_FrontCenterPositionInY_Cmd;
  if (GEM_FrontCenterPositionInZ_Cmd) delete GEM_FrontCenterPositionInZ_Cmd;

  if (GEM_BackCenterPositionInX_Cmd) delete GEM_BackCenterPositionInX_Cmd;
  if (GEM_BackCenterPositionInY_Cmd) delete GEM_BackCenterPositionInY_Cmd;
  if (GEM_BackCenterPositionInZ_Cmd) delete GEM_BackCenterPositionInZ_Cmd;

  if (GEM_FrontChamber_RotationAngleInPhi_Cmd)   delete GEM_FrontChamber_RotationAngleInPhi_Cmd;
  if (GEM_BackChamber_RotationAngleInPhi_Cmd)    delete GEM_BackChamber_RotationAngleInPhi_Cmd;

  if (GEMDir)               delete GEMDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGEMMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimGEMMessenger::SetNewValue() " << newValue << G4endl;

  
  if( command == GEM_MasterContainerMatCmd )
  { 
      G4cout << "#### Messenger: Setting GEM MasterContainer Material to " << newValue << G4endl;
    
      myGEM->SetGEM_MasterContainerMaterial(newValue);
  }


  if( command == GEM_SubContainerMatCmd )
   { 
     G4cout << "#### Messenger: Setting GEM SubContainer Material to " << newValue << G4endl;

     myGEM->SetGEM_SubContainerMaterial(newValue);
   }


  if( command == GEM_FrameMatCmd )
  { 
      G4cout << "#### Messenger: Setting GEM Frame Material to " << newValue << G4endl;
      
      myGEM->SetGEM_FrameMaterial(newValue);
  }


//   if( command == GEM_FoilMatCmd )
//   {
//       G4cout << "#### Messenger: Setting GEM Foil Material to " << newValue << G4endl;
//
//       myGEM->SetGEM_FoilMaterial(newValue);
//   }



//   if( command == GEM_WirePlaneMatCmd )
//    {
//      G4cout << "#### Messenger: Setting GEM WirePlane Material to " << newValue << G4endl;
//
//      myGEM->SetGEM_WirePlaneMaterial(newValue);
//    }



  if( command == GEM_FrontCenterPositionInX_Cmd )
  { 
      G4cout << "#### Messenger: Setting GEM FrontCenter Xpos to " << newValue << G4endl;
      
     myGEM->SetFrontGEM_CenterPositionInX(GEM_FrontCenterPositionInX_Cmd->GetNewDoubleValue(newValue));
  }
  
  if( command == GEM_FrontCenterPositionInY_Cmd )
  { 
      G4cout << "#### Messenger: Setting GEM FrontCenter Ypos to " << newValue << G4endl;
      
      myGEM->SetFrontGEM_CenterPositionInY(GEM_FrontCenterPositionInY_Cmd->GetNewDoubleValue(newValue));
  }
  
  if( command == GEM_FrontCenterPositionInZ_Cmd )
  { 
     G4cout << "#### Messenger: Setting GEM FrontCenter Zpos to " << newValue << G4endl;
     
     myGEM->SetFrontGEM_CenterPositionInZ(GEM_FrontCenterPositionInZ_Cmd->GetNewDoubleValue(newValue));
  }

  if( command == GEM_FrontChamber_RotationAngleInPhi_Cmd )
  { 
      G4cout << "#### Messenger: Setting Front Chamber GEM rotation angle in phi to " << newValue << G4endl;
      
      myGEM->SetGEM_FrontChamber_RotationAngleInPhi(GEM_FrontChamber_RotationAngleInPhi_Cmd->GetNewDoubleValue(newValue));
  }



  if( command == GEM_BackCenterPositionInX_Cmd )
   { 
       G4cout << "#### Messenger: Setting GEM BackCenter Xpos to " << newValue << G4endl;

      myGEM->SetBackGEM_CenterPositionInX(GEM_BackCenterPositionInX_Cmd->GetNewDoubleValue(newValue));
   }

   if( command == GEM_BackCenterPositionInY_Cmd )
   { 
       G4cout << "#### Messenger: Setting GEM BackCenter Ypos to " << newValue << G4endl;

       myGEM->SetBackGEM_CenterPositionInY(GEM_BackCenterPositionInY_Cmd->GetNewDoubleValue(newValue));
   }

   if( command == GEM_BackCenterPositionInZ_Cmd )
   { 
      G4cout << "#### Messenger: Setting GEM BackCenter Zpos to " << newValue << G4endl;

      myGEM->SetBackGEM_CenterPositionInZ(GEM_BackCenterPositionInZ_Cmd->GetNewDoubleValue(newValue));

   }


   if( command == GEM_BackChamber_RotationAngleInPhi_Cmd )
   { 
       G4cout << "#### Messenger: Setting BackChamber GEM rotation angle in phi to " << newValue << G4endl;
       
       myGEM->SetGEM_BackChamber_RotationAngleInPhi(GEM_BackChamber_RotationAngleInPhi_Cmd->GetNewDoubleValue(newValue));
   }
   

  G4cout << "#### Leaving QweakSimGEMMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

