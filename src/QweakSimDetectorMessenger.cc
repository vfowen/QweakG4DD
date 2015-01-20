//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimDetectorMessenger.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:28:11 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:28:11 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimDetectorMessenger.hh"

// user includes
#include "QweakSimDetectorConstruction.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimDetectorMessenger::QweakSimDetectorMessenger(QweakSimDetectorConstruction* theDetector)
:myDetector(theDetector)
{ 

   QweakSimDir = NULL;
   UpdateCmd   = NULL;



  QweakSimDir = new G4UIdirectory("/HallC/");
  QweakSimDir->SetGuidance("UI commands specific to this example.");

  VisibilityDir = new G4UIdirectory("/HallC/Visibility/");
  VisibilityDir -> SetGuidance("Hall Visibility Control.");

  UpdateCmd = new G4UIcmdWithoutParameter("/HallC/GeometryUpdate",this);
  UpdateCmd->SetGuidance("Update Qweak geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

  DumpGeometry_Cmd = new G4UIcmdWithABool("/HallC/DumpGeometry",this);
  DumpGeometry_Cmd->SetGuidance("Dump geometry tree, with optional overlap check.");
  DumpGeometry_Cmd->SetParameterName("check_overlap",true);
  DumpGeometry_Cmd->SetDefaultValue("false");
  DumpGeometry_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ShowHallFloor_Cmd = new G4UIcmdWithoutParameter("/HallC/Visibility/ShowHallFloor",this);
  ShowHallFloor_Cmd->SetGuidance("Make the Hall Floor visible");
  ShowHallFloor_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  HideHallFloor_Cmd = new G4UIcmdWithoutParameter("/HallC/Visibility/HideHallFloor",this);
  HideHallFloor_Cmd->SetGuidance("Make the Hall Floor invisible");
  HideHallFloor_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimDetectorMessenger::~QweakSimDetectorMessenger()
{
  if (UpdateCmd)         delete UpdateCmd;
  if (QweakSimDir)       delete QweakSimDir;
  if (VisibilityDir)     delete VisibilityDir;
  if (DumpGeometry_Cmd)  delete DumpGeometry_Cmd;
  if (ShowHallFloor_Cmd) delete ShowHallFloor_Cmd;
  if (HideHallFloor_Cmd) delete HideHallFloor_Cmd;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  
  if( command == UpdateCmd )
   { 
     G4cout << "#### Messenger: Updating geometry " << G4endl;

     myDetector->UpdateGeometry(); 
   }

//   if( command == HallFloorMat_Cmd )
//    {
//        G4cout << "#### Messenger: Setting Floor Material to " << newValue << G4endl;
//
//        myDetector->SetHallFloorMaterial(newValue);
//    }

   if( command == DumpGeometry_Cmd )
   {
       G4cout << "#### Messenger: Dump Geometry " << G4endl;

       myDetector->DumpGeometry(DumpGeometry_Cmd->GetNewBoolValue(newValue));
   }

   if( command == ShowHallFloor_Cmd )
   { 
       G4cout << "#### Messenger: Show Hall Floor " << G4endl;

       myDetector->ShowHallFloor();
   }

   if( command == HideHallFloor_Cmd )
    { 
	G4cout << "#### Messenger: Hide Hall Floor " << G4endl;

	myDetector->HideHallFloor();
    }





}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimDetectorMessenger.cc,v $
//      Revision 1.3  2006/05/05 21:28:11  grimm
//      Added /HallC/Visibility/ShowHallFloor and /HallC/Visibility/HideHallFloor
//
//      Revision 1.2  2005/12/27 19:07:48  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

