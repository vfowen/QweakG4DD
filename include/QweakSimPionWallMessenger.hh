//=============================================================================
//
//  File     QweakSimPionWallMessenger.hh
//  Revision 1.0
//  Date     07/23/2012
//  Author   James Dowd
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimPionWallMessenger_h
#define QweakSimPionWallMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//  user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimPionWall;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class QweakSimPionWallMessenger: public G4UImessenger
{
  public:
    QweakSimPionWallMessenger(QweakSimPionWall*);
   ~QweakSimPionWallMessenger();
   
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    QweakSimPionWall*  myPionWall;
    
    G4UIdirectory*  PionWallDir;
    
    G4UIcmdWithADoubleAndUnit* PionWall_SetThicknessInX_Cmd;
    G4UIcmdWithADoubleAndUnit* PionWall_SetThicknessInY_Cmd;
    G4UIcmdWithADoubleAndUnit* PionWall_SetThicknessInZ_Cmd;
    G4UIcmdWithADoubleAndUnit* PionWall_SetOffsetX_Cmd;
    G4UIcmdWithADoubleAndUnit* PionWall_SetOffsetY_Cmd;
    G4UIcmdWithADoubleAndUnit* PionWall_SetOffsetZ_Cmd;
    G4UIcmdWithoutParameter*   PionWall_SetEnabled_Cmd;
    G4UIcmdWithoutParameter*   PionWall_SetDisabled_Cmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

