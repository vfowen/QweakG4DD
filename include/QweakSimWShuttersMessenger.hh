//=============================================================================
//
//  File     QweakSimWShuttersMessenger.hh
//  Revision 1.0
//  Date     02/06/2012
//  Author   Kurtis Bartlett
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimWShuttersMessenger_h
#define QweakSimWShuttersMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//  user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimWShutters;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class QweakSimWShuttersMessenger: public G4UImessenger
{
  public:
    QweakSimWShuttersMessenger(QweakSimWShutters*, G4int n);
   ~QweakSimWShuttersMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    QweakSimWShutters*  myWShutters;

    G4UIdirectory*  WShuttersDir;

    G4UIcmdWithADoubleAndUnit* WShutters_SetThicknessInZ_Cmd;
    G4UIcmdWithoutParameter*   WShutters_SetEnabled_Cmd;
    G4UIcmdWithoutParameter*   WShutters_SetDisabled_Cmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif
