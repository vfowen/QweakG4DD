
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimHDCMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:12:24 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:12:24 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimHDCMessenger.hh"

// user includes
#include "QweakSimHDC.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDCMessenger::QweakSimHDCMessenger(QweakSimHDC* theHDC,G4int pkg)
:myHDC(theHDC),fPackage(pkg)
{ 
 // HDC related
  HDCDir = new G4UIdirectory("/HDC/");
  HDCDir -> SetGuidance("HDC control.");

  //--------------------

  HDC_FrontCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetFrontCenterPositionInX",this);
  HDC_FrontCenterPositionInX_Cmd->SetGuidance("Set the X position of the HDC Front container center"); 
  HDC_FrontCenterPositionInX_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInX_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FrontCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetFrontCenterPositionInY",this);
  HDC_FrontCenterPositionInY_Cmd->SetGuidance("Set the Y position of the HDC Front container center"); 
  HDC_FrontCenterPositionInY_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInY_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FrontCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetFrontCenterPositionInZ",this);
  HDC_FrontCenterPositionInZ_Cmd->SetGuidance("Set the Z position of the HDC Front container center"); 
  HDC_FrontCenterPositionInZ_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInZ_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //--------------------

  HDC_BackCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetBackCenterPositionInX",this);
  HDC_BackCenterPositionInX_Cmd->SetGuidance("Set the X position of the HDC Back container center"); 
  HDC_BackCenterPositionInX_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInX_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_BackCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetBackCenterPositionInY",this);
  HDC_BackCenterPositionInY_Cmd->SetGuidance("Set the Y position of the HDC Back container center"); 
  HDC_BackCenterPositionInY_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInY_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_BackCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetBackCenterPositionInZ",this);
  HDC_BackCenterPositionInZ_Cmd->SetGuidance("Set the Z position of the HDC Back container center"); 
  HDC_BackCenterPositionInZ_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInZ_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //--------------------

  HDC_MasterContainerMatCmd = new G4UIcmdWithAString("/HDC/SetMasterContainerMaterial",this);
  HDC_MasterContainerMatCmd->SetGuidance("Select Material of the HDC MasterContainer.");
  HDC_MasterContainerMatCmd->SetParameterName("choice",false);
  HDC_MasterContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_SubContainerMatCmd = new G4UIcmdWithAString("/HDC/SetSubContainerMaterial",this);
  HDC_SubContainerMatCmd->SetGuidance("Select Material of the HDC MasterContainer.");
  HDC_SubContainerMatCmd->SetParameterName("choice",false);
  HDC_SubContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FoilMatCmd = new G4UIcmdWithAString("/HDC/SetFoilMaterial",this);
  HDC_FoilMatCmd->SetGuidance("Select Material of the HDC Foil.");
  HDC_FoilMatCmd->SetParameterName("choice",false);
  HDC_FoilMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FrameMatCmd = new G4UIcmdWithAString("/HDC/SetFrameMaterial",this);
  HDC_FrameMatCmd->SetGuidance("Select Material of the HDC Frame.");
  HDC_FrameMatCmd->SetParameterName("choice",false);
  HDC_FrameMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_WirePlaneMatCmd = new G4UIcmdWithAString("/HDC/SetWirePlaneMaterial",this);
  HDC_WirePlaneMatCmd->SetGuidance("Select Material of the HDC WirePlane.");
  HDC_WirePlaneMatCmd->SetParameterName("choice",false);
  HDC_WirePlaneMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  HDC_RotationAngleInPhi_Cmd =  new G4UIcmdWithADoubleAndUnit("/HDC/SetRotationAngleInPhi",this);
  HDC_RotationAngleInPhi_Cmd->SetGuidance("Set the rotation angle in phi"); 
  HDC_RotationAngleInPhi_Cmd->SetParameterName("Size",true);
  HDC_RotationAngleInPhi_Cmd->SetUnitCategory("Angle");
  HDC_RotationAngleInPhi_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //-----------------------------------------------------------------------------------
  // Below commands for single HDC Packages

  G4String DirPerPackage_name = "/HDC/HDC" + G4UIcommand::ConvertToString(pkg+1);
  DirPerPackage = new  G4UIdirectory(G4String(DirPerPackage_name + "/"));
  DirPerPackage -> SetGuidance("Individual HDC detector control.");

  HDC_FrontCenterPositionInX_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInX"),this);
  HDC_FrontCenterPositionInX_Pkg_Cmd->SetGuidance("Set the X position of the HDC Front container center of a package");
  HDC_FrontCenterPositionInX_Pkg_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInX_Pkg_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInX_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FrontCenterPositionInY_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInY"),this);
  HDC_FrontCenterPositionInY_Pkg_Cmd->SetGuidance("Set the Y position of the HDC Front container center");
  HDC_FrontCenterPositionInY_Pkg_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInY_Pkg_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInY_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_FrontCenterPositionInZ_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInZ"),this);
  HDC_FrontCenterPositionInZ_Pkg_Cmd->SetGuidance("Set the Z position of the HDC Front container center");
  HDC_FrontCenterPositionInZ_Pkg_Cmd->SetParameterName("Size",true);
  HDC_FrontCenterPositionInZ_Pkg_Cmd->SetUnitCategory("Length");
  HDC_FrontCenterPositionInZ_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  HDC_BackCenterPositionInX_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetBackCenterPositionInX"),this);
  HDC_BackCenterPositionInX_Pkg_Cmd->SetGuidance("Set the X position of the HDC Back container center");
  HDC_BackCenterPositionInX_Pkg_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInX_Pkg_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInX_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_BackCenterPositionInY_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetBackCenterPositionInY"),this);
  HDC_BackCenterPositionInY_Pkg_Cmd->SetGuidance("Set the Y position of the HDC Back container center");
  HDC_BackCenterPositionInY_Pkg_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInY_Pkg_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInY_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_BackCenterPositionInZ_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetBackCenterPositionInZ"),this);
  HDC_BackCenterPositionInZ_Pkg_Cmd->SetGuidance("Set the Z position of the HDC Back container center");
  HDC_BackCenterPositionInZ_Pkg_Cmd->SetParameterName("Size",true);
  HDC_BackCenterPositionInZ_Pkg_Cmd->SetUnitCategory("Length");
  HDC_BackCenterPositionInZ_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HDC_RotationAngleInPhi_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetRotationAngleInPhi"),this);
  HDC_RotationAngleInPhi_Pkg_Cmd->SetGuidance("Set the rotation angle in phi");
  HDC_RotationAngleInPhi_Pkg_Cmd->SetParameterName("Size",true);
  HDC_RotationAngleInPhi_Pkg_Cmd->SetUnitCategory("Angle");
  HDC_RotationAngleInPhi_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDCMessenger::~QweakSimHDCMessenger()
{

  if (HDC_WirePlaneMatCmd)        delete HDC_WirePlaneMatCmd;
  if (HDC_FoilMatCmd)             delete HDC_FoilMatCmd;  
  if (HDC_FrameMatCmd)            delete HDC_FrameMatCmd;  
  if (HDC_SubContainerMatCmd)     delete HDC_SubContainerMatCmd;
  if (HDC_MasterContainerMatCmd)  delete HDC_MasterContainerMatCmd;

  if (HDC_FrontCenterPositionInX_Cmd) delete HDC_FrontCenterPositionInX_Cmd;
  if (HDC_FrontCenterPositionInY_Cmd) delete HDC_FrontCenterPositionInY_Cmd;
  if (HDC_FrontCenterPositionInZ_Cmd) delete HDC_FrontCenterPositionInZ_Cmd;

  if (HDC_BackCenterPositionInX_Cmd)  delete HDC_BackCenterPositionInX_Cmd;
  if (HDC_BackCenterPositionInY_Cmd)  delete HDC_BackCenterPositionInY_Cmd;
  if (HDC_BackCenterPositionInZ_Cmd)  delete HDC_BackCenterPositionInZ_Cmd;

  if (HDC_RotationAngleInPhi_Cmd)     delete HDC_RotationAngleInPhi_Cmd;


  if (HDC_FrontCenterPositionInX_Pkg_Cmd) delete HDC_FrontCenterPositionInX_Pkg_Cmd;
  if (HDC_FrontCenterPositionInY_Pkg_Cmd) delete HDC_FrontCenterPositionInY_Pkg_Cmd;
  if (HDC_FrontCenterPositionInZ_Pkg_Cmd) delete HDC_FrontCenterPositionInZ_Pkg_Cmd;

  if (HDC_BackCenterPositionInX_Pkg_Cmd)  delete HDC_BackCenterPositionInX_Pkg_Cmd;
  if (HDC_BackCenterPositionInY_Pkg_Cmd)  delete HDC_BackCenterPositionInY_Pkg_Cmd;
  if (HDC_BackCenterPositionInZ_Pkg_Cmd)  delete HDC_BackCenterPositionInZ_Pkg_Cmd;

  if (HDC_RotationAngleInPhi_Pkg_Cmd)     delete HDC_RotationAngleInPhi_Pkg_Cmd;

  if (HDCDir)               delete HDCDir;
  if (DirPerPackage)		delete DirPerPackage;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimHDCMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimHDCMessenger::SetNewValue() " << newValue << G4endl;

  
  if( command == HDC_MasterContainerMatCmd )
  { 
      G4cout << "#### Messenger: Setting HDC MasterContainer Material to " << newValue << G4endl;
    
      myHDC->SetHDC_MasterContainerMaterial(newValue);
  }


  if( command == HDC_SubContainerMatCmd )
   { 
     G4cout << "#### Messenger: Setting HDC SubContainer Material to " << newValue << G4endl;

     myHDC->SetHDC_SubContainerMaterial(newValue);
   }


  if( command == HDC_FrameMatCmd )
  { 
      G4cout << "#### Messenger: Setting HDC Frame Material to " << newValue << G4endl;
      
      myHDC->SetHDC_FrameMaterial(newValue);
  }


  if( command == HDC_FoilMatCmd )
  { 
      G4cout << "#### Messenger: Setting HDC Foil Material to " << newValue << G4endl;
      
      myHDC->SetHDC_FoilMaterial(newValue);
  }



  if( command == HDC_WirePlaneMatCmd )
   { 
     G4cout << "#### Messenger: Setting HDC WirePlane Material to " << newValue << G4endl;

     myHDC->SetHDC_WirePlaneMaterial(newValue);
   }

  //-----------------------------------------------------------

  if( command == HDC_FrontCenterPositionInX_Cmd )
  { 
      G4cout << "#### Messenger: Setting HDC FrontCenter Xpos to " << newValue << G4endl;
      
     myHDC->SetFrontHDC_CenterPositionInX(HDC_FrontCenterPositionInX_Cmd->GetNewDoubleValue(newValue),0);
  }
  
  if( command == HDC_FrontCenterPositionInY_Cmd )
  { 
      G4cout << "#### Messenger: Setting HDC FrontCenter Ypos to " << newValue << G4endl;
      
      myHDC->SetFrontHDC_CenterPositionInY(HDC_FrontCenterPositionInY_Cmd->GetNewDoubleValue(newValue),0);
  }
  
  if( command == HDC_FrontCenterPositionInZ_Cmd )
  { 
     G4cout << "#### Messenger: Setting HDC FrontCenter Zpos to " << newValue << G4endl;
     
     myHDC->SetFrontHDC_CenterPositionInZ(HDC_FrontCenterPositionInZ_Cmd->GetNewDoubleValue(newValue),0);
  }


  //-----------------------------------------------------------

   if( command == HDC_BackCenterPositionInX_Cmd )
   { 
       G4cout << "#### Messenger: Setting HDC BackCenter Xpos to " << newValue << G4endl;

      myHDC->SetBackHDC_CenterPositionInX(HDC_BackCenterPositionInX_Cmd->GetNewDoubleValue(newValue),0);
   }

   if( command == HDC_BackCenterPositionInY_Cmd )
   { 
       G4cout << "#### Messenger: Setting HDC BackCenter Ypos to " << newValue << G4endl;

       myHDC->SetBackHDC_CenterPositionInY(HDC_BackCenterPositionInY_Cmd->GetNewDoubleValue(newValue),0);
   }

   if( command == HDC_BackCenterPositionInZ_Cmd )
   { 
      G4cout << "#### Messenger: Setting HDC BackCenter Zpos to " << newValue << G4endl;

      myHDC->SetBackHDC_CenterPositionInZ(HDC_BackCenterPositionInZ_Cmd->GetNewDoubleValue(newValue),0);
   }



   if( command == HDC_RotationAngleInPhi_Cmd )
  { 
     G4cout << "#### Messenger: Setting HDC rotation angle in phi to " << newValue << G4endl;
     
     myHDC->SetHDC_RotationAngleInPhi(HDC_RotationAngleInPhi_Cmd->GetNewDoubleValue(newValue),0);
     myHDC->SetHDC_RotationAngleInPhi(HDC_RotationAngleInPhi_Cmd->GetNewDoubleValue(newValue)+180.0*degree,1);
  }
   //-----------------------------------------------------------

   if( command == HDC_FrontCenterPositionInX_Pkg_Cmd )
   {
       G4cout << "#### Messenger: Setting HDC FrontCenter Xpos to " << newValue << G4endl;

      myHDC->SetFrontHDC_CenterPositionInX(HDC_FrontCenterPositionInX_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

   if( command == HDC_FrontCenterPositionInY_Pkg_Cmd )
   {
       G4cout << "#### Messenger: Setting HDC FrontCenter Ypos to " << newValue << G4endl;

       myHDC->SetFrontHDC_CenterPositionInY(HDC_FrontCenterPositionInY_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

   if( command == HDC_FrontCenterPositionInZ_Pkg_Cmd )
   {
      G4cout << "#### Messenger: Setting HDC FrontCenter Zpos to " << newValue << G4endl;

      myHDC->SetFrontHDC_CenterPositionInZ(HDC_FrontCenterPositionInZ_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }


   //-----------------------------------------------------------

    if( command == HDC_BackCenterPositionInX_Pkg_Cmd )
    {
        G4cout << "#### Messenger: Setting HDC BackCenter Xpos to " << newValue << G4endl;

       myHDC->SetBackHDC_CenterPositionInX(HDC_BackCenterPositionInX_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
    }

    if( command == HDC_BackCenterPositionInY_Pkg_Cmd )
    {
        G4cout << "#### Messenger: Setting HDC BackCenter Ypos to " << newValue << G4endl;

        myHDC->SetBackHDC_CenterPositionInY(HDC_BackCenterPositionInY_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
    }

    if( command == HDC_BackCenterPositionInZ_Pkg_Cmd )
    {
       G4cout << "#### Messenger: Setting HDC BackCenter Zpos to " << newValue << G4endl;

       myHDC->SetBackHDC_CenterPositionInZ(HDC_BackCenterPositionInZ_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
    }

    if( command == HDC_RotationAngleInPhi_Pkg_Cmd )
   {
      G4cout << "#### Messenger: Setting HDC rotation angle in phi to " << newValue << G4endl;

      myHDC->SetHDC_RotationAngleInPhi(HDC_RotationAngleInPhi_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

  G4cout << "#### Leaving QweakSimHDC Messenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimHDCMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:12:24  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

