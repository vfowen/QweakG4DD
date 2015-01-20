//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimHDCMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:24:58 $
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
   \class QweakSimHDCMessenger
    
   \brief Scans the input file for /HDC/xyz commands

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
//  Update Date:      $Date: 2005/12/27 19:24:58 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimHDCMessenger_h
#define QweakSimHDCMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimHDC;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimHDCMessenger: public G4UImessenger
{
  public:
    QweakSimHDCMessenger(QweakSimHDC*,G4int pkg = 0);
   ~QweakSimHDCMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimHDC*            myHDC;
  

  G4UIdirectory*             HDCDir;

  G4int 				 	 fPackage;
  G4UIdirectory*             DirPerPackage;

  G4UIcmdWithAString*        HDC_MasterContainerMatCmd;
  G4UIcmdWithAString*        HDC_SubContainerMatCmd;

  G4UIcmdWithAString*        HDC_FrameMatCmd;
  G4UIcmdWithAString*        HDC_FoilMatCmd;
  G4UIcmdWithAString*        HDC_WirePlaneMatCmd;

  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInX_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInY_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInZ_Cmd;

  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInX_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInY_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInZ_Cmd;

  G4UIcmdWithADoubleAndUnit* HDC_RotationAngleInPhi_Cmd;
  
  //------------------------------------------------------

  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInX_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInY_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_FrontCenterPositionInZ_Pkg_Cmd;

  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInX_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInY_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* HDC_BackCenterPositionInZ_Pkg_Cmd;

  G4UIcmdWithADoubleAndUnit* HDC_RotationAngleInPhi_Pkg_Cmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimHDCMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:24:58  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

