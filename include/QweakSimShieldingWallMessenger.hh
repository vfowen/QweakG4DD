//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimShieldingWallMessenger.hh
   $Revision: 1.4 $	
   $Date: 2006/04/26 20:03:18 $
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
   \class QweakSimShieldingWallMessenger
    
   \brief Scans the input file for /ShieldingWall/xyz commands

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
//  Update Date:      $Date: 2006/04/26 20:03:18 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimShieldingWallMessenger_h
#define QweakSimShieldingWallMessenger_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimShieldingWall;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimShieldingWallMessenger: public G4UImessenger
{
  public:
    QweakSimShieldingWallMessenger(QweakSimShieldingWall*);
   ~QweakSimShieldingWallMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    QweakSimShieldingWall*     myShieldingWall;

    G4UIdirectory*             DetectorHutDir;
    G4UIdirectory*             CollimatorWallDir;
    G4UIdirectory*             VisibilityDir;

    G4UIcmdWithAString*        CollimatorWallMatCmd;
    G4UIcmdWithADoubleAndUnit* CollimatorWallZPosCmd;
    G4UIcmdWithoutParameter*   ShowCollimatorWall_Cmd;
    G4UIcmdWithoutParameter*   HideCollimatorWall_Cmd;

    G4UIcmdWithoutParameter*   ShowFrontWall_Cmd;
    G4UIcmdWithoutParameter*   HideFrontWall_Cmd;

    G4UIcmdWithoutParameter*   ShowBackWall_Cmd;
    G4UIcmdWithoutParameter*   HideBackWall_Cmd;

    G4UIcmdWithoutParameter*   ShowLeftWall_Cmd;
    G4UIcmdWithoutParameter*   HideLeftWall_Cmd;

    G4UIcmdWithoutParameter*   ShowRightWall_Cmd;
    G4UIcmdWithoutParameter*   HideRightWall_Cmd;

    G4UIcmdWithoutParameter*   ShowTopWall_Cmd;
    G4UIcmdWithoutParameter*   HideTopWall_Cmd;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimShieldingWallMessenger.hh,v $
//      Revision 1.4  2006/04/26 20:03:18  grimm
//      Added commands for (un)hiding the walls of the shielding detector hut
//
//      Revision 1.3  2006/01/18 20:21:01  grimm
//      Added visibility functions: ShowShieldingWall(), HideShieldingWall()
//
//      Revision 1.2  2005/12/27 19:26:47  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 


