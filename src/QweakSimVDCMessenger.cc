//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimVDCMessenger.cc

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:49:47 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:49:47 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDCMessenger.hh"

// user includes
#include "QweakSimMessengerDefinition.hh"
#include "QweakSimVDC.hh"
#include "QweakSimVDCRotator.hh"
#include "QweakSimTriggerScintillator.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDCMessenger::QweakSimVDCMessenger(QweakSimVDC* theVDC,G4int pkg)
:myVDC(theVDC),fPackage(pkg)
{ 
  
 // VDC related
  VDCDir = new G4UIdirectory("/VDC/");
  VDCDir -> SetGuidance("VDC control.");
       
  VDC_FrontCenterPositionInX_Cmd =  new G4UIcmdWithADoubleAndUnit("/VDC/SetFrontCenterPositionInX",this);
  VDC_FrontCenterPositionInX_Cmd->SetGuidance("Set the X position of the VDC Front container center"); 
  VDC_FrontCenterPositionInX_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInX_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_FrontCenterPositionInY_Cmd =  new G4UIcmdWithADoubleAndUnit("/VDC/SetFrontCenterPositionInY",this);
  VDC_FrontCenterPositionInY_Cmd->SetGuidance("Set the Y position of the VDC Front container center"); 
  VDC_FrontCenterPositionInY_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInY_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_FrontCenterPositionInZ_Cmd =  new G4UIcmdWithADoubleAndUnit("/VDC/SetFrontCenterPositionInZ",this);
  VDC_FrontCenterPositionInZ_Cmd->SetGuidance("Set the Z position of the VDC Front container center"); 
  VDC_FrontCenterPositionInZ_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInZ_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_MasterContainerMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_MasterContainerMaterial",this);
  VDC_MasterContainerMatCmd->SetGuidance("Select Material of the VDC MasterContainer.");
  VDC_MasterContainerMatCmd->SetParameterName("choice",false);
  VDC_MasterContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_SubContainerMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_SubContainerMaterial",this);
  VDC_SubContainerMatCmd->SetGuidance("Select Material of the VDC SubContainer.");
  VDC_SubContainerMatCmd->SetParameterName("choice",false);
  VDC_SubContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_G10FrameMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_G10FrameMaterial",this);
  VDC_G10FrameMatCmd->SetGuidance("Select Material of the VDC G10 Frames.");
  VDC_G10FrameMatCmd->SetParameterName("choice",false);
  VDC_G10FrameMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_AluFrameMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_AluFrameMaterial",this);
  VDC_AluFrameMatCmd->SetGuidance("Select Material of the VDC AluFrame.");
  VDC_AluFrameMatCmd->SetParameterName("choice",false);
  VDC_AluFrameMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_FoilMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_FoilMaterial",this);
  VDC_FoilMatCmd->SetGuidance("Select Material of the VDC Foils.");
  VDC_FoilMatCmd->SetParameterName("choice",false);
  VDC_FoilMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_WirePlaneMatCmd = new G4UIcmdWithAString("/VDC/SetVDC_WirePlaneMaterial",this);
  VDC_WirePlaneMatCmd->SetGuidance("Select Material of the VDC WirePlane.");
  VDC_WirePlaneMatCmd->SetParameterName("choice",false);
  VDC_WirePlaneMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  VDC_RotationAngleInPhi_Cmd =  new G4UIcmdWithADoubleAndUnit("/VDC/SetRotationAngleInPhi",this);
  VDC_RotationAngleInPhi_Cmd->SetGuidance("Set the rotation angle in phi"); 
  VDC_RotationAngleInPhi_Cmd->SetParameterName("Size",true);
  VDC_RotationAngleInPhi_Cmd->SetUnitCategory("Angle");
  VDC_RotationAngleInPhi_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  VDC_MeanTrackAngleInTheta_Cmd =  new G4UIcmdWithADoubleAndUnit("/VDC/SetMeanTrackAngleInTheta",this);
  VDC_MeanTrackAngleInTheta_Cmd->SetGuidance("Set the mean track angle in theta"); 
  VDC_MeanTrackAngleInTheta_Cmd->SetParameterName("Size",true);
  VDC_MeanTrackAngleInTheta_Cmd->SetUnitCategory("Angle");
  VDC_MeanTrackAngleInTheta_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  //========================
  //   Drift Cell related
  //========================

 // VDC related
  DriftCellDir = new G4UIdirectory("/VDC/DriftCell/");
  DriftCellDir -> SetGuidance("VDC Drift Cell control.");

  DCMatCmd = new G4UIcmdWithAString("/VDC/DriftCell/SetMaterial",this);
  DCMatCmd->SetGuidance("Select Material of the VDC DriftCells.");
  DCMatCmd->SetParameterName("choice",false);
  DCMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCFrontWireAngleCmd =  new G4UIcmdWithADoubleAndUnit("/VDC/DriftCell/SetWireAngleFront",this);
  DCFrontWireAngleCmd->SetGuidance("Set Wire Angle of Front Plane"); 
  DCFrontWireAngleCmd->SetParameterName("Angle",true);
  DCFrontWireAngleCmd->SetDefaultUnit("degree");
  DCFrontWireAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCBackWireAngleCmd =  new G4UIcmdWithADoubleAndUnit("/VDC/DriftCell/SetWireAngleBack",this);
  DCBackWireAngleCmd->SetGuidance("Set Wire Angle of Back Plane"); 
  DCBackWireAngleCmd->SetParameterName("Angle",true);
  DCBackWireAngleCmd->SetDefaultUnit("degree");
  DCBackWireAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCThicknessCmd =  new G4UIcmdWithADoubleAndUnit("/VDC/DriftCell/SetFullThickness",this);
  DCThicknessCmd->SetGuidance("Set Drift Cell Full Thickness"); 
  DCThicknessCmd->SetParameterName("Size",true);
  DCThicknessCmd->SetUnitCategory("Length");
  DCThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCHeightCmd =  new G4UIcmdWithADoubleAndUnit("/VDC/DriftCell/SetFullHeight",this);
  DCHeightCmd->SetGuidance("Set Drift Cell Full Height"); 
  DCHeightCmd->SetParameterName("Size",true);
  DCHeightCmd->SetUnitCategory("Length");
  DCHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCWidthOnFrameCmd =  new G4UIcmdWithADoubleAndUnit("/VDC/DriftCell/SetFullWidthOnFrame",this);
  DCWidthOnFrameCmd->SetGuidance("Set Drift Cell Full Width seem by the Frame"); 
  DCWidthOnFrameCmd->SetParameterName("Size",true);
  DCWidthOnFrameCmd->SetUnitCategory("Length");
  DCWidthOnFrameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DCNumberPerPlaneCmd = new G4UIcmdWithAnInteger("/VDC/DriftCell/SetDCNumberPerPlane",this);
  DCNumberPerPlaneCmd->SetGuidance("Set the Number of Drift Cells per Plane");
  DCNumberPerPlaneCmd->SetParameterName("Number",true);
  DCNumberPerPlaneCmd->SetDefaultValue(401);
  DCNumberPerPlaneCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  //-----------------------Individual Package Commands-------------------------------

  G4String DirPerPackage_name = "/VDC/VDC" + G4UIcommand::ConvertToString(pkg+1);
  DirPerPackage = new  G4UIdirectory(G4String(DirPerPackage_name + "/"));
  DirPerPackage -> SetGuidance("Individual VDC detector control.");

  VDC_FrontCenterPositionInX_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInX"),this);
  VDC_FrontCenterPositionInX_Pkg_Cmd->SetGuidance("Set the X position of the VDC Front container center");
  VDC_FrontCenterPositionInX_Pkg_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInX_Pkg_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInX_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_FrontCenterPositionInY_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInY"),this);
  VDC_FrontCenterPositionInY_Pkg_Cmd->SetGuidance("Set the Y position of the VDC Front container center");
  VDC_FrontCenterPositionInY_Pkg_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInY_Pkg_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInY_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_FrontCenterPositionInZ_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetFrontCenterPositionInZ"),this);
  VDC_FrontCenterPositionInZ_Pkg_Cmd->SetGuidance("Set the Z position of the VDC Front container center");
  VDC_FrontCenterPositionInZ_Pkg_Cmd->SetParameterName("Size",true);
  VDC_FrontCenterPositionInZ_Pkg_Cmd->SetUnitCategory("Length");
  VDC_FrontCenterPositionInZ_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VDC_RotationAngleInPhi_Pkg_Cmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerPackage_name + "/SetRotationAngleInPhi"),this);
  VDC_RotationAngleInPhi_Pkg_Cmd->SetGuidance("Set the rotation angle in phi");
  VDC_RotationAngleInPhi_Pkg_Cmd->SetParameterName("Size",true);
  VDC_RotationAngleInPhi_Pkg_Cmd->SetUnitCategory("Angle");
  VDC_RotationAngleInPhi_Pkg_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDCMessenger::~QweakSimVDCMessenger()
{

  if (VDC_WirePlaneMatCmd)            delete VDC_WirePlaneMatCmd;
  if (VDC_FoilMatCmd)                 delete VDC_FoilMatCmd;  

  if (VDC_G10FrameMatCmd)             delete VDC_G10FrameMatCmd;
  if (VDC_AluFrameMatCmd)             delete VDC_AluFrameMatCmd;

  if (VDC_SubContainerMatCmd)         delete VDC_SubContainerMatCmd;
  if (VDC_MasterContainerMatCmd)      delete VDC_MasterContainerMatCmd;

  if (VDC_FrontCenterPositionInX_Cmd) delete VDC_FrontCenterPositionInX_Cmd;
  if (VDC_FrontCenterPositionInY_Cmd) delete VDC_FrontCenterPositionInY_Cmd;
  if (VDC_FrontCenterPositionInZ_Cmd) delete VDC_FrontCenterPositionInZ_Cmd;

  if (VDC_RotationAngleInPhi_Cmd)     delete VDC_RotationAngleInPhi_Cmd;
  if (VDC_MeanTrackAngleInTheta_Cmd)  delete VDC_MeanTrackAngleInTheta_Cmd;


  if (VDC_FrontCenterPositionInX_Pkg_Cmd) delete VDC_FrontCenterPositionInX_Pkg_Cmd;
  if (VDC_FrontCenterPositionInY_Pkg_Cmd) delete VDC_FrontCenterPositionInY_Pkg_Cmd;
  if (VDC_FrontCenterPositionInZ_Pkg_Cmd) delete VDC_FrontCenterPositionInZ_Pkg_Cmd;

  if (VDC_RotationAngleInPhi_Pkg_Cmd)     delete VDC_RotationAngleInPhi_Pkg_Cmd;

  if (VDCDir)               delete VDCDir;
  if (DirPerPackage)               delete DirPerPackage;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDCMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimVDCMessenger::SetNewValue() " << newValue << G4endl;

 
  if( command == VDC_MasterContainerMatCmd )
  { 
      G4cout << "#### Messenger: Setting VDC MasterContainer Material to " << newValue << G4endl;
      
      myVDC->SetVDC_MasterContainerMaterial(newValue);
  }


  if( command == VDC_SubContainerMatCmd )
  { 
      G4cout << "#### Messenger: Setting VDC SubContainer Material to " << newValue << G4endl;
      
      myVDC->SetVDC_SubContainerMaterial(newValue);
  }

  if( command == VDC_G10FrameMatCmd )
   { 
     G4cout << "#### Messenger: Setting VDC G10Frame Material to " << newValue << G4endl;

     myVDC->SetVDC_G10FrameMaterial(newValue);
   }


  if( command == VDC_AluFrameMatCmd )
   { 
     G4cout << "#### Messenger: Setting VDC AluFrame Material to " << newValue << G4endl;

     myVDC->SetVDC_AluFrameMaterial(newValue);
   }


  if( command == VDC_FoilMatCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Foil Material to " << newValue << G4endl;

     myVDC->SetVDC_FoilMaterial(newValue);
   }

  if( command == VDC_WirePlaneMatCmd )
   { 
     G4cout << "#### Messenger: Setting VDC WirePlane Material to " << newValue << G4endl;

     myVDC->SetVDC_WirePlaneMaterial(newValue);
   }

  if( command == VDC_FrontCenterPositionInX_Cmd )
  { 
      G4cout << "#### Messenger: Setting VDC FrontCenter Xpos to " << newValue << G4endl;
      
     myVDC->SetFrontVDC_CenterPositionInX(VDC_FrontCenterPositionInX_Cmd->GetNewDoubleValue(newValue),0);
  }
  
  if( command == VDC_FrontCenterPositionInY_Cmd )
  { 
      G4cout << "#### Messenger: Setting VDC FrontCenter Ypos to " << newValue << G4endl;
      
      myVDC->SetFrontVDC_CenterPositionInY(VDC_FrontCenterPositionInY_Cmd->GetNewDoubleValue(newValue),0);
  }
  
  if( command == VDC_FrontCenterPositionInZ_Cmd )
  { 
     G4cout << "#### Messenger: Setting VDC FrontCenter Zpos to " << newValue << G4endl;
     
     myVDC->SetFrontVDC_CenterPositionInZ(VDC_FrontCenterPositionInZ_Cmd->GetNewDoubleValue(newValue),0);
  }

   if( command == VDC_RotationAngleInPhi_Cmd )
  { 
     G4cout << "#### Messenger: Setting VDC rotation angle in phi to " << newValue << G4endl;
     
     double phi = VDC_RotationAngleInPhi_Cmd->GetNewDoubleValue(newValue);
     myVDC->SetVDC_RotationAngleInPhi(phi,0);
     myVDC->SetVDC_RotationAngleInPhi(phi+180.0*degree,1);
     myRotator = myVDC->GetVDCRotator();
     myRotator->SetRotationAngleInPhi(phi);
     myTriggerScintillator = myVDC->GetTriggerScintillator();
     myTriggerScintillator->SetTriggerScintillatorPhiAngle(phi);
   }


   if( command == VDC_MeanTrackAngleInTheta_Cmd )
   { 
       G4cout << "#### Messenger: Setting VDC mean track angle in theta to " << newValue << G4endl;
       
     myVDC->SetVDC_MeanTrackAngleInTheta(VDC_MeanTrackAngleInTheta_Cmd->GetNewDoubleValue(newValue));
   }
   
//-------------------------------Individual Package Commands-------------------------

   if( command == VDC_FrontCenterPositionInX_Pkg_Cmd )
   {
       G4cout << "#### Messenger: Setting VDC FrontCenter Xpos to " << newValue << G4endl;

      myVDC->SetFrontVDC_CenterPositionInX(VDC_FrontCenterPositionInX_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

   if( command == VDC_FrontCenterPositionInY_Pkg_Cmd )
   {
       G4cout << "#### Messenger: Setting VDC FrontCenter Ypos to " << newValue << G4endl;

       myVDC->SetFrontVDC_CenterPositionInY(VDC_FrontCenterPositionInY_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

   if( command == VDC_FrontCenterPositionInZ_Pkg_Cmd )
   {
      G4cout << "#### Messenger: Setting VDC FrontCenter Zpos to " << newValue << G4endl;

      myVDC->SetFrontVDC_CenterPositionInZ(VDC_FrontCenterPositionInZ_Pkg_Cmd->GetNewDoubleValue(newValue),fPackage);
   }

    if( command == VDC_RotationAngleInPhi_Pkg_Cmd )
   {
      G4cout << "#### Messenger: Setting VDC rotation angle in phi to " << newValue << G4endl;

      double phi = VDC_RotationAngleInPhi_Pkg_Cmd->GetNewDoubleValue(newValue);
      myVDC->SetVDC_RotationAngleInPhi(phi,fPackage);
      myVDC->SetVDC_RotationAngleInPhi(phi+180.0*degree,abs(fPackage-1));
      myRotator = myVDC->GetVDCRotator();
      myRotator->SetRotationAngleInPhi(phi);
    }


  //========================
  //   Drift Cell related
  //========================


   if( command == DCMatCmd )
     { 
       G4cout << "#### Messenger: Setting VDC DriftCell Material to " << newValue << G4endl;

       myVDC->SetVDC_DriftCellMaterial(newValue);
     }


  if( command == DCFrontWireAngleCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Front Wire Angle to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellFrontWireAngle( DCFrontWireAngleCmd->GetNewDoubleValue(newValue) );
   }


  if( command == DCBackWireAngleCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Back Wire Angle to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellBackWireAngle( DCBackWireAngleCmd->GetNewDoubleValue(newValue) );
   }


  if( command == DCThicknessCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Thickness to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellFullThickness( DCThicknessCmd->GetNewDoubleValue(newValue) );
   }

  if( command == DCHeightCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Height to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellFullHeight( DCHeightCmd->GetNewDoubleValue(newValue) );
   }

  if( command ==  DCWidthOnFrameCmd )
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Width seem by Frame to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellFullWidthOnFrame(  DCWidthOnFrameCmd->GetNewDoubleValue(newValue) );
   }

  if( command ==  DCNumberPerPlaneCmd)
   { 
     G4cout << "#### Messenger: Setting VDC Drift Cell Number per Plane to " << newValue << G4endl;

     myVDC->SetVDC_DriftCellNumberPerPlane( DCNumberPerPlaneCmd->GetNewIntValue(newValue) );
   }


  G4cout << "#### Leaving QweakSimVDC Messenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDCMessenger.cc,v $
//      Revision 1.4  2006/05/05 21:49:47  grimm
//      Added   /VDC/DriftCell/SetMaterial
//
//      Revision 1.3  2006/01/13 23:23:19  grimm
//      Due to the updated the VDC geometry code, I changed and added some material setters for MasterContainer, SubContainer, G10Frame, and AluFrame.
//
//      Revision 1.2  2005/12/27 19:20:03  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
