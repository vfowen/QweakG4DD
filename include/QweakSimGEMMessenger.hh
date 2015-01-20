//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimGEMMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:24:21 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimGEMMessenger
    
   \brief Scans the input file for /GEM/xyz commands

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:24:21 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimGEMMessenger_h
#define QweakSimGEMMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimGEM;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimGEMMessenger: public G4UImessenger
{
  public:
    QweakSimGEMMessenger(QweakSimGEM*);
   ~QweakSimGEMMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimGEM*            myGEM;
  
  G4UIdirectory*             GEMDir;

  G4UIcmdWithAString*        GEM_MasterContainerMatCmd;
  G4UIcmdWithAString*        GEM_SubContainerMatCmd;
  G4UIcmdWithAString*        GEM_FrameMatCmd;
  //G4UIcmdWithAString*        GEM_FoilMatCmd;
  //G4UIcmdWithAString*        GEM_WirePlaneMatCmd;
  G4UIcmdWithADoubleAndUnit* GEM_FrontCenterPositionInX_Cmd;
  G4UIcmdWithADoubleAndUnit* GEM_FrontCenterPositionInY_Cmd;
  G4UIcmdWithADoubleAndUnit* GEM_FrontCenterPositionInZ_Cmd;

  G4UIcmdWithADoubleAndUnit* GEM_BackCenterPositionInX_Cmd;
  G4UIcmdWithADoubleAndUnit* GEM_BackCenterPositionInY_Cmd;
  G4UIcmdWithADoubleAndUnit* GEM_BackCenterPositionInZ_Cmd;

  G4UIcmdWithADoubleAndUnit* GEM_FrontChamber_RotationAngleInPhi_Cmd;
  G4UIcmdWithADoubleAndUnit* GEM_BackChamber_RotationAngleInPhi_Cmd;
  
  G4UIdirectory*             DriftCellDir;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimGEMMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:24:21  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
