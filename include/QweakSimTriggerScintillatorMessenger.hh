
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTriggerScintillatorMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:22 $
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
   \class QweakSimTriggerScintillatorMessenger
    
   \brief Scans the input file for /Scintillator/xyz commands

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
//  Update Date:      $Date: 2005/12/27 19:28:22 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTriggerScintillatorMessenger_h
#define QweakSimTriggerScintillatorMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimTriggerScintillator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimTriggerScintillatorMessenger: public G4UImessenger
{
  public:
    QweakSimTriggerScintillatorMessenger(QweakSimTriggerScintillator*,G4int pkg = 0);
   ~QweakSimTriggerScintillatorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimTriggerScintillator*            myTriggerScintillator;
  
  G4UIdirectory*             Dir;

  G4int 		     fPackage;
  G4UIdirectory*             DirPerPackage;

  G4UIcmdWithAString*        ContainerMatCmd;
  G4UIcmdWithAString*        DetectorMatCmd;

  G4UIcmdWithADoubleAndUnit* ContainerXPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPositionCmd;

  G4UIcmdWithADoubleAndUnit* ContainerXPosition_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPosition_Pkg_Cmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPosition_Pkg_Cmd;

  G4UIcmdWithADoubleAndUnit* ContainerThicknessCmd;

  G4UIcmdWithADoubleAndUnit* TiltingAngleCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillatorMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:28:22  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
